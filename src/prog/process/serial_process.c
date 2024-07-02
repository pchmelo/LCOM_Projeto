#include "serial_process.h"

extern state_machine_game state_of_game_current;
extern state_machine_game state_of_game_previous;
extern state_main_menu state_main_menu_current;
extern state_game state_game_current;
extern state_menu_pause state_menu_pause_current;
extern state_multiplayer state_multiplayer_current;
extern game_round round;

extern state_connection state_connection_current;
extern state_invited state_invited_current;
extern state_sp state_sp_current;

extern int selected_card_player_1;
extern int selected_card_player_3;

extern state_select_card state_select_card_current;
extern state_prepare state_prepare_current;
extern state_time_tracker state_time_tracker_current;

extern int trump_location;
extern int slide_number;

extern uint8_t value_sp;
extern rtc_struct time_end;

void serial_process(){
    printf("Value_sp: %d\n", value_sp);
    if(state_of_game_current == MAIN_MENU || state_connection_current != NOTHING_CONNECTING || state_invited_current != NOTHING_INVITED){
        serial_process_main_menu();
    }
    else if(state_of_game_current == MULTIPLAYER_P1){
        serial_process_P1();
    }
    else if(state_of_game_current == MULTIPLAYER_P2){
        serial_process_P2();
    }
    else{
        sp_clean_interrupts();
    }

}

void serial_process_main_menu(){
    if(value_sp == 0x01){
        state_multiplayer_current = STARTED_SESSION;
        state_invited_current = WHAIT_INVITE;
    }
    else if(value_sp == 0x02){
        if(state_multiplayer_current == PLAYER_1_MUL){
            state_of_game_current = MULTIPLAYER_READY;
            state_connection_current = NOTHING_CONNECTING;
        }
    }
    else if(value_sp == 0xff){
        if(state_connection_current != NOTHING_CONNECTING){
            state_multiplayer_current = NO_PLAYER;
            state_connection_current = NOTHING_CONNECTING;
            state_of_game_current = MAIN_MENU;
            state_sp_current = NOTHING_SP;
        }
        else if(state_invited_current != NOTHING_INVITED){
            state_multiplayer_current = NO_PLAYER;
            state_invited_current = NOTHING_INVITED;
            state_of_game_current = MAIN_MENU;
            state_sp_current = NOTHING_SP;
        }
    }
   
}

void serial_process_P1(){
    if(value_sp == 0xff){
        state_of_game_current = MAIN_MENU;
        state_multiplayer_current = NO_PLAYER;
        state_sp_current = NOTHING_SP;
        state_time_tracker_current = NOTHING_TIME_SELECTED;

        if(rtc_get_time(&time_end)){
            printf("Error getting time\n");
            return;
        }
            
        printf("Exit the game Player 2 disconnected\n");
    }
    else if(value_sp == 0xfe){
        state_game_current = GAME_INIT;
    }
    else if(round == PLAYER_3){
        printf("Receive card from the player 3: %d\n", value_sp);
        selected_card_player_3 = value_sp;
    }
    else if(state_game_current == PREPARE_ROUND){
        if(state_prepare_current == PLAYER_3_TRUMP){
            if(value_sp == 0x04){
                trump_location = 1;
                //printf("Trump location: %d\n", trump_location);
            }
            else if(value_sp == 0x05){
                trump_location = 0;
                //printf("Trump location: %d\n", trump_location);
            }
            state_prepare_current = PLAYER_3_TRUMP_FINISH;
        }
        else if(state_prepare_current == PLAYER_3_SLIDE){
            slide_number = value_sp;
            state_prepare_current = PLAYER_3_SLIDE_FINISH;
            printf("Slide number: %d\n", slide_number);  
        }
    }
}

void serial_process_P2(){
    if(value_sp == 0xff){
        state_of_game_current = MAIN_MENU;
        state_multiplayer_current = NO_PLAYER;
        state_sp_current = NOTHING_SP;
        state_time_tracker_current = NOTHING_TIME_SELECTED;

        if(rtc_get_time(&time_end)){
            printf("Error getting time\n");
            return;
        }

        printf("Exit the game Player 1 disconnected\n");
    }
    else if(value_sp == 0xfe){
        state_game_current = GAME_INIT;
    }
    else if(round == PLAYER_1){
        printf("Receive card from the player 1: %d\n", value_sp);
        selected_card_player_1 = value_sp;
    }
    else if(state_game_current == PREPARE_ROUND){
        if(state_prepare_current == PLAYER_1_TRUMP){
            if(value_sp == 0x04){
                trump_location = 1;
                //printf("Trump location: %d\n", trump_location);
            }
            else if(value_sp == 0x05){
                trump_location = 0;
                //printf("Trump location: %d\n", trump_location);
            }
            state_prepare_current = PLAYER_1_TRUMP_FINISH;
        }
        else if(state_prepare_current == PLAYER_1_SLIDE){
            slide_number = value_sp;
            state_prepare_current = PLAYER_1_SLIDE_FINISH;
            printf("Slide number: %d\n", slide_number);  
        }
    }
}
