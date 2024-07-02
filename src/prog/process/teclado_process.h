#ifndef TECLADO_PROCESS_H
#define TECLADO_PROCESS_H


#include "../functions/composer.h"
#include "../../dispositivos/i8042.h"
#include "../../dispositivos/sp/sp.h"
#include "../game_rules/rules.h"
#include "../game.h"
#include "../functions/aux_func.h"


/**
 * @brief Processes keyboard inputs based on the current game state.
 * 
 * Handles the processing of keyboard inputs based on the current game state. If the game is in the main menu, 
 * processes the keyboard inputs for the main menu, connection, or invitation based on the current connection and invitation states. 
 * If the game is in the game state or multiplayer mode, it processes the keyboard inputs for the game.
 * 
 * @param scancode The scancode of the key pressed.
 * @param teclado_on Pointer to the variable that indicates if the keyboard is on.
 * @param rato_on Pointer to the variable that indicates if the mouse is on.
 */
void process_teclado(uint8_t scancode, int *teclado_on, int *rato_on);

/**
 * @brief Processes keyboard inputs in the main menu.
 * 
 * Handles the processing of keyboard inputs in the main menu. Checks the scancode of the key pressed and 
 * performs actions based on the scancode and the current state of the main menu. Handles the navigation between different 
 * buttons in the main menu and the actions to be performed when certain keys are pressed.
 * 
 * @param scancode The scancode of the key pressed.
 * @param teclado_on Pointer to the variable that indicates if the keyboard is on.
 * @param rato_on Pointer to the variable that indicates if the mouse is on.
 */
void process_main_menu_teclado(uint8_t scancode, int *teclado_on, int *rato_on);


/**
 * @brief Processes keyboard inputs during the game.
 * 
 * Handles the processing of keyboard inputs during the game. Checks the scancode of the key pressed and 
 * performs actions based on the scancode and the current state of the game. Handles the navigation between different 
 * buttons in the pause menu and the actions to be performed when certain keys are pressed. Also processes 
 * the selection of cards in the game or multiplayer mode.
 * 
 * @param scancode The scancode of the key pressed.
 * @param teclado_on Pointer to the variable that indicates if the keyboard is on.
 * @param rato_on Pointer to the variable that indicates if the mouse is on.
 */
void process_game_teclado(uint8_t scancode, int *teclado_on, int *rato_on);



/**
 * @brief Processes the selection of cards for Player 1.
 * 
 * Handles the processing of keyboard inputs for the selection of cards for Player 1. Checks the scancode of the key pressed and 
 * performs actions based on the scancode. Handles the navigation between different cards using arrow keys and the action 
 * to be performed when the ENTER key is pressed.
 * 
 * @param scancode The scancode of the key pressed.
 * @param teclado_on Pointer to the variable that indicates if the keyboard is on.
 * @param rato_on Pointer to the variable that indicates if the mouse is on.
 * @param max_cards The maximum number of cards that can be selected.
 */
void process_select_card_P1(uint8_t scancode, int *teclado_on, int *rato_on, int max_cards);


/**
 * @brief Processes the selection of cards for Player 2.
 * 
 * Handles the processing of keyboard inputs for the selection of cards for Player 2. Checks the scancode of the key pressed and 
 * performs actions based on the scancode. Handles the navigation between different cards using arrow keys and the action 
 * to be performed when the ENTER key is pressed.
 * 
 * @param scancode The scancode of the key pressed.
 * @param teclado_on Pointer to the variable that indicates if the keyboard is on.
 * @param rato_on Pointer to the variable that indicates if the mouse is on.
 * @param max_cards The maximum number of cards that can be selected.
 */
void process_select_card_P2(uint8_t scancode, int *teclado_on, int *rato_on, int max_cards);


/**
 * @brief Processes keyboard inputs during the connection phase.
 * 
 * Handles the processing of keyboard inputs during the connection phase. Checks the scancode of the key pressed and 
 * performs actions based on the scancode and the current state of the connection. Handles the actions to be performed when certain keys are pressed, 
 * and the navigation between different states using arrow keys.
 * 
 * @param scancode The scancode of the key pressed.
 * @param teclado_on Pointer to the variable that indicates if the keyboard is on.
 * @param rato_on Pointer to the variable that indicates if the mouse is on.
 */
void process_connection_teclado(uint8_t scancode, int *teclado_on, int *rato_on);


/**
 * @brief Processes keyboard inputs during the invitation phase.
 * 
 * Handles the processing of keyboard inputs during the invitation phase. Checks the scancode of the key pressed and 
 * performs actions based on the scancode and the current state of the invitation. Handles the actions to be performed when certain keys are pressed, 
 * and the navigation between different states using arrow keys.
 * 
 * @param scancode The scancode of the key pressed.
 * @param teclado_on Pointer to the variable that indicates if the keyboard is on.
 * @param rato_on Pointer to the variable that indicates if the mouse is on.
 */
void process_invitation_teclado(uint8_t scancode, int *teclado_on, int *rato_on);

void process_prepare_round_trump_teclado(uint8_t scancode, int *teclado_on, int *rato_on);

void process_prepare_round_slide_teclado(uint8_t scancode, int *teclado_on, int *rato_on);

void process_time_tracker_teclado(uint8_t scancode, int *teclado_on, int *rato_on);

#endif // TECLADO_PROCESS_H
