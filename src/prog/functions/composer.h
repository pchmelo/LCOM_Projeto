#ifndef COMPOSER_H
#define COMPOSER_H

#include "sprite.h"
#include "collision.h"
#include "../../dispositivos/grafica/grafica.h"
#include "../../dispositivos/rato/mouse.h"
#include "../../dispositivos/rtc/rtc.h"
#include "../game_rules/rules.h"
#include "../process/teclado_process.h"



/**
 * @brief Enum representing the different states of the application.
 */
typedef enum {MAIN_MENU, GAME, END, NOTHING_GAME, MULTIPLAYER_P1, MULTIPLAYER_P2, MULTIPLAYER_READY} state_machine_game;

/**
 * @brief Enum representing the different states of the main menu.
 */
typedef enum {NOTHING_MAIN_MENU, WAIT, START_BUTTON_COL, MULTI_BUTTON_COL ,EXIT_BUTTON_COL} state_main_menu;

/**
 * @brief Enum representing the different states of the "Sueca" game itself.
 */
typedef enum {NOTHING_GAME_PLAY, PAUSE_MENU, GAME_INIT, START_GAME, END_ROUND, SCORE_ROUND, PREPARE_ROUND} state_game;

/**
 * @brief Enum representing the different states of the pause menu.
 */
typedef enum {NOTHING_PAUSE_MENU, WAIT_PAUSE, RESUME_BUTTON_COL, EXIT_BUTTON_COL_PAUSE, RESTART_BUTTON_COL} state_menu_pause;

/**
 * @brief Enum representing the different states of a Trick in the game.
 */
typedef enum {PLAYER_1, PLAYER_1_CHOOSE, PLAYER_1_DIS ,PLAYER_2, PLAYER_2_DIS, PLAYER_3, PLAYER_3_CHOOSE ,PLAYER_3_DIS , PLAYER_4, PLAYER_4_DIS, WHAIT_GAME_ROUND} game_round;

/**
 * @brief Enum representing the different states of the grab.
 */
typedef enum {NO_GRAB, PROCESS_GRAB, GRAB, STOP_GRAB} grab_state;

/**
 * @brief Enum that determines who the different players in a multiplayer game are
 */
typedef enum {NO_PLAYER, STARTED_SESSION, PLAYER_1_MUL, PLAYER_3_MUL} state_multiplayer;

/**
 * @brief Enum representing a waiting state for an Serial Port Interrupt from another player before a multiplayer game.
 */
typedef enum {NOTHING_SP, START_SP, FINISH_SP} state_sp;

/**
 * @brief Enum representing the different states of the multiplayer connection menu.
 */
typedef enum {NOTHING_CONNECTING, CANCEL, CANCEL_COL} state_connection;

/**
 * @brief Enum representing the different states of the multiplayer invitation menu.
 */
typedef enum {NOTHING_INVITED, WHAIT_INVITE, ACCEPT_COL, DECLINE_COL} state_invited;

/**
 * @brief Enum representing the different states of the select top or bottom menu.
 */
typedef enum {NOTHING_CARD_SELECT, NOTHING_SELECTED, SELECTED_TOP, SELECTED_BOT} state_select_card;

/**
 * @brief Enum representing the different states of the split deck menu.
 */
typedef enum {NOTHING_SPLIT, NOTHING_SPLIT_SELECTED, SPLIT_SELECTED} state_split;

/**
 * @brief Enum representing the different states of the time tracker.
 */
typedef enum {NOTHING_TIME, NOTHING_TIME_SELECTED, TIME_SELECTED} state_time_tracker;


/**
 * @brief Enum representing the different states of the prepare round.
 */
typedef enum {SHUFFLE, PLAYER_1_TRUMP, PLAYER_1_TRUMP_FINISH, PLAYER_3_TRUMP, PLAYER_3_TRUMP_FINISH, END_PREPARE, NOTHING_PREPARE, PLAYER_1_SLIDE, PLAYER_1_SLIDE_FINISH, PLAYER_3_SLIDE, PLAYER_3_SLIDE_FINISH, MID_TERM} state_prepare;

/**
 * @brief Creates the main menu of the game.
 *
 * Creates the main menu of the game. Clears the graphic buffer and prints the main menu background and title. 
 * Depending on the current state of the main menu, it prints the appropriate buttons (start, multiplayer, exit) in their normal or pressed state.
 * If the current state of the connection is not NOTHING_CONNECTING, it displays the connection menu.
 *
 * @return Returns 0 if the main menu is successfully created, and 1 if there is an error in printing the sprites or displaying the connection menu.
 */
int criar_main_menu();

/**
 * @brief Manages the game state.
 *
 * Sets up the game by clearing the graphic buffer and printing the background. Depending on the game state, it manages player hands, 
 * displays the score board and the trump card. Handles card selection, card grabbing, and card display based on the round and grab states.
 *
 * @return 0 on success, 1 on error.
 */
int criar_jogo();


