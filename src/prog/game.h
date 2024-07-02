#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <stdint.h>

#include "../dispositivos/grafica/grafica.h"
#include "../dispositivos/rato/mouse.h"
#include "../dispositivos/timer/timer.h"
#include "../dispositivos/rtc/rtc.h"
#include "../dispositivos/sp/sp.h"
#include "../dispositivos/interrupts.h"
#include "../dispositivos/handler.h"

#include "functions/composer.h"
#include "functions/collision.h"
#include "game_rules/rules.h"

#include "process/teclado_process.h"
#include "process/rato_process.h"
#include "process/timer_process.h"
#include "process/serial_process.h"


/**
 * @brief Main game loop handling hardware interrupts.
 * 
 * Main game loop that handles hardware interrupts from the timer, keyboard, mouse, and serial port.
 * Initializes and subscribes to the necessary hardware interrupts, processes the interrupts, and unsubscribes from the interrupts at the end.
 * Also handles error checking for each operation and returns an error code if any operation fails.
 */
int (loop_interrupcoes)();


/**
 * @brief Waits for 60 seconds during a pause in the game.
 * 
 * Increments a counter during a pause in the game. When the counter reaches the frames per second (fps) value,
 * resets the counter and returns 1, effectively waiting for 60 seconds. If the game is not paused, returns 0.
 */
int (wait_60_seconds)();
