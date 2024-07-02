#include "timer_process.h"

extern state_machine_game state_of_game_current;
extern state_machine_game state_of_game_previous;
extern state_main_menu state_main_menu_current;
extern state_game state_game_current;
extern state_menu_pause state_menu_pause_current;
extern grab_state grab;
extern state_multiplayer state_multiplayer_current;
extern state_sp state_sp_current;
extern state_select_card state_select_card_current;

extern int rato_on;

extern game_round round;
extern state_prepare state_prepare_current;
extern state_split state_split_current;

extern int turn;
extern int num_cards;

extern int player_a_dar;
extern int selected_card_player_1;

extern Player player1;
extern Player player2;
extern Player player3;
extern Player player4;

extern int selected_card_player_1;
extern int selected_card_player_2;
extern int selected_card_player_3;
extern int selected_card_player_4;

extern Card card_player_1;
extern Card card_player_2;
extern Card card_player_3;
extern Card card_player_4;

extern int player_1_played;
extern int player_3_played;

extern Card trump_card;
extern int trumpSuit;
extern int roundSuit;

extern int timer_pause;
extern int pause_on;
extern int trump_location;
extern int slide_number;

extern int player_a_split;

extern uint8_t value_sp;

extern int blueScore;
extern int redScore;

extern int square_x;
extern rtc_struct time_start;

int process_timer(int *teclado_on, int *rato_on, int mouse_x, int mouse_y){
    if(state_of_game_current == MULTIPLAYER_READY){
        if(state_multiplayer_current == PLAYER_1_MUL){
            printf("I am the Player 1\n");
            state_of_game_current = MULTIPLAYER_P1;

            uint8_t seed = get_seed();
            printf("Seed: %d\n", seed);
            
            enviar_byte(seed);
            set_seed(seed);
        }
        else if(state_multiplayer_current == PLAYER_3_MUL){
            printf("I am the Player 3\n");

            if(state_sp_current == NOTHING_SP){
                if(value_sp > 0x01){
                    state_sp_current = NOTHING_SP;
                    set_seed(value_sp);
                    state_of_game_current = MULTIPLAYER_P2;
                }
                else if(value_sp == 0x01){
                    printf("Start SP\n");
                    state_sp_current = START_SP;
                    return 0;
                }
                
            }
            else if(state_sp_current == FINISH_SP){
                printf("FINISH SP\n");
                state_sp_current = NOTHING_SP;
                set_seed(value_sp);
                state_of_game_current = MULTIPLAYER_P2;
            }

        }
        
        player_a_dar = 1;
        player_a_split = 4;
        if(rtc_get_time(&time_start)){
            fprintf(stderr, "Error: %s\n", "rtc_get_time function error.");
            return 1;
        }
    }


    if(state_of_game_current == MAIN_MENU){
        if(process_main_menu_timer()){
            fprintf(stderr, "Error: %s\n", "process_main_menu_timer function error.");
            return 1;
        }
    }
    else if(state_of_game_current == GAME){
        if(process_game_timer()){
            fprintf(stderr, "Error: %s\n", "process_game_timer function error.");
            return 1;
        }
    }
    else if(state_of_game_current == MULTIPLAYER_P1){
        if(process_game_timer_P1()){
            fprintf(stderr, "Error: %s\n", "process_game_timer_P1 function error.");
            return 1;
        }
    }
    else if(state_of_game_current == MULTIPLAYER_P2){
        if(process_game_timer_P2()){
            fprintf(stderr, "Error: %s\n", "process_game_timer_P2 function error.");
            return 1;
        }
    }

    if(*rato_on){
        if(criar_rato(mouse_x, mouse_y)){
            fprintf(stderr, "Error: %s\n", "criar_rato function error.");
            return 1;
        }
    }
            
    copiarbufferSetDesenhoToBufferGrafico();

    if(state_of_game_current == GAME && state_game_current == START_GAME){
        //printf("Process Round\n");
        process_round();
    }

    if((state_of_game_current == MULTIPLAYER_P1 || state_of_game_current == MULTIPLAYER_P2) && state_game_current == START_GAME){
        process_round_MUL();
    }

    return 0;
}

