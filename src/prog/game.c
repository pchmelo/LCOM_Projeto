#include "game.h"

extern state_machine_game state_of_game_current;
extern state_machine_game state_of_game_previous;
extern state_main_menu state_main_menu_current;
extern state_game state_game_current;
extern state_menu_pause state_menu_pause_current;
extern state_multiplayer state_multiplayer_current;
extern state_sp state_sp_current;

extern game_round round;
extern grab_state grab;

extern uint8_t scancode;
extern int counter;
extern vbe_mode_info_t mode_info;

extern int mouse_x;
extern int mouse_y;
extern uint8_t byte_index;
extern struct packet mouse_packet;

int pause_on = 0;
int counter_pause = 0;
extern uint8_t value_sp;

extern rtc_struct rtc_time;

int fps = 30;
int teclado_on = 0;
int rato_on = 0;

int x_before = 100;
int y_before = 100;


int (loop_interrupcoes)(){
  int ipc_status;
  message msg;
  uint8_t timerMascara, tecladoMascara, mouseMascara, serialMascara;

  timer_set_frequency(TIMER0_IRQ, fps);

  if(allocate_collision_array()){
    fprintf(stderr, "Error: %s\n", "allocate_collision_array function error.");
    return 1;
  }

  fillDeck();

  if(timer_subscribe_int(&timerMascara)){
    fprintf(stderr, "Error: %s\n", "timer_subscribe_int function error.");
    return 1;
  }

  if(keyboard_subscribe_interrupt(&tecladoMascara)){
    fprintf(stderr, "Error: %s\n", "keyboard_subscribe_interrupt function error.");
    return 1;
  }

  //printf("Subscribed to keyboard\n");
  
  if(mouse_subscribe_int(&mouseMascara)){
    fprintf(stderr, "Error: %s\n", "mouse_subscribe_int function error.");
    return 1;
  }

  if(write_mouse(LIGAR_STREAM_MODE)){
    fprintf(stderr, "Error: %s\n", "mouse_write_command function error.");
    return 1;
  }

  if(write_mouse(LIGAR_DATA_REPORT)){
    fprintf(stderr, "Error: %s\n", "mouse_write_command function error.");
    return 1;
  }

  if(rtc_read_set()){
    fprintf(stderr, "Error: %s\n", "rtc_read_set function error.");
    return 1;
  }

  //printf("Subscribed to mouse\n");


  //serial port
  if((start_serial_port)()){
    fprintf(stderr, "Error: %s\n", "start_serial_port function error.");
    return 1;
  }

  if((serial_port_subscribe_interrupt(&serialMascara))){
    fprintf(stderr, "Error: %s\n", "serial_port_subscribe_interrupt function error.");
    return 1;
  }

  while(state_of_game_current != END){
    if( driver_receive(ANY, &msg, &ipc_status) != 0 ){
        printf("Error");
        continue;
    }
    if(is_ipc_notify(ipc_status)) {
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE:

          if(msg.m_notify.interrupts & timerMascara){    //verifica se a interrupção foi do timer
            timer_int_handler();
            process_timer(&teclado_on, &rato_on, mouse_x, mouse_y);
            //printf("timer1\n");

            if(counter % fps == 0){
              /*
                if(rtc_get_time()){
                  fprintf(stderr, "Error: %s\n", "rtc_get_time function error.");
                  return 1;
                }
              */
              
              //printf("Time: %d:%d:%d\n", rtc_time.hours, rtc_time.minutes, rtc_time.seconds);
              counter = 0;
            }

          }
          
          if (msg.m_notify.interrupts & tecladoMascara){    //verifica se a interrupção foi do teclado
            keyboard_ih();
            process_teclado(scancode, &teclado_on, &rato_on);
          } 

          if (msg.m_notify.interrupts & mouseMascara){    //verifica se a interrupção foi do rato
            mouse_interrupt_handler();
            mouse_sync_bytes();

            if(byte_index == 3){
              mouse_bytes_to_packet();
              byte_index = 0;

              if(rato_on == 0){
                if(mouse_x != x_before || mouse_y != y_before){
                  rato_on = 1;
                  teclado_on = 0;
                }
              }

              if(mouse_packet.lb){
                process_rato(mouse_x, mouse_y);
              }

              if(grab == GRAB){
                if(mouse_packet.lb == 0){
                  process_rato_grab_drop(mouse_x, mouse_y, &rato_on);
                }
              }

            }
          }

          else if(msg.m_notify.interrupts & serialMascara){    //verifica se a interrupção foi do serial port
            printf("Serial interrupt\n");
            sp_interrupt_handler();
            get_value();

            serial_process();

            if(state_sp_current == START_SP){
              printf("sending value finish\n");
              state_sp_current = FINISH_SP;
            }
          }

          break;

        default:
          break;
      }
    }

  }

  if(serial_port_unsubscribe_interrupt()){
    fprintf(stderr, "Error: %s\n", "serial_port_unsubscribe_interrupt function error.");
    return 1;
  }

  if(mouse_unsubscribe_int()){
    fprintf(stderr, "Error: %s\n", "mouse_unsubscribe_int function error.");
    return 1;
  }

  if(keyboard_unsubscribe_interrupt()){
    fprintf(stderr, "Error: %s\n", "keyboard_unsubscribe_interrupt function error.");
    return 1;
  }

  if(write_mouse(DESLIGAR_DATA_REPORT)){
    fprintf(stderr, "Error: %s\n", "mouse_write_command function error.");
    return 1;
  }

  if(timer_unsubscribe_int()){
    fprintf(stderr, "Error: %s\n", "timer_unsubscribe_int function error.");
    return 1;
  }
  
  free_collision_array();

  return 0;
}

int (wait_60_seconds)(){
  if(pause_on){
    counter_pause++;
    if(counter_pause == fps){
      counter_pause = 0;
      return 1;
    }
  }
  return 0;
}
