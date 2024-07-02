#include "composer.h"

int debug_cards = 0;

uint32_t ambar = 0xffbf00;
uint32_t vermelho = 0xb22222;

extern int mouse_x;
extern int mouse_y;

extern Collision* array_collision_main_menu;
extern int size_array_collision_main_menu;

extern Collision* array_collision_pause_menu;
extern int size_array_collision_pause_menu;

extern Card deck[DECK_SIZE];
extern Player player1;
extern Player player2;
extern Player player3;
extern Player player4;

extern Card card_player_1;
extern Card card_player_2;
extern Card card_player_3;
extern Card card_player_4;

extern int selected_card_player_1;
extern int selected_card_player_2;
extern int selected_card_player_3;
extern int selected_card_player_4;

extern int player_1_played;
extern int player_3_played;

extern Card trump_card;

extern int blueScore;
extern int redScore;

state_machine_game state_of_game_current = MAIN_MENU;
state_machine_game state_of_game_previous = NOTHING_GAME;
state_main_menu state_main_menu_current = NOTHING_MAIN_MENU;
state_game state_game_current = NOTHING_GAME_PLAY;
state_menu_pause state_menu_pause_current = NOTHING_PAUSE_MENU;
state_multiplayer state_multiplayer_current = NO_PLAYER;
state_sp state_sp_current = NOTHING_SP;
state_invited state_invited_current = NOTHING_INVITED;

state_connection state_connection_current = NOTHING_CONNECTING;
state_select_card state_select_card_current = NOTHING_CARD_SELECT;

grab_state grab = NO_GRAB;

game_round round = WHAIT_GAME_ROUND;
state_prepare state_prepare_current = NOTHING_PREPARE;

state_split state_split_current = NOTHING_SPLIT;

state_time_tracker state_time_tracker_current = NOTHING_TIME;

int grabCardX = -1000;
int grabCardY = -1000;
Card grabbedCard;
Card player_1_deck_grabbed[10];
Card player_3_deck_grabbed[10];

int previous_mouse_x = 0;
int previous_mouse_y = 0;

int square_x = 387;
int square_y = 328;

rtc_struct time_start;
rtc_struct time_end;

int criar_main_menu(){
    limparBufferGrafico();


    if(printar_form_xpm_sprite(0, 0, sprite_main_menu_background)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print main_menu_background error.");
        return 1;
    }

    if(printar_form_xpm_sprite(200, 0, sprite_title)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print title error.");
        return 1;
    }

    if(state_main_menu_current == WAIT){
        if(printar_form_xpm_sprite(120, 330, sprite_button_start)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print title error.");
            return 1;
        }

        if(printar_form_xpm_sprite(433, 330, sprite_button_multi)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print title error.");
            return 1;
        }

        if(printar_form_xpm_sprite(270, 460, sprite_button_exit)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print title error.");
            return 1;
        }
    }
    else if(state_main_menu_current == START_BUTTON_COL){
        if(printar_form_xpm_sprite(120, 330, sprite_button_start_pressed)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print title error.");
            return 1;
        }

        if(printar_form_xpm_sprite(433, 330, sprite_button_multi)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print title error.");
            return 1;
        }

        if(printar_form_xpm_sprite(270, 460, sprite_button_exit)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print title error.");
            return 1;
        }
    }
    else if(state_main_menu_current == MULTI_BUTTON_COL){
        if(printar_form_xpm_sprite(120, 330, sprite_button_start)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print title error.");
            return 1;
        }

        if(printar_form_xpm_sprite(433, 330, sprite_button_multi_pressed)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print title error.");
            return 1;
        }

        if(printar_form_xpm_sprite(270, 460, sprite_button_exit)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print title error.");
            return 1;
        }
    }
    else if(state_main_menu_current == EXIT_BUTTON_COL){
        if(printar_form_xpm_sprite(120, 330, sprite_button_start)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print title error.");
            return 1;
        }

        if(printar_form_xpm_sprite(433, 330, sprite_button_multi)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print title error.");
            return 1;
        }

        if(printar_form_xpm_sprite(270, 460, sprite_button_exit_pressed)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print title error.");
            return 1;
        }
    }

    if(state_time_tracker_current != NOTHING_TIME){
        if(displayTimeTracker()){
            fprintf(stderr, "Error: %s\n", "displayTimeTracker function error.");
            return 1;
        }
    }

    if(state_connection_current != NOTHING_CONNECTING){
        if(display_connection_menu()){
            fprintf(stderr, "Error: %s\n", "display_connection_menu function error.");
            return 1;
        }
    }

    if(state_invited_current != NOTHING_INVITED){
        if(display_invitation_menu()){
            fprintf(stderr, "Error: %s\n", "display_invitation_menu function error.");
            return 1;
        }
    }

    return 0;
}

