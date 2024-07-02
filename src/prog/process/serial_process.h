#ifndef SERIAL_PROCESS_H
#define SERIAL_PROCESS_H

#include "lcom/lcf.h"
#include "../functions/composer.h"
#include "../../dispositivos/sp/sp.h"
#include "../../dispositivos/rtc/rtc.h"
#include "../game_rules/rules.h"


/**
 * @brief Processes serial inputs during different game states.
 * 
 * Handles the processing of serial inputs during different game states. Checks the current state of the game and 
 * performs actions based on the state. Handles the actions to be performed in the main menu, multiplayer mode, and other states.
 */
void serial_process();


/**
 * @brief Processes serial inputs in the main menu.
 * 
 * Handles the processing of serial inputs in the main menu. Checks the value of the serial port and performs actions based on the value.
 * Handles the actions to be performed when the player starts a multiplayer session, accepts an invite, or disconnects from the session.
 */
void serial_process_main_menu();


/**
 * @brief Processes serial inputs for Player 1 during the game.
 * 
 * Handles the processing of serial inputs for Player 1 during the game. Checks the received value and 
 * performs actions based on the value. Handles the actions to be performed when Player 2 disconnects, the game is initialized, 
 * and when Player 3 plays a card.
 */
void serial_process_P1();


/**
 * @brief Processes serial inputs for Player 2 during the game.
 * 
 * Handles the processing of serial inputs for Player 2 during the game. Checks the received value and 
 * performs actions based on the value. Handles the actions to be performed when Player 1 disconnects, the game is initialized, 
 * and when Player 1 plays a card.
 */
void serial_process_P2();

#endif // SERIAL_PROCESS_H
