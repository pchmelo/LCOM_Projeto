#include "teclado_process.h"

extern int num_cards;
extern int selected_card_player_1;
extern int selected_card_player_3;

extern state_machine_game state_of_game_current;
extern state_machine_game state_of_game_previous;
extern state_main_menu state_main_menu_current;
extern state_game state_game_current;
extern state_menu_pause state_menu_pause_current;
extern state_multiplayer state_multiplayer_current;
extern state_time_tracker state_time_tracker_current;

extern state_connection state_connection_current;
extern state_invited state_invited_current;
extern state_sp state_sp_current;   
extern state_select_card state_select_card_current;
extern state_prepare state_prepare_current;
extern state_split state_split_current;

extern Player player1;
extern Player player3;

extern int trump_location;

extern game_round round;
extern int slide_number;

extern int square_x;

extern rtc_struct time_end;

void process_teclado(uint8_t scancode, int *teclado_on, int *rato_on){
    if(state_of_game_current == MAIN_MENU){
        if(state_connection_current == NOTHING_CONNECTING && state_invited_current == NOTHING_INVITED && state_time_tracker_current == NOTHING_TIME){
            process_main_menu_teclado(scancode, teclado_on, rato_on);
        }
        else if (state_connection_current != NOTHING_CONNECTING){
            process_connection_teclado(scancode, teclado_on, rato_on);  
        }
        else if (state_invited_current != NOTHING_INVITED){
            process_invitation_teclado(scancode, teclado_on, rato_on);
        }
        else if(state_time_tracker_current != NOTHING_TIME){
            process_time_tracker_teclado(scancode, teclado_on, rato_on);    
        }
        
    }
            
    else if((state_of_game_current == GAME || state_of_game_current == MULTIPLAYER_P1 || state_of_game_current == MULTIPLAYER_P2) && state_game_current != PREPARE_ROUND){
        process_game_teclado(scancode, teclado_on, rato_on);
    }
    else if(state_game_current == PREPARE_ROUND){
        if(state_prepare_current == PLAYER_1_TRUMP || state_prepare_current == PLAYER_3_TRUMP){
            process_prepare_round_trump_teclado(scancode, teclado_on, rato_on);
        }
        else if(state_prepare_current == PLAYER_1_SLIDE || state_prepare_current == PLAYER_3_SLIDE){
            process_prepare_round_slide_teclado(scancode, teclado_on, rato_on);
        }
        
    }
}

void process_main_menu_teclado(uint8_t scancode, int *teclado_on, int *rato_on){
    if(scancode == UP_ARROW_BREAK || scancode == DOWN_ARROW_BREAK || scancode == LEFT_ARROW_BREAK || scancode == RIGHT_ARROW_BREAK){
        if(*teclado_on == 0){
            *teclado_on = 1;
            *rato_on = 0;
        }

        if(scancode == UP_ARROW_BREAK){
            if(state_main_menu_current == WAIT){
                state_main_menu_current = START_BUTTON_COL;
            }
            else if(state_main_menu_current == START_BUTTON_COL){
                state_main_menu_current = EXIT_BUTTON_COL;
            }
            else if(state_main_menu_current == EXIT_BUTTON_COL){
                state_main_menu_current = START_BUTTON_COL;
            }
            else if(state_main_menu_current == MULTI_BUTTON_COL){
                state_main_menu_current = EXIT_BUTTON_COL;
            }
        }
        else if(scancode == DOWN_ARROW_BREAK){
            if(state_main_menu_current == WAIT){
                state_main_menu_current = EXIT_BUTTON_COL;
            }
            else if(state_main_menu_current == START_BUTTON_COL){
                state_main_menu_current = EXIT_BUTTON_COL;
            }
            else if(state_main_menu_current == EXIT_BUTTON_COL){
                state_main_menu_current = START_BUTTON_COL;
            }
            else if(state_main_menu_current == MULTI_BUTTON_COL){
                state_main_menu_current = EXIT_BUTTON_COL;
            }
        }
        else if(scancode == LEFT_ARROW_BREAK){
            if(state_main_menu_current == START_BUTTON_COL){
                state_main_menu_current = MULTI_BUTTON_COL;
            }
            else if(state_main_menu_current == MULTI_BUTTON_COL){
                state_main_menu_current = START_BUTTON_COL;
            }
            else if(state_main_menu_current == EXIT_BUTTON_COL){
                state_main_menu_current = START_BUTTON_COL;
            }
            else if(state_main_menu_current == WAIT){
                state_main_menu_current = START_BUTTON_COL;
            }
        }
        else if(scancode == RIGHT_ARROW_BREAK){
            if(state_main_menu_current == START_BUTTON_COL){
                state_main_menu_current = MULTI_BUTTON_COL;
            }
            else if(state_main_menu_current == MULTI_BUTTON_COL){
                state_main_menu_current = START_BUTTON_COL;
            }
            else if(state_main_menu_current == EXIT_BUTTON_COL){
                state_main_menu_current = MULTI_BUTTON_COL;
            }
            else if(state_main_menu_current == WAIT){
                state_main_menu_current = MULTI_BUTTON_COL;
            }
        }
    }

    if(scancode == ESC_BREAK){
        state_of_game_current = END;
    }

    if(scancode == ENTER_BREAK){
        if(state_main_menu_current == START_BUTTON_COL){
            state_of_game_current = GAME;
            state_game_current = GAME_INIT;
            state_multiplayer_current = NO_PLAYER;
        }
        else if(state_main_menu_current == EXIT_BUTTON_COL){
             state_of_game_current = END;
        }
        else if(state_main_menu_current == MULTI_BUTTON_COL){
            if(state_multiplayer_current == NO_PLAYER){
                state_multiplayer_current = PLAYER_1_MUL;
                state_connection_current = CANCEL;
                enviar_byte(0x01);
            }
            else if(state_multiplayer_current == STARTED_SESSION){
                state_invited_current = NOTHING_INVITED;
                state_multiplayer_current = PLAYER_3_MUL;
                state_of_game_current = MULTIPLAYER_READY;
                state_sp_current = NOTHING_SP;
                enviar_byte(0x02);
            }
        }
    }
}

