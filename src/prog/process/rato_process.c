#include "rato_process.h"

extern state_machine_game state_of_game_current;
extern state_machine_game state_of_game_previous;
extern state_main_menu state_main_menu_current;
extern state_game state_game_current;
extern state_menu_pause state_menu_pause_current;
extern state_multiplayer state_multiplayer_current;

extern state_invited state_invited_current;
extern state_connection state_connection_current;
extern state_sp state_sp_current;

extern state_select_card state_select_card_current;
extern state_prepare state_prepare_current;
extern state_split state_split_current;
extern state_time_tracker state_time_tracker_current;

extern game_round round;
extern grab_state grab;

extern Player player1;
extern Player player3;  

extern int selected_card_player_1;
extern int selected_card_player_3;

extern int trump_location;
extern int slide_number;

extern int square_x;

extern rtc_struct time_end;
extern rtc_struct time_start;

void process_rato(int mouse_x, int mouse_y){
    if(state_of_game_current == MAIN_MENU && state_connection_current == NOTHING_CONNECTING && state_invited_current == NOTHING_INVITED && state_time_tracker_current == NOTHING_TIME){
        if(testStartButtonCollision(mouse_x, mouse_y)){
            printf("Start button clicked\n");
            state_of_game_current = GAME;
            state_game_current = GAME_INIT;
            state_multiplayer_current = NO_PLAYER;
        }
        else if(testExitButtonCollision(mouse_x, mouse_y)){
            printf("Exit button clicked\n");
            state_of_game_current = END;
        }
        else if(testMultiButtonCollision(mouse_x, mouse_y)){
            if(state_multiplayer_current == NO_PLAYER){
                state_multiplayer_current = PLAYER_1_MUL;
                state_connection_current = CANCEL;
                enviar_byte(0x01);
            }
            else if(state_multiplayer_current == STARTED_SESSION){
                state_multiplayer_current = PLAYER_3_MUL;
                enviar_byte(0x02);
                state_of_game_current = MULTIPLAYER_READY;
            }
        }
    }
    else if(state_of_game_current == GAME && state_game_current != PREPARE_ROUND){
        if(state_game_current == PAUSE_MENU){
            if(testResumeButtonCollision(mouse_x, mouse_y)){
                state_game_current = START_GAME;
            }
            else if(testRestartButtonCollision(mouse_x, mouse_y)){
                state_game_current = GAME_INIT;
            }
            else if(testExitButtonCollisionPause(mouse_x, mouse_y)){
                state_of_game_current = MAIN_MENU;
                state_multiplayer_current = NO_PLAYER;
                state_time_tracker_current = NOTHING_TIME_SELECTED;
                if(rtc_get_time(&time_end)){
                    fprintf(stderr, "Error: %s\n", "rtc_get_time function error.");
                    return;
                }

                printf("Time start: %d:%d:%d\n", time_start.hours, time_start.minutes, time_start.seconds);
                printf("Time end: %d:%d:%d\n", time_end.hours, time_end.minutes, time_end.seconds);

            }
        }

        if(round == PLAYER_1){
            if(grab != GRAB && grab != PROCESS_GRAB){
                bool check = isPlayable(player1.playerHand, player1.numCards, player1.playerHand[selected_card_player_1]);
                if(check){
                    selected_card_player_1 = selected_card(mouse_x, mouse_y); 
                    if(selected_card_player_1 != -1){
                        printf("Card selected\n");
                        grab = PROCESS_GRAB;
                    }
                }
            }
        }

    }
    else if(state_of_game_current == GAME && state_game_current == PREPARE_ROUND){
        if(state_prepare_current == PLAYER_1_TRUMP || state_prepare_current == PLAYER_3_TRUMP){
            process_rato_get_trump(mouse_x, mouse_y);
        }
        else if(state_prepare_current == PLAYER_1_SLIDE || state_prepare_current == PLAYER_3_SLIDE){
            process_rato_slide(mouse_x, mouse_y);
        }
    }
    else if (state_of_game_current == MULTIPLAYER_P1){
        process_rato_P1(mouse_x, mouse_y);
    }
    else if (state_of_game_current == MULTIPLAYER_P2){
        process_rato_P2(mouse_x, mouse_y);
    }
    else if(state_connection_current != NOTHING_CONNECTING){
        process_rato_connection(mouse_x, mouse_y);
    }
    else if(state_invited_current != NOTHING_INVITED){
        process_rato_invitation(mouse_x, mouse_y);
    }
    else if(state_time_tracker_current != NOTHING_TIME){
        process_rato_time_tracker(mouse_x, mouse_y);
    }
}

void process_rato_grab_drop(int mouse_x, int mouse_y, int * rato_on){
    printf("Stop Grab\n");
    if(state_prepare_current != PLAYER_1_SLIDE && state_prepare_current != PLAYER_3_SLIDE){
        if(testCardGrabCollision(mouse_x, mouse_y)){
        
            if(state_of_game_current == MULTIPLAYER_P2){
                round = PLAYER_3_CHOOSE;
                enviar_byte(selected_card_player_3);
            }
            else{
                round = PLAYER_1_CHOOSE;
                enviar_byte(selected_card_player_1);
            }
        
            rato_on = 0;
        }
    }
    
    grab = NO_GRAB;
}

void process_card(int mouse_x, int mouse_y){
    selected_card_player_1 = selected_card(mouse_x, mouse_y); 
}