int process_main_menu_timer(){
    if(state_of_game_previous != MAIN_MENU){
        state_of_game_previous = MAIN_MENU;
        state_main_menu_current = WAIT;
        state_game_current = NOTHING_GAME_PLAY;
    }

    if(criar_main_menu(state_main_menu_current)){
        fprintf(stderr, "Error: %s\n", "criar_main_menu function error.");
        return 1;
    }
    return 0;
}

int process_game_timer(){
    if(state_of_game_previous != GAME){
        state_of_game_previous = GAME;
        state_main_menu_current = NOTHING_MAIN_MENU;
        state_game_current = GAME_INIT;
        if(rtc_get_time(&time_start)){
            fprintf(stderr, "Error: %s\n", "rtc_get_time function error.");
            return 1;
        }
    }

    if(state_game_current == GAME_INIT){

        printf("Game Init\n");

        state_prepare_current = SHUFFLE;
        state_game_current = PREPARE_ROUND;

        selected_card_player_1 = -1;
        selected_card_player_2 = -1;
        selected_card_player_3 = -1;
        selected_card_player_4 = -1;

        player_a_dar = 1;

        player_1_played = 0;
        player_3_played = 0;
        
        turn = 1;
        num_cards = 10;
        roundSuit = -1;
        trump_location = -1;
        slide_number = -1;
        redScore = 0;
        blueScore = 0;

        square_x = 387;

    }
    else if(state_game_current == PREPARE_ROUND){
        if(state_prepare_current == SHUFFLE){
            printf("Shuffle\n");
            shuffleDeck();
            

            if(player_a_dar == 1){
                state_prepare_current = PLAYER_1_SLIDE;
                state_split_current = NOTHING_SPLIT_SELECTED;
            }
            else{
                if(player_a_dar == 2){
                    fillPlayersHand(1, 2);
                    round = PLAYER_2;
                    trump_card = player2.playerHand[0];
                }
                else if(player_a_dar == 3){
                    fillPlayersHand(1, 3);
                    round = PLAYER_3;
                    trump_card = player3.playerHand[0];
                }
                else if(player_a_dar == 4){
                    fillPlayersHand(1, 4);
                    round = PLAYER_4;
                    trump_card = player4.playerHand[0];
                }
                state_prepare_current = END_PREPARE;
            }
            

        }

        if(state_prepare_current == PLAYER_1_SLIDE_FINISH){
            splitDeck();
            state_prepare_current = PLAYER_1_TRUMP;
            state_select_card_current = NOTHING_SELECTED;
            state_split_current = NOTHING_SPLIT;
        }
        else if(state_prepare_current ==  PLAYER_1_TRUMP_FINISH){
            printf("Player 1 Trump Finish\n");
            round = PLAYER_1;
            if(trump_location == 1){
                trump_card = getTop();
                fillPlayersHand(1, 1);
            }
            else if (trump_location == 0){
                trump_card = getBottom();
                fillPlayersHand(0, 2);
            }
            state_prepare_current = END_PREPARE;
            state_select_card_current = NOTHING_CARD_SELECT;
        }
        else if(state_prepare_current == END_PREPARE){
            trumpSuit = trump_card.suit;
            state_game_current = START_GAME;
        }
    }

    if(state_game_current == START_GAME && turn != 5){
       
       process_display();
    }

    if(criar_jogo()){
        fprintf(stderr, "Error: %s\n", "criar_jogo function error.");
        return 1;
    }


    if(state_game_current == PAUSE_MENU){
        if(criar_menu_pausa(state_menu_pause_current)){
            fprintf(stderr, "Error: %s\n", "criar_menu_pausa function error.");
            return 1;
        }
    }
    return 0;
}

