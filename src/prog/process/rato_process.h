#ifndef RATO_PROCESS_H
#define RATO_PROCESS_H

#include "../functions/composer.h"
#include "../../dispositivos/i8042.h"
#include "../../dispositivos/sp/sp.h"
#include "../functions/composer.h"
#include "../functions/collision.h"
#include "../functions/aux_func.h"

#include "../game_rules/rules.h"


/**
 * @brief Processes mouse inputs during different game states.
 * 
 * Handles the processing of mouse inputs during different game states. Checks the current state of the game and 
 * performs actions based on the state and the mouse coordinates. Handles the actions to be performed when different buttons are clicked, 
 * and the navigation between different states based on mouse inputs.
 * 
 * @param mouse_x The x-coordinate of the mouse cursor.
 * @param mouse_y The y-coordinate of the mouse cursor.
 */
void process_rato(int mouse_x, int mouse_y);


/**
 * @brief Processes mouse inputs for card grab and drop actions.
 * 
 * Handles the processing of mouse inputs for card grab and drop actions. Checks if a card grab collision has occurred 
 * and performs actions based on the current state of the game. Handles the actions to be performed when a card is dropped in the multiplayer mode.
 * 
 * @param mouse_x The x-coordinate of the mouse cursor.
 * @param mouse_y The y-coordinate of the mouse cursor.
 * @param rato_on Pointer to the variable that indicates if the mouse is on.
 */
void process_rato_grab_drop(int mouse_x, int mouse_y, int * rato_on);

/**
 * @brief Processes mouse inputs for Player 1 during the game.
 * 
 * Handles the processing of mouse inputs for Player 1 during the game. Checks the current state of the game and 
 * performs actions based on the state and the mouse coordinates. Handles the actions to be performed when different buttons are clicked in the pause menu, 
 * and the selection of cards by Player 1.
 * 
 * @param mouse_x The x-coordinate of the mouse cursor.
 * @param mouse_y The y-coordinate of the mouse cursor.
 */
void process_rato_P1(int mouse_x, int mouse);

/**
 * @brief Processes mouse inputs for Player 2 during the game.
 * 
 * Handles the processing of mouse inputs for Player 2 during the game. Checks the current state of the game and 
 * performs actions based on the state and the mouse coordinates. Handles the actions to be performed when different buttons are clicked in the pause menu, 
 * and the selection of cards by Player 2.
 * 
 * @param mouse_x The x-coordinate of the mouse cursor.
 * @param mouse_y The y-coordinate of the mouse cursor.
 */
void process_rato_P2(int mouse_x, int mouse);


/**
 * @brief Processes mouse inputs during the connection phase.
 * 
 * Handles the processing of mouse inputs during the connection phase. Checks if the cancel button has been clicked 
 * and performs actions based on the mouse coordinates. Handles the actions to be performed when the cancel button is clicked.
 * 
 * @param mouse_x The x-coordinate of the mouse cursor.
 * @param mouse_y The y-coordinate of the mouse cursor.
 */
void process_rato_connection(int mouse_x, int mouse_y);


/**
 * @brief Processes mouse inputs during the invitation phase.
 * 
 * Handles the processing of mouse inputs during the invitation phase. Checks if the accept or decline buttons have been clicked 
 * and performs actions based on the mouse coordinates. Handles the actions to be performed when the accept or decline buttons are clicked.
 * 
 * @param mouse_x The x-coordinate of the mouse cursor.
 * @param mouse_y The y-coordinate of the mouse cursor.
 */
void process_rato_invitation(int mouse_x, int mouse_y);

void process_rato_get_trump(int mouse_x, int mouse_y);

void process_rato_slide(int mouse_x, int mouse_y);
void grabSquareSlide(int mouse_x, int mouse_y);

void process_rato_time_tracker(int mouse_x, int mouse_y);

#endif // RATO_PROCESS_H