void process_game_teclado(uint8_t scancode, int *teclado_on, int *rato_on){
    if(scancode == ESC_BREAK){
        if(state_game_current != PAUSE_MENU){
            state_game_current = PAUSE_MENU;
            state_menu_pause_current = WAIT_PAUSE;
        }
        else{
            state_game_current = START_GAME;
        }
    }


    if(state_game_current == PAUSE_MENU){
        if(scancode == UP_ARROW_BREAK || scancode == DOWN_ARROW_BREAK){
            if(*teclado_on == 0){
                *teclado_on = 1;
                *rato_on = 0;
            }
        }

        if(scancode == UP_ARROW_BREAK){
            if(state_menu_pause_current == WAIT_PAUSE){
                state_menu_pause_current = RESUME_BUTTON_COL;
            }
            else if(state_menu_pause_current == RESUME_BUTTON_COL){
                state_menu_pause_current = EXIT_BUTTON_COL_PAUSE;
            }
            else if(state_menu_pause_current == RESTART_BUTTON_COL){
                state_menu_pause_current = RESUME_BUTTON_COL;
            }
            else if(state_menu_pause_current == EXIT_BUTTON_COL_PAUSE){
                state_menu_pause_current = RESTART_BUTTON_COL;
            }
        }
        else if(scancode == DOWN_ARROW_BREAK){
            if(state_menu_pause_current == WAIT_PAUSE){
                state_menu_pause_current = EXIT_BUTTON_COL_PAUSE;
            }
            else if(state_menu_pause_current == RESUME_BUTTON_COL){
                state_menu_pause_current = RESTART_BUTTON_COL;
            }
            else if(state_menu_pause_current == RESTART_BUTTON_COL){
                state_menu_pause_current = EXIT_BUTTON_COL_PAUSE;
            }
            else if(state_menu_pause_current == EXIT_BUTTON_COL_PAUSE){
                state_menu_pause_current = RESUME_BUTTON_COL;
            }
        }

        if(scancode == ENTER_BREAK){
            if(state_menu_pause_current == RESUME_BUTTON_COL){
                state_game_current = START_GAME;
                scancode = 0;
            }
            else if(state_menu_pause_current == RESTART_BUTTON_COL){
                state_game_current = GAME_INIT;

                if(state_of_game_current == MULTIPLAYER_P1 || state_of_game_current == MULTIPLAYER_P2){
                    enviar_byte(0xFE);
                }
                
            }
            else if(state_menu_pause_current == EXIT_BUTTON_COL_PAUSE){
                state_of_game_current = MAIN_MENU;
                state_multiplayer_current = NO_PLAYER;
                state_time_tracker_current = NOTHING_TIME_SELECTED;
                if(state_of_game_current == MULTIPLAYER_P1 || state_of_game_current == MULTIPLAYER_P2){
                    enviar_byte(0xFF);
                }
                if(rtc_get_time(&time_end)){
                    fprintf(stderr, "Error: %s\n", "rtc_get_time function error.");
                }
            }
        }
    }

    if(state_of_game_current == GAME || state_of_game_current == MULTIPLAYER_P1){
        process_select_card_P1(scancode, teclado_on, rato_on, num_cards);
    }
    if(state_of_game_current == MULTIPLAYER_P2){
        process_select_card_P2(scancode, teclado_on, rato_on, num_cards);
    }

}