int criar_jogo(){
    limparBufferGrafico();

    if(printar_form_xpm_sprite(0, 0, sprite_table_top)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print game_background error.");
        return 1;
    }

    /*
    if(displayTime(10, 10)){
        fprintf(stderr, "Error: %s\n", "displayTime function error.");
        return 1;
    }
    */

   if(state_game_current == PREPARE_ROUND){
        if(state_prepare_current == PLAYER_1_SLIDE){
            grabSquare();
            if(displaySplitDeck()){
                fprintf(stderr, "Error: %s\n", "displaySplitDeck function error.");
                return 1;
            }
        }
        else if(state_prepare_current == PLAYER_1_TRUMP){
            if(displaySelectCard()){
                fprintf(stderr, "Error: %s\n", "displaySelectCard function error.");
                return 1;
            }
        }
   }

    if(state_game_current == START_GAME){
        if(criar_score_board()){
            fprintf(stderr, "Error: %s\n", "criar_score_round function error.");
            return 1;
        }
        
        if(grab == GRAB){
            if(criar_mao_grabbed()){
                fprintf(stderr, "Error: %s\n", "criar_mao_grabbed function error.");
                return 1;
            }   
            if(displayDragFrame()){
                fprintf(stderr, "Error: %s\n", "displayDragFrame function error.");
                return 1;
            }
        }
        else{
            if(criar_mao_jogador_1(player1.playerHand, player1.numCards)){
                fprintf(stderr, "Error: %s\n", "criar_mao_jogador_1 function error.");
                return 1;
            }
        }
    
        if(criar_mao_jogador_2(player2.playerHand, player2.numCards)){
            fprintf(stderr, "Error: %s\n", "criar_mao_jogador_2 function error.");
            return 1;
        }

        if(criar_mao_jogador_3(player3.playerHand, player3.numCards)){
            fprintf(stderr, "Error: %s\n", "criar_mao_jogador_2 function error.");
            return 1;
        }

        if(criar_mao_jogador_4(player4.playerHand, player4.numCards)){
            fprintf(stderr, "Error: %s\n", "criar_mao_jogador_2 function error.");
            return 1;
        }


        if(display_trump_card(trump_card)){
            fprintf(stderr, "Error: %s\n", "display_card_jogador_1 function error.");
            return 1;
        }

        if(round == PLAYER_1 && grab == NO_GRAB){

            bool frame = isPlayable(player1.playerHand, player1.numCards, player1.playerHand[selected_card_player_1]);

            if(frame){
                if(criarMolduraCarta(ambar)){
                    fprintf(stderr, "Error: %s\n", "criarMolduraCarta function error.");
                    return 1;
                }
            }
            else{
                if(criarMolduraCarta(vermelho)){
                    fprintf(stderr, "Error: %s\n", "criarMolduraCarta function error.");
                    return 1;
                }
            }
            
        }
        else if(round == PLAYER_1 && (grab == PROCESS_GRAB || grab == GRAB)){
            if(grabCard()){
                fprintf(stderr, "Error: %s\n", "grabCard function error.");
                return 1;
            }
        }

        displayCards();
    }
    
    return 0;
}