/**
 * @brief Handles the creation of a mouse in the game.
 *
 * Checks the current state of the game and the connection, and based on these states, performs different actions.
 * Checks for collisions and changes the state of the game accordingly.
 * Handles the printing of the mouse sprite, and returns an error if the printing fails.
 *
 * @param x The x-coordinate where the mouse should be created.
 * @param y The y-coordinate where the mouse should be created.
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error in printing the mouse sprite.
 */
int criar_rato(int x, int y);


/**
 * @brief Creates a pause menu in the game.
 *
 * Depending on the current state of the game, it creates the hands of the players.
 * It then displays the trump card and prints the pause menu sprite.
 * Depending on the current state of the pause menu, it prints the buttons with different states (normal, selected, pressed).
 * If there is an error in printing any of the sprites, it prints an error message to stderr and returns 1.
 *
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error in printing any of the sprites.
 */
int criar_menu_pausa();


/**
 * @brief Displays a score board in the game.
 *
 * Prints the score board sprite. If there is an error in printing the sprite, it prints an error message to stderr and returns 1.
 *
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error in printing the sprite.
 */
int criar_score_board();



/**
 * @brief Creates the hand of player 1.
 *
 * @param playerHand A pointer to the array of cards that represents the player's hand.
 * @param numCards The number of cards in the player's hand.
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error.
 */
int criar_mao_jogador_1(Card * playerHand, int numCards);



/**
 * @brief Creates the hand of player 2.
 *
 * @param playerHand A pointer to the array of cards that represents the player's hand.
 * @param numCards The number of cards in the player's hand.
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error.
 */
int criar_mao_jogador_2(Card * playerHand, int numCards);



/**
 * @brief Creates the hand of player 3.
 *
 * @param playerHand A pointer to the array of cards that represents the player's hand.
 * @param numCards The number of cards in the player's hand.
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error.
 */
int criar_mao_jogador_3(Card * playerHand, int numCards);



/**
 * @brief Creates the hand of player 4.
 *
 * @param playerHand A pointer to the array of cards that represents the player's hand.
 * @param numCards The number of cards in the player's hand.
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error.
 */
int criar_mao_jogador_4(Card * playerHand, int numCards);



/**
 * @brief Displays the card for player 1.
 *
 * Prints the sprite of the card. If there is an error in printing the sprite, it prints an error message to stderr and returns 1.
 *
 * @param card The card to be displayed.
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error in printing the sprite.
 */

int display_card_jogador_1(Card card);


/**
 * @brief Displays the card for player 2.
 * Prints the sprite of the card. If there is an error in printing the sprite, it prints an error message to stderr and returns 1.
 * @param card The card to be displayed.
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error in printing the sprite.
*/
int display_card_jogador_2(Card card);


/**
 * @brief Displays the card for player 3.
 *
 * Prints the sprite of the card. If there is an error in printing the sprite, it prints an error message to stderr and returns 1.
 *
 * @param card The card to be displayed.
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error in printing the sprite.
 */
int display_card_jogador_3(Card card);


/**
 * @brief Displays the card for player 4.
 *
 * Prints the sprite of the card. If there is an error in printing the sprite, it prints an error message to stderr and returns 1.
 *
 * @param card The card to be displayed.
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error in printing the sprite.
 */
int display_card_jogador_4(Card card);


/**
 * @brief Displays the trump card.
 *
 * Prints the sprite of the trump card. If there is an error in printing the sprite, it prints an error message to stderr and returns 1.
 *
 * @param card The card to be displayed.
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error in printing the sprite.
 */
int display_trump_card(Card card);


/**
 * @brief Creates a frame for a card.
 *
 * If no card is selected by player 1, the function returns 0.
 * Calculates the space needed for the frame and the x and y coordinates where the frame should be created.
 * Calls the molduraCarta function to create the frame. If there is an error in creating the frame, it prints an error message to stderr and returns 1.
 *
 * @param color The color of the frame to be created.
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error in creating the frame.
 */
int criarMolduraCarta(int color);


/**
 * @brief Displays the cards of all players.
 *
 * If player 1 has played, it displays player 1's card.
 * If player 2 has played, it displays player 2's card.
 * If player 3 has played, it displays player 3's card.
 * If player 4 has played, it displays player 4's card.
 */
void displayCards();



/**
 * @brief Displays a drag frame in the game.
 *
 * Calls the molduraCarta function to create a drag frame. If there is an error in creating the frame, it prints an error message to stderr and returns 1.
 *
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error in creating the frame.
 */
int displayDragFrame();



/**
 * @brief Handles the grabbing of a card by player 1.
 *
 * If the grab process is ongoing, it calculates the x and y coordinates of the grabbed card and stores the current mouse coordinates.
 * Iterates over the cards in player 1's hand. If a card is the selected card, it is set as the grabbed card.
 * If the grab process is not ongoing, it checks if the mouse has moved. If it has, it updates the x and y coordinates of the grabbed card and stores the new mouse coordinates.
 * Prints the sprite of the grabbed card. If there is an error in printing the sprite, prints an error message to stderr and returns 1.
 *
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error in printing the sprite.
 */