void process_round(){
    if(turn == 5){
        int winner = processRound();

        if(winner == 1){
            round = PLAYER_1;
        }
        else if(winner == 2){
            round = PLAYER_2;
        }
        else if(winner == 3){
            round = PLAYER_3;
        }
        else if(winner == 4){
            round = PLAYER_4;
        }

        selected_card_player_1 = -1;
        selected_card_player_2 = -1;
        selected_card_player_3 = -1;
        selected_card_player_4 = -1;

        player_1_played = 0;
        player_3_played = 0;

        num_cards --;
        turn = 1;
        roundSuit = -1;

        if(num_cards == 0){
            printf("End Round\n");
            state_game_current = GAME_INIT;
        }
    }
    else{
        if(round == PLAYER_1_DIS){
            rato_on = 0;
            round = PLAYER_2;
            turn++;
        }
        else if(round == PLAYER_2_DIS){
            if(pause_on != 1){
                pause_on = 1;
                rato_on = 0;
            }
            int finish = wait_60_seconds();
            if(finish){
                round = PLAYER_3;
                turn++;
                pause_on = 0;
            }
        }
        else if(round == PLAYER_3_DIS){
            if(pause_on != 1){
                pause_on = 1;
                rato_on = 0;
            }
            int finish = wait_60_seconds();
            if(finish){
                round = PLAYER_4;
                turn++;
                pause_on = 0;
            }
        }
        else if(round == PLAYER_4_DIS){
             if(pause_on != 1){
                pause_on = 1;
                rato_on = 0;
            }
            int finish = wait_60_seconds();
            if(finish){
                round = PLAYER_1;
                turn++;
                pause_on = 0;
            }
        }
    }
}

void process_display(){
    if(round == PLAYER_1_CHOOSE){
        //printf("Selected Card player1: %d\n", selected_card_player_1);
        round = PLAYER_1_DIS;
        player_1_played = 1;
        card_player_1 = player1.playerHand[selected_card_player_1];
        removeCard (1, selected_card_player_1);
        if(turn == 1){
            roundSuit = card_player_1.suit;
        }

        
    }
    else if(round == PLAYER_2){
        //printf("Player 2\n");
        round = PLAYER_2_DIS;
        selected_card_player_2 = botPlayCard(player2.playerHand);
        //printf("Selected Card player2: %d\n", selected_card_player_2);
        removeCard (2, selected_card_player_2);
        if(turn == 1){
            roundSuit = card_player_2.suit;
        }

    }
    else if(round == PLAYER_3){
        //printf("Player 3\n");
        round = PLAYER_3_DIS;
        selected_card_player_3 = botPlayCard(player3.playerHand);
        //printf("Selected Card player3: %d\n", selected_card_player_3);
        removeCard (3, selected_card_player_3);
        if(turn == 1){
            roundSuit = card_player_3.suit;
        }
    }
    else if(round == PLAYER_4){
        //printf("Player 4\n");
        round = PLAYER_4_DIS;
        selected_card_player_4 = botPlayCard(player4.playerHand);
        //printf("Selected Card player4: %d\n", selected_card_player_4);
        removeCard (4, selected_card_player_4);
        if(turn == 1){
            roundSuit = card_player_4.suit;
        }

    }
}