int criar_rato(int x, int y){
    int collision_result = 0;

    if(state_time_tracker_current != NOTHING_TIME){
        if(testTimerTrackerCollision(x, y)){
            collision_result = 1;
            state_time_tracker_current = TIME_SELECTED;
        }
        if(collision_result){
            if(printar_form_xpm_sprite(x, y, sprite_mouse_click)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else{
            state_time_tracker_current = NOTHING_TIME_SELECTED;
            if(printar_form_xpm_sprite(x, y, sprite_mouse)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
    }

    else if(state_connection_current != NOTHING_CONNECTING){
        if(testCancelButtonCollision(mouse_x, mouse_y)){
            collision_result = 1;
            state_connection_current = CANCEL_COL;
        }
        if(collision_result){
            if(printar_form_xpm_sprite(x, y, sprite_mouse_click)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else{
            state_connection_current = CANCEL;
            if(printar_form_xpm_sprite(x, y, sprite_mouse)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
    }
    else if(state_invited_current != NOTHING_CONNECTING){
        if(testAcceptButtonCollision(mouse_x, mouse_y)){
            collision_result = 1;
            state_invited_current = ACCEPT_COL;
        }
        else if(testCancelButtonCollision(mouse_x, mouse_y)){
            collision_result = 1;
            state_invited_current = DECLINE_COL;
        }
        if(collision_result){
            if(printar_form_xpm_sprite(x, y, sprite_mouse_click)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else{
            state_invited_current = WHAIT_INVITE;
            if(printar_form_xpm_sprite(x, y, sprite_mouse)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
    }

    else if(state_of_game_current == MAIN_MENU && state_connection_current == NOTHING_CONNECTING){
        for(int i = 0; i < size_array_collision_main_menu; i++){
            Collision collision = array_collision_main_menu[i];
            if((isCollision)(x, y, collision)){
                collision_result = 1;
                if(i == 0){
                    state_main_menu_current = START_BUTTON_COL;
                }
                else if(i == 1){
                    state_main_menu_current = EXIT_BUTTON_COL;
                }
                else if(i == 2){
                    state_main_menu_current = MULTI_BUTTON_COL;
                }

                break;
            }
        }
        if(collision_result){
            if(printar_form_xpm_sprite(x, y, sprite_mouse_click)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else{
            state_main_menu_current = WAIT;
            if(printar_form_xpm_sprite(x, y, sprite_mouse)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
    }
    else if(state_of_game_current == GAME && state_game_current != PREPARE_ROUND){
        if(state_game_current == PAUSE_MENU){
            for(int i = 0; i < size_array_collision_pause_menu; i++){
                Collision collision = array_collision_pause_menu[i];
                if((isCollision)(x, y, collision)){
                    collision_result = 1;
                    if(i == 0){
                        state_menu_pause_current = RESUME_BUTTON_COL;
                    }
                    else if(i == 1){
                        state_menu_pause_current = RESTART_BUTTON_COL;
                    }
                    else if(i == 2){
                        state_menu_pause_current = EXIT_BUTTON_COL_PAUSE;
                    }

                    break;
                }
            }
        }
        else if(round == PLAYER_1 && grab == NO_GRAB){
            selected_card_player_1 = selected_card(x, y); 
        }
        if(collision_result){
            if(printar_form_xpm_sprite(x, y, sprite_mouse_click)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else if (grab == GRAB && state_game_current == START_GAME){
            //printf("Grab mouse xpm\n");
            if(printar_form_xpm_sprite(x, y, sprite_mouse_grab)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else if(round == PLAYER_1 && selected_card_player_1 != -1 && state_game_current == START_GAME){
            if(printar_form_xpm_sprite(x, y, sprite_mouse_hand)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else{
            state_menu_pause_current = WAIT_PAUSE;
            if(printar_form_xpm_sprite(x, y, sprite_mouse)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
    }
    else if(((state_of_game_current == GAME || state_of_game_current == MULTIPLAYER_P1) &&  state_prepare_current == PLAYER_1_TRUMP) || (state_of_game_current == MULTIPLAYER_P2 && state_prepare_current == PLAYER_3_TRUMP)){
        if(testTopButton(mouse_x, mouse_y)){
            collision_result = 1;
            state_select_card_current = SELECTED_TOP;
        }
        else if(testBotButton(mouse_x, mouse_y)){
            collision_result = 1;
            state_select_card_current = SELECTED_BOT;
        }
        if(collision_result){
            if(printar_form_xpm_sprite(x, y, sprite_mouse_click)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else{
            state_select_card_current = NOTHING_SELECTED;
            if(printar_form_xpm_sprite(x, y, sprite_mouse)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
    }
    else if(((state_of_game_current == GAME || state_of_game_current == MULTIPLAYER_P1) &&  state_prepare_current == PLAYER_1_SLIDE) || (state_of_game_current == MULTIPLAYER_P2 && state_prepare_current == PLAYER_3_SLIDE)){
        if(testSlideButton(mouse_x, mouse_y)){
            collision_result = 1;
            state_split_current = SPLIT_SELECTED;
        }
        if(collision_result){
            if(printar_form_xpm_sprite(x, y, sprite_mouse_click)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else if(grab == GRAB || grab == PROCESS_GRAB){
            if(printar_form_xpm_sprite(x, y, sprite_mouse_grab)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else if(grab == NO_GRAB){
            if(testSquareCollision(mouse_x, mouse_y)){
                if(printar_form_xpm_sprite(x, y, sprite_mouse_hand)){
                    fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                    return 1;
                }
            }
            else{
                state_split_current = NOTHING_SPLIT_SELECTED;
                if(printar_form_xpm_sprite(x, y, sprite_mouse)){
                    fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                    return 1;
                }
            }
        }
        
    }
    else if(state_of_game_current == MULTIPLAYER_P1){
        if(state_game_current == PAUSE_MENU){
            for(int i = 0; i < size_array_collision_pause_menu; i++){
                Collision collision = array_collision_pause_menu[i];
                if((isCollision)(x, y, collision)){
                    collision_result = 1;
                    if(i == 0){
                        state_menu_pause_current = RESUME_BUTTON_COL;
                    }
                    else if(i == 1){
                        state_menu_pause_current = RESTART_BUTTON_COL;
                    }
                    else if(i == 2){
                        state_menu_pause_current = EXIT_BUTTON_COL_PAUSE;
                    }

                    break;
                }
            }
        }
        else if(round == PLAYER_1 && grab == NO_GRAB){
            selected_card_player_1 = selected_card(x, y); 
        }
        if(collision_result){
            if(printar_form_xpm_sprite(x, y, sprite_mouse_click)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else if (grab == GRAB && state_game_current == START_GAME){
            //printf("Grab mouse xpm\n");
            if(printar_form_xpm_sprite(x, y, sprite_mouse_grab)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else if(round == PLAYER_1 && selected_card_player_1 != -1 && state_game_current == START_GAME){
            if(printar_form_xpm_sprite(x, y, sprite_mouse_hand)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else{
            state_menu_pause_current = WAIT_PAUSE;
            if(printar_form_xpm_sprite(x, y, sprite_mouse)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
    }
    else if(state_of_game_current == MULTIPLAYER_P2){
        if(state_game_current == PAUSE_MENU){
            for(int i = 0; i < size_array_collision_pause_menu; i++){
                Collision collision = array_collision_pause_menu[i];
                if((isCollision)(x, y, collision)){
                    collision_result = 1;
                    if(i == 0){
                        state_menu_pause_current = RESUME_BUTTON_COL;
                    }
                    else if(i == 1){
                        state_menu_pause_current = RESTART_BUTTON_COL;
                    }
                    else if(i == 2){
                        state_menu_pause_current = EXIT_BUTTON_COL_PAUSE;
                    }

                    break;
                }
            }
        }
        else if(round == PLAYER_3 && grab == NO_GRAB){
            selected_card_player_3 = selected_card(x, y); 
        }
        if(collision_result){
            if(printar_form_xpm_sprite(x, y, sprite_mouse_click)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else if (grab == GRAB && state_game_current == START_GAME){
            //printf("Grab mouse xpm\n");
            if(printar_form_xpm_sprite(x, y, sprite_mouse_grab)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else if(round == PLAYER_3 && selected_card_player_3 != -1 && state_game_current == START_GAME){
            if(printar_form_xpm_sprite(x, y, sprite_mouse_hand)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
        else{
            state_menu_pause_current = WAIT_PAUSE;
            if(printar_form_xpm_sprite(x, y, sprite_mouse)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
                return 1;
            }
        }
    }


    else {
        if(printar_form_xpm_sprite(x, y, sprite_mouse)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print mouse error.");
            return 1;
        }
    }
    

    return 0;
}

int criar_menu_pausa(){
    if(criar_score_board()){
        fprintf(stderr, "Error: %s\n", "criar_score_round function error.");
        return 1;
    }
    
    if(state_of_game_current == MULTIPLAYER_P2){
        criar_mao_jogador_1(player3.playerHand, player3.numCards);
        criar_mao_jogador_2(player4.playerHand, player4.numCards);
        criar_mao_jogador_3(player1.playerHand, player1.numCards);
        criar_mao_jogador_4(player2.playerHand, player2.numCards);
    }
    else{
        criar_mao_jogador_1(player1.playerHand, player1.numCards);
        criar_mao_jogador_2(player2.playerHand, player2.numCards);
        criar_mao_jogador_3(player3.playerHand, player3.numCards);
        criar_mao_jogador_4(player4.playerHand, player4.numCards);
    }
    
    display_trump_card(trump_card);

    if(printar_form_xpm_sprite(150, 40, sprite_menu_pausa)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print menu_pausa error.");
        return 1;
    }

    if(state_menu_pause_current == WAIT_PAUSE){
        if(printar_form_xpm_sprite(275, 115, sprite_button_resume)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print button_resume error.");
            return 1;
        }

        if(printar_form_xpm_sprite(275, 240, sprite_button_restart)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print button_restart error.");
            return 1;
        }

        if(printar_form_xpm_sprite(275, 365, sprite_button_exit)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print button_exit error.");
            return 1;
        }
    }

    if(state_menu_pause_current == RESUME_BUTTON_COL){
        if(printar_form_xpm_sprite(275, 115, sprite_button_resume_selected)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print button_resume error.");
            return 1;
        }

        if(printar_form_xpm_sprite(275, 240, sprite_button_restart)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print button_restart error.");
            return 1;
        }

        if(printar_form_xpm_sprite(275, 365, sprite_button_exit)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print button_exit error.");
            return 1;
        }
    }

    if(state_menu_pause_current == RESTART_BUTTON_COL){
        if(printar_form_xpm_sprite(275, 115, sprite_button_resume)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print button_resume error.");
            return 1;
        }

        if(printar_form_xpm_sprite(275, 240, sprite_button_restart_selected)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print button_restart error.");
            return 1;
        }

        if(printar_form_xpm_sprite(275, 365, sprite_button_exit)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print button_exit error.");
            return 1;
        }
    }

    if(state_menu_pause_current == EXIT_BUTTON_COL_PAUSE){
        if(printar_form_xpm_sprite(275, 115, sprite_button_resume)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print button_resume error.");
            return 1;
        }

        if(printar_form_xpm_sprite(275, 240, sprite_button_restart)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print button_restart error.");
            return 1;
        }

        if(printar_form_xpm_sprite(275, 365, sprite_button_exit_pressed)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print button_exit error.");
            return 1;
        }
    }
    

    return 0;
}


int criar_mao_jogador_1(Card * playerHand, int numCards){
    int space = (730 - 73 * numCards) / 2;

    for(int i = 0; i < numCards; i++){
        if(printar_form_xpm_sprite(73*i + space + 34, 490, playerHand[i].sprite)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print clubs_2 error.");
            return 1;
        }
    }

    return 0;
}

int criar_mao_jogador_2(Card * playerHand, int numCards){
    int space = (108 - (73 + 15 * (numCards-1))) / 2;
    if(debug_cards){
        for(int i = 0; i < numCards; i++){
            if(printar_form_xpm_sprite_rotated(690, 15*i + space + 250, playerHand[i].sprite)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print clubs_2 error.");
                return 1;
            }
        }
    }
    else{
        for(int i = 0; i < numCards; i++){
            if(printar_form_xpm_sprite_rotated(690, 15*i + space + 250, sprite_back_2)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print clubs_2 error.");
                return 1;
            }
        }
    }
    

    return 0;
}

int criar_mao_jogador_3(Card * playerHand, int numCards){
    int space = (108 - (73 + 15 * (numCards-1))) / 2;

    if(debug_cards){
        for(int i = 0; i < numCards; i++){
            if(printar_form_xpm_sprite(15*i + space + 330, 0, playerHand[i].sprite)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print clubs_2 error.");
                return 1;
            }
        }
    }
    else{
        for(int i = 0; i < numCards; i++){
            if(printar_form_xpm_sprite(15*i + space + 330, 0, sprite_back_1)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print clubs_2 error.");
                return 1;
            }
        }
    }
    

    return 0;
}

int criar_mao_jogador_4(Card * playerHand, int numCards){
    int space = (108 - (73 + 15 * (numCards-1))) / 2;

    if(debug_cards){
        for(int i = 0; i < numCards; i++){
            if(printar_form_xpm_sprite_rotated(0, 15*i + space + 250, playerHand[i].sprite)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print clubs_2 error.");
                return 1;
            }
        }
    }
    else{
        for(int i = 0; i < numCards; i++){
            if(printar_form_xpm_sprite_rotated(0, 15*i + space + 250, sprite_back_2)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print clubs_2 error.");
                return 1;
            }
        }
    }
    

    return 0;
}


int display_card_jogador_1(Card card){
    if(printar_form_xpm_sprite(370, 330, card.sprite)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print clubs_2 error.");
        return 1;
    }

    return 0;
}

int display_card_jogador_2(Card card){
    if(printar_form_xpm_sprite(453, 245, card.sprite)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print clubs_2 error.");
        return 1;
    }

    return 0;
}

int display_card_jogador_3(Card card){
    if(printar_form_xpm_sprite(370, 160, card.sprite)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print clubs_2 error.");
        return 1;
    }

    return 0;
}

int display_card_jogador_4(Card card){
    if(printar_form_xpm_sprite(290, 245, card.sprite)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print clubs_2 error.");
        return 1;
    }

    return 0;
}

int display_trump_card(Card card){
    if(printar_form_xpm_sprite(720, 5, card.sprite)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print clubs_2 error.");
        return 1;
    }

    return 0;
}

int criarMolduraCarta(int color){
    if(selected_card_player_1 == -1){
        return 0;
    }

    int space = (730 - 73 * player1.numCards) / 2;

    int x = 73 * selected_card_player_1 + space + 34;
    int y = 490;

    if(molduraCarta(x, y, color)){
        fprintf(stderr, "Error: %s\n", "molduraCarta function error.");
        return 1;
    }
    return 0;
}

int criarMolduraCarta_P2(int color){
    if(selected_card_player_3 == -1){
        return 0;
    }

    int space = (730 - 73 * player3.numCards) / 2;

    int x = 73 * selected_card_player_3 + space + 34;
    int y = 490;

    if(molduraCarta(x, y, color)){
        fprintf(stderr, "Error: %s\n", "molduraCarta function error.");
        return 1;
    }
    return 0;
}

void displayCards(){
    if(player_1_played){
        display_card_jogador_1(card_player_1);
    }
    if(selected_card_player_2 != -1){
        display_card_jogador_2(card_player_2);
    }
    if(selected_card_player_3 != -1){
        display_card_jogador_3(card_player_3);
    }
    if(selected_card_player_4 != -1){
        display_card_jogador_4(card_player_4);
    }
}

int displayDragFrame(){
    if(molduraCarta(370, 330, ambar)){
        fprintf(stderr, "Error: %s\n", "molduraCarta function error.");
        return 1;
    }
    return 0;
}

int grabCard(){
    //printf("Selected card: %d\n", selected_card_player_1);
    if(grab == PROCESS_GRAB){
        //printf("Grab Card Process\n");
        grabCardX = 73 * selected_card_player_1 + ((730 - 73 * player1.numCards) / 2) + 34;
        grabCardY = 490;
        
        previous_mouse_x = mouse_x;
        previous_mouse_y = mouse_y;

        int i = 0;
        int j = 0;

        while(i < player1.numCards){
            if(i == selected_card_player_1){
                grabbedCard = player1.playerHand[i];
            }
            else{
                player_1_deck_grabbed[j] = player1.playerHand[i];
                j++;
            }
            i++;
        }
        grab = GRAB;
    }
    else{
        if(previous_mouse_x != mouse_x || previous_mouse_y != mouse_y){
            grabCardX += (mouse_x - previous_mouse_x);
            grabCardY += (mouse_y - previous_mouse_y);

            previous_mouse_x = mouse_x;
            previous_mouse_y = mouse_y;
        }
    }

    //printf("Grabbed card x: %d\n", grabCardX);
    //printf("Grabbed card y: %d\n", grabCardY);

    
    if(printar_form_xpm_sprite(grabCardX, grabCardY, grabbedCard.sprite)){
        fprintf(stderr, "Error: %s\n", "molduraCarta function error.");
        return 1;
    }
    

    return 0;
}

int grabCard_P2(){
    //printf("Selected card: %d\n", selected_card_player_1);
    if(grab == PROCESS_GRAB){
        //printf("Grab Card Process\n");
        grabCardX = 73 * selected_card_player_3 + ((730 - 73 * player3.numCards) / 2) + 34;
        grabCardY = 490;
        
        previous_mouse_x = mouse_x;
        previous_mouse_y = mouse_y;

        int i = 0;
        int j = 0;

        while(i < player3.numCards){
            if(i == selected_card_player_3){
                grabbedCard = player3.playerHand[i];
            }
            else{
                player_3_deck_grabbed[j] = player3.playerHand[i];
                j++;
            }
            i++;
        }
        grab = GRAB;
    }
    else{
        if(previous_mouse_x != mouse_x || previous_mouse_y != mouse_y){
            grabCardX += (mouse_x - previous_mouse_x);
            grabCardY += (mouse_y - previous_mouse_y);

            previous_mouse_x = mouse_x;
            previous_mouse_y = mouse_y;
        }
    }

    //printf("Grabbed card x: %d\n", grabCardX);
    //printf("Grabbed card y: %d\n", grabCardY);

    
    if(printar_form_xpm_sprite(grabCardX, grabCardY, grabbedCard.sprite)){
        fprintf(stderr, "Error: %s\n", "molduraCarta function error.");
        return 1;
    }
    

    return 0;
}


int criar_mao_grabbed(){
    int space = (730 - 73 * (player1.numCards - 1)) / 2;
    for(int i = 0; i < player1.numCards - 1; i++){
        if(printar_form_xpm_sprite(73*i + space + 34, 490, player_1_deck_grabbed[i].sprite)){  
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print clubs_2 error.");
            return 1;
        }
    }

    return 0;
}

int criar_mao_grabbed_P2(){
    int space = (730 - 73 * (player3.numCards - 1)) / 2;
    for(int i = 0; i < player3.numCards - 1; i++){
        if(printar_form_xpm_sprite(73*i + space + 34, 490, player_3_deck_grabbed[i].sprite)){  
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print clubs_2 error.");
            return 1;
        }
    }

    return 0;
}

int criar_jogo_P1(){
    limparBufferGrafico();

    if(printar_form_xpm_sprite(0, 0, sprite_table_top)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print game_background error.");
        return 1;
    }

    if(state_game_current == PREPARE_ROUND){
        if(state_prepare_current == PLAYER_1_SLIDE){
            grabSquare();
            if(displaySplitDeck()){
                fprintf(stderr, "Error: %s\n", "displaySplitDeck function error.");
                return 1;
            }
        }
        else if(state_prepare_current == PLAYER_1_TRUMP){
            if(displaySelectCard()){
                fprintf(stderr, "Error: %s\n", "displaySelectCard function error.");
                return 1;
            }
        }
    }

    if(state_game_current == START_GAME){
        if(criar_score_board()){
            fprintf(stderr, "Error: %s\n", "criar_score_round function error.");
            return 1;
        }
        
        if(grab == GRAB){
            if(criar_mao_grabbed()){
                fprintf(stderr, "Error: %s\n", "criar_mao_grabbed function error.");
                return 1;
            }   
            if(displayDragFrame()){
                fprintf(stderr, "Error: %s\n", "displayDragFrame function error.");
                return 1;
            }
        }
        else{
            if(criar_mao_jogador_1(player1.playerHand, player1.numCards)){
                fprintf(stderr, "Error: %s\n", "criar_mao_jogador_1 function error.");
                return 1;
            }
        }
    
        if(criar_mao_jogador_2(player2.playerHand, player2.numCards)){
            fprintf(stderr, "Error: %s\n", "criar_mao_jogador_2 function error.");
            return 1;
        }

        if(criar_mao_jogador_3(player3.playerHand, player3.numCards)){
            fprintf(stderr, "Error: %s\n", "criar_mao_jogador_2 function error.");
            return 1;
        }

        if(criar_mao_jogador_4(player4.playerHand, player4.numCards)){
            fprintf(stderr, "Error: %s\n", "criar_mao_jogador_2 function error.");
            return 1;
        }

        if(display_trump_card(trump_card)){
            fprintf(stderr, "Error: %s\n", "display_card_jogador_1 function error.");
            return 1;
        }

        if(round == PLAYER_1 && grab == NO_GRAB){

            bool frame = isPlayable(player1.playerHand, player1.numCards, player1.playerHand[selected_card_player_1]);

            if(frame){
                if(criarMolduraCarta(ambar)){
                    fprintf(stderr, "Error: %s\n", "criarMolduraCarta function error.");
                    return 1;
                }
            }
            else{
                if(criarMolduraCarta(vermelho)){
                    fprintf(stderr, "Error: %s\n", "criarMolduraCarta function error.");
                    return 1;
                }
            }
            
        }
        else if(round == PLAYER_1 && (grab == PROCESS_GRAB || grab == GRAB)){
            if(grabCard()){
                fprintf(stderr, "Error: %s\n", "grabCard function error.");
                return 1;
            }
        }

        displayCards_MUL();
    }
    
    return 0;
}

int criar_jogo_P2(){
    limparBufferGrafico();

    if(printar_form_xpm_sprite(0, 0, sprite_table_top)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print game_background error.");
        return 1;
    }

    if(state_game_current == PREPARE_ROUND){
        if(state_prepare_current == PLAYER_3_SLIDE){
            grabSquare();
            if(displaySplitDeck()){
                fprintf(stderr, "Error: %s\n", "displaySplitDeck function error.");
                return 1;
            }
        }
        else if(state_prepare_current == PLAYER_3_TRUMP){
            if(displaySelectCard()){
                fprintf(stderr, "Error: %s\n", "displaySelectCard function error.");
                return 1;
            }
        }
    }


    if(state_game_current == START_GAME){
        if(criar_score_board()){
            fprintf(stderr, "Error: %s\n", "criar_score_round function error.");
            return 1;
        }
        
        if(grab == GRAB){
            if(criar_mao_grabbed_P2()){
                fprintf(stderr, "Error: %s\n", "criar_mao_grabbed function error.");
                return 1;
            }   


            if(displayDragFrame()){
                fprintf(stderr, "Error: %s\n", "displayDragFrame function error.");
                return 1;
            }

        }
        else{
            if(criar_mao_jogador_1(player3.playerHand, player3.numCards)){
                fprintf(stderr, "Error: %s\n", "criar_mao_jogador_3 function error.");
                return 1;
            }
        }
    
        if(criar_mao_jogador_2(player4.playerHand, player4.numCards)){
            fprintf(stderr, "Error: %s\n", "criar_mao_jogador_4 function error.");
            return 1;
        }


        if(criar_mao_jogador_3(player1.playerHand, player1.numCards)){
            fprintf(stderr, "Error: %s\n", "criar_mao_jogador_1 function error.");
            return 1;
        }


        if(criar_mao_jogador_4(player2.playerHand, player2.numCards)){
            fprintf(stderr, "Error: %s\n", "criar_mao_jogador_2 function error.");
            return 1;
        }


        if(display_trump_card(trump_card)){
            fprintf(stderr, "Error: %s\n", "display_card_jogador_1 function error.");
            return 1;
        }


        if(round == PLAYER_3 && grab == NO_GRAB){


            bool frame = isPlayable(player3.playerHand, player3.numCards, player3.playerHand[selected_card_player_3]);

            if(frame){
                if(criarMolduraCarta_P2(ambar)){
                    fprintf(stderr, "Error: %s\n", "criarMolduraCarta function error.");
                    return 1;
                }
            }
            else{
                if(criarMolduraCarta_P2(vermelho)){
                    fprintf(stderr, "Error: %s\n", "criarMolduraCarta function error.");
                    return 1;
                }
            }
            
        }
        else if(round == PLAYER_3 && (grab == PROCESS_GRAB || grab == GRAB)){
            if(grabCard_P2()){
                fprintf(stderr, "Error: %s\n", "grabCard function error.");
                return 1;
            }
        }

        displayCards_MUL();
    }
    
    return 0;
}

void displayCards_MUL(){
    if(state_of_game_current == MULTIPLAYER_P1){
        if(player_1_played){
            display_card_jogador_1(card_player_1);
        }
        if(selected_card_player_2 != -1){
            display_card_jogador_2(card_player_2);
        }
        if(player_3_played){
            display_card_jogador_3(card_player_3);
        }
        if(selected_card_player_4 != -1){
            display_card_jogador_4(card_player_4);
        }
    }
    else if(state_of_game_current == MULTIPLAYER_P2){
        if(player_3_played){
            display_card_jogador_1(card_player_3);
        }
        if(selected_card_player_4 != -1){
            display_card_jogador_2(card_player_4);
        }
        if(player_1_played){
            display_card_jogador_3(card_player_1);
        }
        if(selected_card_player_2 != -1){
            display_card_jogador_4(card_player_2);
        }
    }
    
}

int displayTime(int x, int y){
    int* time = time_to_int();

    int width = 20, space_digit = 2, space_unit = 6;
    Sprite* sprite;

    for (int i = 0; i < 6; i++){
        sprite = num_to_sprite(time[i]);

        if(printar_form_xpm_sprite(x, y, sprite)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
            return 1;
        }

        x += width + space_digit;

        if (i % 2 != 0){
            x += space_unit;
        }
    }

    return 0;
}

int display_connection_menu(){
    if(printar_form_xpm_sprite(200, 100, sprite_main_menu_connection)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print connection_menu error.");
        return 1;
    }

    if(state_connection_current == CANCEL){
        if(printar_form_xpm_sprite(275, 330, sprite_button_cancel)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print connection_menu error.");
            return 1;
        }
    }
    else if(state_connection_current == CANCEL_COL){
        if(printar_form_xpm_sprite(275, 330, sprite_button_cancel_selected)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print connection_menu error.");
            return 1;
        }
    }

    
    return 0;
}


int display_invitation_menu(){
    if(printar_form_xpm_sprite(150, 40, sprite_menu_invited)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print connection_menu error.");
        return 1;
    }

    if(state_invited_current == WHAIT_INVITE){
        if(printar_form_xpm_sprite(250, 240, sprite_button_accept)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print connection_menu error.");
            return 1;
        }
        if(printar_form_xpm_sprite(250, 365, sprite_button_decline)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print connection_menu error.");
            return 1;
        }
    }
    else if(state_invited_current == ACCEPT_COL){
        if(printar_form_xpm_sprite(250, 240, sprite_button_accept_selected)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print connection_menu error.");
            return 1;
        }
        if(printar_form_xpm_sprite(250, 365, sprite_button_decline)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print connection_menu error.");
            return 1;
        }
    }
    else if(state_invited_current == DECLINE_COL){
        if(printar_form_xpm_sprite(250, 240, sprite_button_accept)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print connection_menu error.");
            return 1;
        }
        if(printar_form_xpm_sprite(250, 365, sprite_button_decline_selected)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print connection_menu error.");
            return 1;
        }
    }


    return 0;
}


int criar_score_board(){
    if(printar_form_xpm_sprite(26, 26, sprite_score_board)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print score_board error.");
        return 1;
    }

    int* int_blueScore = score_to_int(blueScore);
    int* int_redScore = score_to_int(redScore);

    int blue_x = 126, blue_y = 39, red_x = 126, red_y = 72, space = 5, width = 20;

    for(int i = 0; i < 3; i++){
        Sprite* score_sprite = num_to_sprite(int_blueScore[i]);

        if((i == 0 && int_blueScore[0] == 0) || (i == 1 && int_blueScore[0] == 0 && int_blueScore[1] == 0)){
            //skip
        }
        else{
            if(printar_form_xpm_sprite(blue_x, blue_y, score_sprite)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print score_board error.");
                return 1;
            }
        }

        blue_x += width + space;
    }

    for(int i = 0; i < 3; i++){
        Sprite* score_sprite = num_to_sprite(int_redScore[i]);

        if((i == 0 && int_redScore[0] == 0) || (i == 1 && int_redScore[0] == 0 && int_redScore[1] == 0)){
            //skip
        }
        else{
            if(printar_form_xpm_sprite(red_x, red_y, score_sprite)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print score_board error.");
                return 1;
            }
        }

        red_x += width + space;
    }

    return 0;
}


int displaySelectCard(){
    if(printar_form_xpm_sprite(209, 101, sprite_select_card_bg)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
        return 1;
    }

    if(printar_form_xpm_sprite(255, 273, sprite_card_deck)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
        return 1;
    }

    if(printar_form_xpm_sprite(311, 263, sprite_select_card_arrow)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
        return 1;
    }

    if(printar_form_xpm_sprite(462, 324, sprite_select_card_arrow_inv)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
        return 1;
    }

    if(printar_form_xpm_sprite(414, 273, sprite_card_deck)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
        return 1;
    }

    if(state_select_card_current == NOTHING_SELECTED){

        if(printar_form_xpm_sprite(249, 392, sprite_select_top_btn)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
            return 1;
        }

        if(printar_form_xpm_sprite(412, 392, sprite_select_bot_btn)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
            return 1;
        }
    }
    else if(state_select_card_current == SELECTED_TOP){

        if(printar_form_xpm_sprite(249, 392, sprite_select_top_btn_pressed)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
            return 1;
        }

        if(printar_form_xpm_sprite(412, 392, sprite_select_bot_btn)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
            return 1;
        }
    }
    else if(state_select_card_current == SELECTED_BOT){

        if(printar_form_xpm_sprite(249, 392, sprite_select_top_btn)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
            return 1;
        }

        if(printar_form_xpm_sprite(412, 392, sprite_select_bot_btn_pressed)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
            return 1;
        }
    }

    return 0;
}

int displaySplitDeck(){
    if(printar_form_xpm_sprite(148, 50, sprite_split_deck_bg)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
        return 1;
    }

    if(printar_form_xpm_sprite(square_x, square_y, sprite_slider)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
        return 1;
    }

    int x_seconde_bar = 247;
    int y_seconde_bar = 334;
    int width_split = square_x - 247;
    int height_split = 10;
    if(width_split < 0){
        width_split = 1;
    }

    if(drawSpiltSecondBar(x_seconde_bar, y_seconde_bar, width_split, height_split, 0x0000ff)){
        fprintf(stderr, "Error: %s\n", "drawSpiltSecondBar function error.");
        return 1;
    }

    //display a cada numero do split

    int num_split = get_slider_pos(square_x) + 1;

    int* display_split = score_to_int(num_split);
    int x_pos = 385;
    int space = 5;
    int width = 20;

    for(int i = 1; i < 3; i++){
        Sprite* score_sprite = num_to_sprite(display_split[i]);

        if(display_split[1] == 0 && i == 1){
            //skip
        }
        else{
            if(printar_form_xpm_sprite(x_pos, 360, score_sprite)){
                fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
                return 1;
            }
        }

        x_pos += width + space;
    }


    if(state_split_current == NOTHING_SPLIT_SELECTED){
        if(printar_form_xpm_sprite(274, 413, sprite_split_deck_btn)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
            return 1;
        }
    }
    else if(state_split_current == SPLIT_SELECTED){
        if(printar_form_xpm_sprite(274, 413, sprite_split_deck_btn_pressed)){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
            return 1;
        }
    }

    return 0;
}

int displayTimeTracker() {
    if (printar_form_xpm_sprite(148, 50, sprite_time_tracker)) {
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
        return 1;
    }

    int time_spent = get_time_spent(time_start, time_end), size, pos = 314;
    int* time_array = time_spent_to_array(time_spent, &size);

    for(int i = 0; i < size; i++){
        if(printar_form_xpm_sprite(pos, 230, num_to_sprite(time_array[i]))){
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
            return 1;
        }

        pos += 22;
    }

    pos += 20;

    if(printar_form_xpm_sprite(pos, 233, sprite_minutes)){
        fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
        return 1;
    }

    if (state_time_tracker_current == NOTHING_TIME_SELECTED) {
        if (printar_form_xpm_sprite(274, 283, sprite_split_deck_btn)) {
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
            return 1;
        }
    } else if (state_time_tracker_current == TIME_SELECTED) {
        if (printar_form_xpm_sprite(274, 283, sprite_split_deck_btn_pressed)) {
            fprintf(stderr, "Error: %s\n", "printar_form_xpm_sprite function to print num error.");
            return 1;
        }

    }

    return 0;
}

void grabSquare(){
    if(grab == PROCESS_GRAB){
        previous_mouse_x = mouse_x;
        grab = GRAB;
    }
    else if(grab == GRAB){
        if(previous_mouse_x != mouse_x && mouse_x >= 247 && mouse_x <= 515){
            square_x += (mouse_x - previous_mouse_x);

            previous_mouse_x = mouse_x;
        }
    }

    //printf("Grabbed card x: %d\n", grabCardX);
    //printf("Grabbed card y: %d\n", grabCardY);
}