void process_select_card_P1(uint8_t scancode, int *teclado_on, int *rato_on, int max_cards){
    if(scancode == LEFT_ARROW_BREAK || scancode == RIGHT_ARROW_BREAK){
        if(*teclado_on == 0){
            *teclado_on = 1;
            *rato_on = 0;
        }
    }

    if(scancode == LEFT_ARROW_BREAK){
        if(selected_card_player_1 == 0){
            selected_card_player_1 = max_cards - 1;
        }
        else if(selected_card_player_1 == -1){
            selected_card_player_1 = 0;
        }

        else{
            selected_card_player_1--;
        }
    }
    else if(scancode == RIGHT_ARROW_BREAK){
        if(selected_card_player_1 == max_cards - 1){
            selected_card_player_1 = 0;
        }
        else if(selected_card_player_1 == -1){
            selected_card_player_1 = 0;
        }
        else{
            selected_card_player_1++;
        }
    }
    else if(scancode == ENTER_BREAK){
        bool check = isPlayable(player1.playerHand, player1.numCards, player1.playerHand[selected_card_player_1]);
        if(check){
            round = PLAYER_1_CHOOSE;
            enviar_byte(selected_card_player_1);
        }
    }
}

void process_select_card_P2(uint8_t scancode, int *teclado_on, int *rato_on, int max_cards){
    if(scancode == LEFT_ARROW_BREAK || scancode == RIGHT_ARROW_BREAK){
        if(*teclado_on == 0){
            *teclado_on = 1;
            *rato_on = 0;
        }
    }

    if(scancode == LEFT_ARROW_BREAK){
        if(selected_card_player_3 == 0){
            selected_card_player_3 = max_cards - 1;
        }
        else if(selected_card_player_3 == -1){
            selected_card_player_3 = 0;
        }

        else{
            selected_card_player_3--;
        }
    }
    else if(scancode == RIGHT_ARROW_BREAK){
        if(selected_card_player_3 == max_cards - 1){
            selected_card_player_3 = 0;
        }
        else if(selected_card_player_3 == -1){
            selected_card_player_3 = 0;
        }
        else{
            selected_card_player_3++;
        }
    }
    else if(scancode == ENTER_BREAK){
        bool check = isPlayable(player3.playerHand, player3.numCards, player3.playerHand[selected_card_player_3]);
        if(check){
            round = PLAYER_3_CHOOSE;
            enviar_byte(selected_card_player_3);
        }
    }
}

void process_connection_teclado(uint8_t scancode, int *teclado_on, int *rato_on){
    if(scancode == UP_ARROW_BREAK || scancode == DOWN_ARROW_BREAK){
        if(*teclado_on == 0){
            *teclado_on = 1;
            *rato_on = 0;
        }
    }
    if(scancode == ESC_BREAK){
        state_connection_current = NOTHING_CONNECTING;
        state_multiplayer_current = NO_PLAYER;
        state_of_game_current = MAIN_MENU;
        enviar_byte(0xFF);
    }
    else if(scancode == ENTER_BREAK){
        if(state_connection_current == CANCEL_COL){
            state_connection_current = NOTHING_CONNECTING;
            state_multiplayer_current = NO_PLAYER;
            state_of_game_current = MAIN_MENU;
            enviar_byte(0xFF);
        }
    }
    else if(scancode == UP_ARROW_BREAK || scancode == DOWN_ARROW_BREAK){
        if(state_connection_current == CANCEL){
            state_connection_current = CANCEL_COL;
        }
        else if(state_connection_current == CANCEL_COL){
            state_connection_current = CANCEL;
        }
    }
}

void process_invitation_teclado(uint8_t scancode, int *teclado_on, int *rato_on){
    if(scancode == ESC_BREAK){
        state_invited_current = NOTHING_INVITED;
        state_multiplayer_current = NO_PLAYER;
        state_of_game_current = MAIN_MENU;
        enviar_byte(0xFF);
    }
    else if(scancode == ENTER_BREAK){
        if(state_invited_current == ACCEPT_COL){
            state_invited_current = NOTHING_INVITED;
            state_multiplayer_current = PLAYER_3_MUL;
            state_of_game_current = MULTIPLAYER_READY;
            state_sp_current = NOTHING_SP;
            enviar_byte(0x02);
        }
        else if(state_invited_current == DECLINE_COL){
            state_invited_current = NOTHING_INVITED;
            state_multiplayer_current = NO_PLAYER;
            state_of_game_current = MAIN_MENU;
            enviar_byte(0xFF);
        }
    }
    else if(scancode == UP_ARROW_BREAK){
        if(state_invited_current == WHAIT_INVITE){
            state_invited_current = ACCEPT_COL;
        }
        else if(state_invited_current == ACCEPT_COL){
            state_invited_current = DECLINE_COL;
        }
        else if(state_invited_current == DECLINE_COL){
            state_invited_current = ACCEPT_COL;
        }
    }
    else if(scancode == DOWN_ARROW_BREAK){
        if(state_invited_current == WHAIT_INVITE){
            state_invited_current = DECLINE_COL;
        }
        else if(state_invited_current == ACCEPT_COL){
            state_invited_current = DECLINE_COL;
        }
        else if(state_invited_current == DECLINE_COL){
            state_invited_current = ACCEPT_COL;
        }
    }
}