int process_game_timer_P1(){
    if(state_of_game_previous != MULTIPLAYER_P1){
        state_of_game_previous = MULTIPLAYER_P1;
        state_main_menu_current = NOTHING_MAIN_MENU;
        state_game_current = GAME_INIT;
    }

    if(state_game_current == GAME_INIT){
        printf("Game Init\n");

        state_prepare_current = SHUFFLE;
        state_game_current = PREPARE_ROUND;

        selected_card_player_1 = -1;
        selected_card_player_2 = -1;
        selected_card_player_3 = -1;
        selected_card_player_4 = -1;

        player_1_played = 0;
        player_3_played = 0;
        round = WHAIT_GAME_ROUND;
        slide_number = -1;
        
        turn = 1;
        num_cards = 10;
        roundSuit = -1;
        trump_location = -1;

        redScore = 0;
        blueScore = 0;

        square_x = 387;


    }
    else if(state_game_current == PREPARE_ROUND){
        if(state_prepare_current == SHUFFLE){
            printf("Shuffle Seeded\n");
            shuffleDeckSeed();
            

            if(player_a_split == 1){
                state_prepare_current = PLAYER_1_SLIDE;
                state_split_current = NOTHING_SPLIT_SELECTED;
            }
            else if(player_a_split == 3){
                state_prepare_current = PLAYER_3_SLIDE;
                //player 3 a dar
            }
            else{
                state_prepare_current = MID_TERM;
            }
            
        }

        if(state_prepare_current == PLAYER_1_SLIDE_FINISH){
            splitDeck();
            state_split_current = NOTHING_SPLIT;
            state_prepare_current = MID_TERM;
        }
        else if(state_prepare_current == PLAYER_3_SLIDE_FINISH){
            splitDeck();
            state_split_current = NOTHING_SPLIT;
            state_prepare_current = MID_TERM;
        }

        if(state_prepare_current == MID_TERM){
            if(player_a_dar == 1){
                state_prepare_current = PLAYER_1_TRUMP;
                state_select_card_current = NOTHING_SELECTED;
            }
            else if(player_a_dar == 3){
                state_prepare_current = PLAYER_3_TRUMP;
            }
            else{
                if(player_a_dar == 2){
                    fillPlayersHand(1, 2);
                    round = PLAYER_2;
                    trump_card = player2.playerHand[0];
                }
                
                else if(player_a_dar == 4){
                    fillPlayersHand(1, 4);
                    round = PLAYER_4;
                    trump_card = player4.playerHand[0];
                }
                state_prepare_current = END_PREPARE;
            }
        }

        if(state_prepare_current ==  PLAYER_1_TRUMP_FINISH){
            printf("Player 1 Trump Finish\n");
            round = PLAYER_1;
            if(trump_location == 1){
                trump_card = getTop();
                fillPlayersHand(1, 1);
            }
            else if (trump_location == 0){
                trump_card = getBottom();
                fillPlayersHand(0, 2);
            }
            state_prepare_current = END_PREPARE;
            state_select_card_current = NOTHING_CARD_SELECT;
        }
        else if(state_prepare_current ==  PLAYER_3_TRUMP_FINISH){
            printf("Player 3 Trump Finish\n");
            round = PLAYER_3;
            if(trump_location == 1){
                trump_card = getTop();
                fillPlayersHand(1, 3);
            }
            else if (trump_location == 0){
                trump_card = getBottom();
                fillPlayersHand(0, 4);
            }
            state_prepare_current = END_PREPARE;
            state_select_card_current = NOTHING_CARD_SELECT;
        }
        else if(state_prepare_current == END_PREPARE){
            trumpSuit = trump_card.suit;
            state_game_current = START_GAME;
            state_prepare_current = NOTHING_PREPARE;
        }
    }



    if(state_game_current == START_GAME && turn != 5){
       process_display_P1();
    }

    if(criar_jogo_P1()){
        fprintf(stderr, "Error: %s\n", "criar_jogo function error.");
        return 1;
    }


    if(state_game_current == PAUSE_MENU){
        if(criar_menu_pausa(state_menu_pause_current)){
            fprintf(stderr, "Error: %s\n", "criar_menu_pausa function error.");
            return 1;
        }
    }
    return 0;
}

