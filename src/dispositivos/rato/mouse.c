#include "mouse.h"

struct packet mouse_packet;       
uint8_t byte_index = 0;       
uint8_t mouse_bytes[3];       
uint8_t current_byte;
int mouse_x = 100;
int mouse_y = 100;


// A escrita para o rato tem de ser feita de forma mais controlada do que no keyboard
// Temos de injetar o comando DIRETAMENTE no rato e esperar por uma resposta afirmativa (ACK).
int (write_mouse)(uint8_t command){
    uint8_t mouse_response;

    do {

        if (write_command_KBC(KBC_INPUT_COMMAND, WRITE_MOUSE_BYTE)){
            fprintf(stderr, "Error: %s\n", "write_command_KBC function error");
            return 1;
        } 

        if (write_command_KBC(KBC_OUTPUT_COMMAND, command)){
            fprintf(stderr, "Error: %s\n", "write_command_KBC function error");
            return 1;
        } 

        tickdelay(micros_to_ticks(KBC_TEMPO_ESPERA));

        if (util_sys_inb(KBC_OUTPUT_COMMAND, &mouse_response)){
            fprintf(stderr, "Error: %s\n", "util_sys_inb function error");
            return 1;
        }

    } while (mouse_response != ACKNOWLEDGED);

  return 0;
}

// Avalia a disposição dos bytes no array @mouse_bytes
// O primeiro byte do pacote é sempre o que tem o BIT(3) ativo
void mouse_sync_bytes(){
    if(byte_index == 0 && (current_byte & PRIMEIRO_BYTE)){
        mouse_bytes[byte_index] = current_byte;
        byte_index++;
    } else if (byte_index > 0){
        mouse_bytes[byte_index] = current_byte;
        byte_index++;
    }
}

// Transforma o array de bytes numa struct definida de acordo com a documentação
// do rato
void mouse_bytes_to_packet(){
    for (size_t i = 0; i < 3; i++){
       mouse_packet.bytes[i] = mouse_bytes[i];
    }                

    mouse_packet.lb = mouse_bytes[0] & LEFT_BUTTON;
    mouse_packet.rb = mouse_bytes[0] & RIGHT_BUTTON;
    mouse_packet.mb = mouse_bytes[0] & MIDDLE_BUTTON;
    mouse_packet.x_ov = mouse_bytes[0] & X_OVERFLOW;
    mouse_packet.y_ov = mouse_bytes[0] & Y_OVERFLOW;

    if (mouse_bytes[0] & MOUSE_X){
         mouse_packet.delta_x = (0xFF00 | mouse_bytes[1]);
    } else {
         mouse_packet.delta_x = mouse_bytes[1];
    }

    if (mouse_bytes[0] & MOUSE_Y){
         mouse_packet.delta_y = (0xFF00 | mouse_bytes[2]);
    } else {
         mouse_packet.delta_y = mouse_bytes[2];
    }

    for (int i = 0; i < 3; i++) {
        mouse_packet.bytes[i] = mouse_bytes[i];
    }

    int16_t dx = mouse_x + mouse_packet.delta_x;
    int16_t dy = mouse_y - mouse_packet.delta_y;

    /*
    uint16_t dx_t = dx + 18;
    uint16_t dy_t = dy + 2;

    uint16_t dx_f = dx + 46;
    uint16_t dy_f = dy + 50;
    */

    if (dx < (0 - 18) || dy < (0 - 13) || dx > (800 - 46) || dy > (600 - 50)) {
        return;
    }


    mouse_x = dx;
    mouse_y = dy;
    
    //printf("x = %d", mouse_x);
    //printf("y = %d \n", mouse_y);
}