void process_rato_P1(int mouse_x, int mouse_y){
    if(state_game_current == PAUSE_MENU){
        if(testResumeButtonCollision(mouse_x, mouse_y)){
            state_game_current = START_GAME;
        }
        else if(testRestartButtonCollision(mouse_x, mouse_y)){
            state_game_current = GAME_INIT;
            enviar_byte(0xFE);
        }
        else if(testExitButtonCollisionPause(mouse_x, mouse_y)){
            state_of_game_current = MAIN_MENU;
            state_multiplayer_current = NO_PLAYER;
            state_time_tracker_current = NOTHING_TIME_SELECTED;
            enviar_byte(0xFF); 
            if(rtc_get_time(&time_end)){
                fprintf(stderr, "Error: %s\n", "rtc_get_time function error.");
                return;
            }
            printf("Time start: %d:%d:%d\n", time_start.hours, time_start.minutes, time_start.seconds);
            printf("Time end: %d:%d:%d\n", time_end.hours, time_end.minutes, time_end.seconds);
        }
    }

    else if(round == PLAYER_1){
        if(grab != GRAB && grab != PROCESS_GRAB){
            bool check = isPlayable(player1.playerHand, player1.numCards, player1.playerHand[selected_card_player_1]);
            if(check){
                selected_card_player_1 = selected_card(mouse_x, mouse_y); 
                if(selected_card_player_1 != -1){
                    printf("Card selected\n");
                    grab = PROCESS_GRAB;
                }
            }
        }
    }
    else if(state_prepare_current == PLAYER_1_TRUMP){
        process_rato_get_trump(mouse_x, mouse_y);
    }
    else if(state_prepare_current == PLAYER_1_SLIDE){
        process_rato_slide(mouse_x, mouse_y);
    }
}

void process_rato_P2(int mouse_x, int mouse_y){
    if(state_game_current == PAUSE_MENU){
        if(testResumeButtonCollision(mouse_x, mouse_y)){
            state_game_current = START_GAME;
        }
        else if(testRestartButtonCollision(mouse_x, mouse_y)){
            state_game_current = GAME_INIT;
            enviar_byte(0xFE);
        }
        else if(testExitButtonCollisionPause(mouse_x, mouse_y)){
            state_of_game_current = MAIN_MENU;
            state_multiplayer_current = NO_PLAYER;
            state_time_tracker_current = NOTHING_TIME_SELECTED;
            enviar_byte(0xFF);
            if(rtc_get_time(&time_end)){
                fprintf(stderr, "Error: %s\n", "rtc_get_time function error.");
                return;
            }
            printf("Time start: %d:%d:%d\n", time_start.hours, time_start.minutes, time_start.seconds);
            printf("Time end: %d:%d:%d\n", time_end.hours, time_end.minutes, time_end.seconds);
        }
    }

    else if(round == PLAYER_3){
        if(grab != GRAB && grab != PROCESS_GRAB){
            bool check = isPlayable(player3.playerHand, player3.numCards, player3.playerHand[selected_card_player_3]);
            if(check){
                selected_card_player_3 = selected_card(mouse_x, mouse_y); 
                if(selected_card_player_3 != -1){
                    printf("Card selected\n");
                    grab = PROCESS_GRAB;
                }
            }
        }
    }
    else if(state_prepare_current == PLAYER_3_TRUMP){
        process_rato_get_trump(mouse_x, mouse_y);
    }
    else if(state_prepare_current == PLAYER_3_SLIDE){
        process_rato_slide(mouse_x, mouse_y);
    }
}  

void process_rato_connection(int mouse_x, int mouse_y){
    if(testCancelButtonCollision(mouse_x, mouse_y)){
        state_connection_current = NOTHING_CONNECTING;
        state_multiplayer_current = NO_PLAYER;
        enviar_byte(0xff);
    }
}

void process_rato_invitation(int mouse_x, int mouse_y){
    if(testAcceptButtonCollision(mouse_x, mouse_y)){
        state_invited_current = NOTHING_INVITED;
        state_multiplayer_current = PLAYER_3_MUL;
        state_of_game_current = MULTIPLAYER_READY;
        state_sp_current = NOTHING_SP;
        enviar_byte(0x02);
    }
    else if(testDeclineButtonCollision(mouse_x, mouse_y)){
        state_invited_current = NOTHING_INVITED;
        state_multiplayer_current = NO_PLAYER;
        enviar_byte(0xFF);
    }
}

void process_rato_get_trump(int mouse_x, int mouse_y){
    if(testTopButton(mouse_x, mouse_y)){
        trump_location = 1;
        if(state_of_game_current == MULTIPLAYER_P2){
            state_prepare_current = PLAYER_3_TRUMP_FINISH;
        }
        else{
            state_prepare_current = PLAYER_1_TRUMP_FINISH;
        }

        if(state_of_game_current == MULTIPLAYER_P2 || state_of_game_current == MULTIPLAYER_P1){
            enviar_byte(0x04);
        }
        
        //printf("Trump selected TOP MOUSE\n");
    }
    else if(testBotButton(mouse_x, mouse_y)){
        trump_location = 0;
        if(state_of_game_current == MULTIPLAYER_P2){
            state_prepare_current = PLAYER_3_TRUMP_FINISH;
        }
        else{
            state_prepare_current = PLAYER_1_TRUMP_FINISH;
        }

        if(state_of_game_current == MULTIPLAYER_P2 || state_of_game_current == MULTIPLAYER_P1){
            enviar_byte(0x05);
        }
        //printf("Trump selected BOT MOUSE\n");
    }
}

void process_rato_slide(int mouse_x, int mouse_y){
    if(testSlideButton(mouse_x, mouse_y)){
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
    if(testSquareCollision(mouse_x, mouse_y)){
        if(grab != GRAB){
            grab = PROCESS_GRAB;
        }
    }
    else if(grab != GRAB){
        grab = NO_GRAB;
    }
}

void process_rato_time_tracker(int mouse_x, int mouse_y){
    if(testTimerTrackerCollision(mouse_x, mouse_y)){
        state_time_tracker_current = NOTHING_TIME;
    }
}