int process_game_timer_P2(){
    if(state_of_game_previous != MULTIPLAYER_P2){
        state_of_game_previous = MULTIPLAYER_P2;
        state_main_menu_current = NOTHING_MAIN_MENU;
        state_game_current = GAME_INIT;
    }

    if(state_game_current == GAME_INIT){
        printf("Game Init\n");

        state_prepare_current = SHUFFLE;
        state_game_current = PREPARE_ROUND;

        selected_card_player_1 = -1;
        selected_card_player_2 = -1;
        selected_card_player_3 = -1;
        selected_card_player_4 = -1;
        round = WHAIT_GAME_ROUND;

        player_1_played = 0;
        player_3_played = 0;
        slide_number = -1;

        turn = 1;
        num_cards = 10;
        roundSuit = -1;
        trump_location = -1;
        redScore = 0;
        blueScore = 0;

        square_x = 387;


    }
    else if(state_game_current == PREPARE_ROUND){
        if(state_prepare_current == SHUFFLE){
            printf("Shuffle Seeded\n");
            shuffleDeckSeed();
            

            if(player_a_split == 1){
                state_prepare_current = PLAYER_1_SLIDE;
            }
            else if(player_a_split == 3){
                state_prepare_current = PLAYER_3_SLIDE;
                state_split_current = NOTHING_SPLIT_SELECTED;
            }
            else{
                state_prepare_current = MID_TERM;
            }
        }

        if(state_prepare_current == PLAYER_1_SLIDE_FINISH){
            splitDeck();
            state_split_current = NOTHING_SPLIT;
            state_prepare_current = MID_TERM;
        }
        else if(state_prepare_current == PLAYER_3_SLIDE_FINISH){
            splitDeck();
            state_split_current = NOTHING_SPLIT;
            state_prepare_current = MID_TERM;
        }

        if(state_prepare_current == MID_TERM){
            if(player_a_dar == 1){
                state_prepare_current = PLAYER_1_TRUMP;
            }
            else if(player_a_dar == 3){
                state_prepare_current = PLAYER_3_TRUMP;
                state_select_card_current = NOTHING_SELECTED;
            }
            else{
                if(player_a_dar == 2){
                    fillPlayersHand(1, 2);
                    round = PLAYER_2;
                    trump_card = player2.playerHand[0];
                }
                
                else if(player_a_dar == 4){
                    fillPlayersHand(1, 4);
                    round = PLAYER_4;
                    trump_card = player4.playerHand[0];
                }
                state_prepare_current = END_PREPARE;
            }
        }

        if(state_prepare_current ==  PLAYER_1_TRUMP_FINISH){
            printf("Player 1 Trump Finish\n");
            round = PLAYER_1;
            if(trump_location == 1){
                trump_card = getTop();
                fillPlayersHand(1, 1);
            }
            else if (trump_location == 0){
                trump_card = getBottom();
                fillPlayersHand(0, 2);
            }
            state_prepare_current = END_PREPARE;
            state_select_card_current = NOTHING_CARD_SELECT;
        }
        else if(state_prepare_current ==  PLAYER_3_TRUMP_FINISH){
            printf("Player 3 Trump Finish\n");
            round = PLAYER_3;
            if(trump_location == 1){
                trump_card = getTop();
                fillPlayersHand(1, 3);
            }
            else if (trump_location == 0){
                trump_card = getBottom();
                fillPlayersHand(0, 4);
            }
            state_prepare_current = END_PREPARE;
            state_select_card_current = NOTHING_CARD_SELECT;
        }
        else if(state_prepare_current == END_PREPARE){
            trumpSuit = trump_card.suit;
            state_game_current = START_GAME;
            state_prepare_current = NOTHING_PREPARE;
        }
    }

    if(state_game_current == START_GAME && turn != 5){
       process_display_P2();
    }


    if(criar_jogo_P2()){
        fprintf(stderr, "Error: %s\n", "criar_jogo function error.");
        return 1;
    }

    if(state_game_current == PAUSE_MENU){
        if(criar_menu_pausa(state_menu_pause_current)){
            fprintf(stderr, "Error: %s\n", "criar_menu_pausa function error.");
            return 1;
        }
    }
    return 0;
}

void process_display_P1(){
    if(round == PLAYER_1_CHOOSE){
        //printf("Selected Card player1: %d\n", selected_card_player_1);
        round = PLAYER_1_DIS;
        player_1_played = 1;
        card_player_1 = player1.playerHand[selected_card_player_1];
        removeCard (1, selected_card_player_1);
        if(turn == 1){
            roundSuit = card_player_1.suit;
        }
    }
    else if(round == PLAYER_2){
        //printf("Player 2\n");
        round = PLAYER_2_DIS;
        selected_card_player_2 = botPlayCard(player2.playerHand);
        //printf("Selected Card player2: %d\n", selected_card_player_2);
        removeCard (2, selected_card_player_2);
        if(turn == 1){
            roundSuit = card_player_2.suit;
        }

    }
    else if(round == PLAYER_3){
        //read input from player 3
        if(state_sp_current == NOTHING_SP){
            printf("Start SP\n");
            state_sp_current = START_SP;
            return;
        }
        else if(state_sp_current == FINISH_SP){
            printf("FINISH SP\n");
            state_sp_current = NOTHING_SP;
            round = PLAYER_3_DIS;
            player_3_played = 1;
            card_player_3 = player3.playerHand[selected_card_player_3];
            removeCard (3, selected_card_player_3);
            if(turn == 1){
                roundSuit = card_player_3.suit;
            }
        }
    }
    else if(round == PLAYER_4){
        //printf("Player 4\n");
        round = PLAYER_4_DIS;
        selected_card_player_4 = botPlayCard(player4.playerHand);
        //printf("Selected Card player4: %d\n", selected_card_player_4);
        removeCard (4, selected_card_player_4);
        if(turn == 1){
            roundSuit = card_player_4.suit;
        }

    }
}