void process_prepare_round_trump_teclado(uint8_t scancode, int *teclado_on, int *rato_on){
    if(scancode == LEFT_ARROW_BREAK || scancode == RIGHT_ARROW_BREAK){
        if(*teclado_on == 0){
            *teclado_on = 1;
            *rato_on = 0;
        }
    }
    
    if(scancode == ENTER_BREAK){
        if(state_select_card_current == SELECTED_TOP){
            if(state_of_game_current == MULTIPLAYER_P2){
                state_prepare_current = PLAYER_3_TRUMP_FINISH;
            }
            else{
                state_prepare_current = PLAYER_1_TRUMP_FINISH;
            }
            enviar_byte(0x04);
            trump_location = 1;
        }
        else if(state_select_card_current == SELECTED_BOT){
            if(state_of_game_current == MULTIPLAYER_P2){
                state_prepare_current = PLAYER_3_TRUMP_FINISH;
            }
            else{
                state_prepare_current = PLAYER_1_TRUMP_FINISH;
            }
            enviar_byte(0x05);
            trump_location = 0;
        }
    }
    else if(scancode == LEFT_ARROW_BREAK){
        if(state_select_card_current == NOTHING_SELECTED){
            state_select_card_current = SELECTED_TOP;
        }
        else if(state_select_card_current == SELECTED_TOP){
            state_select_card_current = SELECTED_BOT;
        }
        else if(state_select_card_current == SELECTED_BOT){
            state_select_card_current = SELECTED_TOP;
        }
    }
    else if(scancode == RIGHT_ARROW_BREAK){
        if(state_select_card_current == NOTHING_SELECTED){
            state_select_card_current = SELECTED_BOT;
        }
        else if(state_select_card_current == SELECTED_TOP){
            state_select_card_current = SELECTED_BOT;
        }
        else if(state_select_card_current == SELECTED_BOT){
            state_select_card_current = SELECTED_TOP;
        }
    }
}

void process_prepare_round_slide_teclado(uint8_t scancode, int *teclado_on, int *rato_on){
    if(scancode == UP_ARROW_BREAK || scancode == DOWN_ARROW_BREAK || scancode == LEFT_ARROW_BREAK || scancode == RIGHT_ARROW_BREAK){
        if(*teclado_on == 0){
            *teclado_on = 1;
            *rato_on = 0;
        }
    }

    if(scancode == ENTER_BREAK){
        if(state_split_current == SPLIT_SELECTED){
            slide_number = get_slider_pos(square_x);
            if(state_of_game_current == MULTIPLAYER_P2){
                state_prepare_current = PLAYER_3_SLIDE_FINISH;
            }
            else{
                state_prepare_current = PLAYER_1_SLIDE_FINISH;
            }
            if(state_of_game_current == MULTIPLAYER_P2 || state_of_game_current == MULTIPLAYER_P1){
                enviar_byte(slide_number);
            }
        }
    }
    else if(scancode == UP_ARROW_BREAK || scancode == DOWN_ARROW_BREAK){
        if(state_split_current == NOTHING_SPLIT_SELECTED){
            state_split_current = SPLIT_SELECTED;
        }
        else if(state_split_current == SPLIT_SELECTED){
            state_split_current = NOTHING_SPLIT_SELECTED;
        }
    }
    else if(scancode == LEFT_ARROW_BREAK){
        int t = square_x - 1;
        if(t >= 247){
            square_x = t;
        }
    }
    else if(scancode == RIGHT_ARROW_BREAK){
        int t = square_x + 1;
        if(t <= 528){
            square_x = t;
        }
    }
}

void process_time_tracker_teclado(uint8_t scancode, int *teclado_on, int *rato_on){
    if(scancode == UP_ARROW_BREAK || scancode == DOWN_ARROW_BREAK){
        if(*teclado_on == 0){
            *teclado_on = 1;
            *rato_on = 0;
        }
    }

    if(scancode == ENTER_BREAK){
        if(state_time_tracker_current == TIME_SELECTED){
            state_time_tracker_current = NOTHING_TIME;
        }
    }
    else if(scancode == UP_ARROW_BREAK || scancode == DOWN_ARROW_BREAK){
        if(state_time_tracker_current == NOTHING_TIME_SELECTED){
            state_time_tracker_current = TIME_SELECTED;
        }
        else if(state_time_tracker_current == TIME_SELECTED){
            state_time_tracker_current = NOTHING_TIME_SELECTED;
        }
    }
}

