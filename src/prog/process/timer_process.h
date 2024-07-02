#ifndef TIMER_PROCESS_H
#define TIMER_PROCESS_H

#include "../functions/composer.h"
#include "../game_rules/rules.h"
#include "../../dispositivos/sp/sp.h"
#include "../../dispositivos/rtc/rtc.h"
#include "../functions/aux_func.h"


/**
 * @brief Processes game timer events and updates game states.
 * 
 * Handles the game timer events based on the current game state. Processes the main menu timer, 
 * game timer, multiplayer game timers, and mouse events. It also handles the creation of the mouse and the copying 
 * of the buffer set drawing to the graphic buffer. Processes game rounds for both single and multiplayer modes.
 * 
 * @param teclado_on Pointer to the keyboard status.
 * @param rato_on Pointer to the mouse status.
 * @param mouse_x X-coordinate of the mouse.
 * @param mouse_y Y-coordinate of the mouse.
 * @return int Returns 0 on successful execution, 1 if an error occurs.
 */
int process_timer(int *teclado_on, int *rato_on, int mouse_x, int mouse_y);



/**
 * @brief Processes the main menu timer events and updates game states.
 * 
 * Handles the main menu timer events. If the previous game state was not MAIN_MENU, 
 * sets the current game state to MAIN_MENU, the main menu state to WAIT, and the game play state to NOTHING_GAME_PLAY.
 * Also handles the creation of the main menu.
 * 
 * @return int Returns 0 on successful execution, 1 if an error occurs in the criar_main_menu function.
 */
int process_main_menu_timer();


/**
 * @brief Processes the game timer events and updates game states.
 * 
 * Handles the game timer events. If the previous game state was not GAME, 
 * sets the current game state to GAME, the main menu state to NOTHING_MAIN_MENU, and the game play state to GAME_INIT.
 * Also handles the initialization of the game, the start of the game, the creation of the game, and the pause menu.
 * 
 * @return int Returns 0 on successful execution, 1 if an error occurs in the criar_jogo or criar_menu_pausa functions.
 */
int process_game_timer();


/**
 * @brief Processes a round of the game.
 * 
 * handles the processing of a game round. Determines the winner of the round, 
 * resets the selected cards and the player who played, and updates the number of cards, turn, and round suit.
 * It also handles the end of the round and the transitions between players, including pauses and waits.
 */
void process_round();


/**
 * @brief Processes the display of the game based on the current round.
 * 
 * Handles the display of the game based on the current round. Processes the display for each player's turn,
 * including the selection of the card, the removal of the card from the player's hand, and the setting of the round suit.
 */
void process_display();


/**
 * @brief Processes the game timer events and updates game states for Player 1 in multiplayer mode.
 * 
 * Handles the game timer events for Player 1 in multiplayer mode. If the previous game state was not MULTIPLAYER_P1, 
 * it sets the current game state to MULTIPLAYER_P1, the main menu state to NOTHING_MAIN_MENU, and the game play state to GAME_INIT.
 * Handles the initialization of the P1 game, the start of the game, the creation of the game, and the pause menu.
 * 
 * @return int Returns 0 on successful execution, 1 if an error occurs in the criar_jogo_P1 or criar_menu_pausa functions.
 */
int process_game_timer_P1();


/**
 * @brief Processes the game timer events and updates game states for Player 2 in multiplayer mode.
 * 
 * This function handles the game timer events for Player 2 in multiplayer mode. If the previous game state was not MULTIPLAYER_P2, 
 * it sets the current game state to MULTIPLAYER_P2, the main menu state to NOTHING_MAIN_MENU, and the game play state to GAME_INIT.
 * Handles the initialization of the P2 game, the start of the game, the creation of the game, and the pause menu.
 * 
 * @return int Returns 0 on successful execution, 1 if an error occurs in the criar_jogo_P2 or criar_menu_pausa functions.
 */
int process_game_timer_P2();


/**
 * @brief Processes the round in a multiplayer game.
 * 
 * Handles the processing of a round in a multiplayer game. Checks if the turn is 5, indicating the end of a round, 
 * and then processes the round to determine the winner. Also handles the resetting of the game state at the end of a round.
 * If the turn is not 5, processes the round for each player, waiting for 60 seconds before moving to the next player.
 */
void process_round_MUL();


/**
 * @brief Processes the display for Player 1 in a multiplayer game.
 * 
 * Handles the display processing for Player 1 in a multiplayer game. Checks the current round and performs 
 * actions based on the player whose turn it is. For Player 1, it handles the display of the selected card and the removal of the card 
 * from the player's hand. For Players 2 and 4, it handles the display of the selected card by the bot and the removal of the card 
 * from the bot's hand. For Player 3, it handles the start and finish of the single player mode.
 */
void process_display_P1();


/**
 * @brief Processes the display for Player 2 in a multiplayer game.
 * 
 * Handles the display processing for Player 2 in a multiplayer game. Checks the current round and performs 
 * actions based on the player whose turn it is. For Player 1, it handles the start and finish of the single player mode. 
 * For Players 2, 3, and 4, it handles the display of the selected card and the removal of the card from the player's hand.
 */
void process_display_P2();

#endif // TIMER_PROCESS_H