void process_round_MUL(){
    if(turn == 5){
        printf("End Round\n");
        int winner = processRound();

        if(winner == 1){
            round = PLAYER_1;
        }
        else if(winner == 2){
            round = PLAYER_2;
        }
        else if(winner == 3){
            round = PLAYER_3;
        }
        else if(winner == 4){
            round = PLAYER_4;
        }

        selected_card_player_1 = -1;
        selected_card_player_2 = -1;
        selected_card_player_3 = -1;
        selected_card_player_4 = -1;

        player_1_played = 0;
        player_3_played = 0;

        num_cards --;
        turn = 1;
        roundSuit = -1;

        if(num_cards == 0){
            printf("End Round\n");
            state_game_current = GAME_INIT;
            player_a_dar++;
            player_a_split++;

            if(player_a_dar == 5){
                player_a_dar = 1;
            }
            if(player_a_split == 5){
                player_a_split = 1;
            }
        }
    }
    else{
        if(round == PLAYER_1_DIS){
            if(pause_on != 1){
                printf("Player 1 processed\n");
                pause_on = 1;
                rato_on = 0;
            }
            int finish = wait_60_seconds();
            if(finish){
                rato_on = 0;
                round = PLAYER_2;
                turn++;
                printf("Player 2 next\n");
            }
        }
        else if(round == PLAYER_2_DIS){
            if(pause_on != 1){
                pause_on = 1;
                rato_on = 0;
            }
            int finish = wait_60_seconds();
            if(finish){
                round = PLAYER_3;
                turn++;
                pause_on = 0;
            }
        }
        else if(round == PLAYER_3_DIS){
            if(pause_on != 1){
                pause_on = 1;
                rato_on = 0;
            }
            int finish = wait_60_seconds();
            if(finish){
                round = PLAYER_4;
                turn++;
                pause_on = 0;
            }
        }
        else if(round == PLAYER_4_DIS){
             if(pause_on != 1){
                pause_on = 1;
                rato_on = 0;
            }
            int finish = wait_60_seconds();
            if(finish){
                round = PLAYER_1;
                turn++;
                pause_on = 0;
            }
        }
    }
}
void process_display_P2(){
    if(round == PLAYER_1){
        //read input from player 1
        if(state_sp_current == NOTHING_SP){
            printf("Start SP\n");
            state_sp_current = START_SP;
            return;
        }
        else if(state_sp_current == FINISH_SP){
            printf("Display player 1 card SP\n");
            state_sp_current = NOTHING_SP;
            round = PLAYER_1_DIS;
            player_1_played = 1;
            card_player_1 = player1.playerHand[selected_card_player_1];
            removeCard (1, selected_card_player_1);
            if(turn == 1){
                roundSuit = card_player_1.suit;
            }
            printf("Display player 1 finished\n");
            if(state_game_current == START_GAME){
                printf("Start Game\n");
            }
        }
    }
    else if(round == PLAYER_2){
        //printf("Player 2\n");
        round = PLAYER_2_DIS;
        selected_card_player_2 = botPlayCard(player2.playerHand);
        //printf("Selected Card player2: %d\n", selected_card_player_2);
        removeCard (2, selected_card_player_2);
        if(turn == 1){
            roundSuit = card_player_2.suit;
        }

    }
    else if(round == PLAYER_3_CHOOSE){
        //printf("Selected Card player3: %d\n", selected_card_player_3);
        round = PLAYER_3_DIS;
        player_3_played = 1;
        card_player_3 = player3.playerHand[selected_card_player_3];
        removeCard (3, selected_card_player_3);
        if(turn == 1){
            roundSuit = card_player_3.suit;
        }
    }
    else if(round == PLAYER_4){
        //printf("Player 4\n");
        round = PLAYER_4_DIS;
        selected_card_player_4 = botPlayCard(player4.playerHand);
        //printf("Selected Card player4: %d\n", selected_card_player_4);
        removeCard (4, selected_card_player_4);
        if(turn == 1){
            roundSuit = card_player_4.suit;
        }

    }
}