int grabCard();



/**
 * @brief Creates the hand of grabbed cards for player 1.
 *
 * Calculates the space needed for the cards. Iterates over the grabbed cards and prints the sprite of each card, excludes the grabbed card.
 * For each card, it prints the sprite of the card. If there is an error in printing the sprite, it prints an error message to stderr and returns 1.
 *
 * @return int Returns 0 if the function executes successfully, and 1 if there is an error.
 */
int criar_mao_grabbed();


/**
 * @brief Creates the game for player 1.
 *
 * Manages game state, player hands, card grabbing, and card playability. Displays game elements and handles errors.
 *
 * @return int Returns 0 if successful, and 1 if there is an error.
 */
int criar_jogo_P1();

/**
 * @brief Creates the game for player 2.
 *
 * Similar to criar_jogo_P1, but tailored for player 2. Manages game state, player hands, card grabbing, and card playability. Displays game elements and handles errors.
 *
 * @return int Returns 0 if successful, and 1 if there is an error.
 */
int criar_jogo_P2();


/**
 * @brief Displays the cards for a multiplayer game.
 *
 * Depending on the current game state, it checks if a player has played. If so, it displays the player's card. 
 * If a card is selected by a player, it also displays that card.
 *
 * @note The function handles two game states: MULTIPLAYER_P1 and MULTIPLAYER_P2.
 */
void displayCards_MUL();

/**
 * @brief Creates the hand of grabbed cards for player 2.
 *
 * Calculates the space needed for the cards and then iterates over the number of cards in player 3's hand. 
 * It prints each card using the printar_form_xpm_sprite function. If there's an error in printing, it logs the error and returns 1.
 *
 * @return int Returns 0 if successful, and 1 if there is an error.
 */
int criar_mao_grabbed_P2();

/**
 * @brief Handles the card grabbing process for player 2.
 *
 * If the grab process is ongoing, it calculates the card's position and stores the current mouse coordinates. 
 * It then iterates over the player's hand, storing the grabbed card and the remaining cards separately.
 * If the grab process is not ongoing, it updates the card's position based on the mouse movement.
 * Prints the grabbed card using the printar_form_xpm_sprite function. If there's an error in printing, it logs the error and returns 1.
 *
 * @return int Returns 0 if successful, and 1 if there is an error.
 */
int grabCard_P2();



/**
 * @brief Creates a frame around the selected card for player 2.
 *
 * If no card is selected, it returns 0. Otherwise, it calculates the position of the selected card and calls the molduraCarta function to create a frame of the specified color around the card.
 * If there's an error in creating the frame, it logs the error and returns 1.
 *
 * @param color The color of the frame to be created.
 * @return int Returns 0 if successful, and 1 if there is an error.
 */
int criarMolduraCarta_P2(int color);


/**
 * @brief Displays the current time at (x, y).
 *
 * Converts time to an array of digits, prints each digit as a sprite. If printing fails, logs the error and returns 1.
 * Adjusts x-coordinate for each digit and adds extra space after every two digits.
 *
 * @param x The x-coordinate to start displaying time.
 * @param y The y-coordinate to start displaying time.
 * @return int Returns 0 if successful, 1 if an error occurs.
 */
int displayTime(int x, int y);


/**
 * @brief Displays the connection menu.
 *
 * Prints the main menu and the cancel button, depending on the current connection state. 
 * If printing fails, logs the error and returns 1.
 *
 * @return int Returns 0 if successful, 1 if an error occurs.
 */
int display_connection_menu();


/**
 * @brief Displays the invitation menu.
 *
 * Prints the menu and the accept and decline buttons, depending on the current invitation state. 
 * If printing fails, logs the error and returns 1.
 *
 * @return int Returns 0 if successful, 1 if an error occurs.
 */
int display_invitation_menu();


/**
 * @brief Displays the select top or bottom card menu.
 *
 * Prints the menu and the top and bottom buttons, depending on the current select card state. 
 * If printing fails, logs the error and returns 1.
 *
 * @return int Returns 0 if successful, 1 if an error occurs.
 */
int displaySelectCard();


/**
 * @brief Displays the split deck menu.
 *
 * Prints the menu and the split button, depending on the current split state. 
 * If printing fails, logs the error and returns 1.
 *
 * @return int Returns 0 if successful, 1 if an error occurs.
 */
int displaySplitDeck();


/**
 * @brief Displays the time tracking
 *
 * Prints the elapsed time in minutes at the end of the game. If printing fails, logs the error and returns 1.
 *
 * @return int Returns 0 if successful, 1 if an error occurs.
 */
int displayTimeTracker();


/**
 * @brief Slider for the deck split.
 * 
 * If the mouse is clicked, it checks if the mouse is over the split button. If it is, it changes the split state to SPLIT_SELECTED.
 * .
 */
void grabSquare();

#endif // COMPOSER_H

