#ifndef __HANDLER_H
#define __HANDLER_H

void (timer_int_handler)();

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "i8042.h"
#include "teclado/kbc.h"
#include "rato/mouse.h"
#include "utils.h"
#include "sp/sp_macros.h"
#include "sp/sp.h"
#include "sp/fila_sp.h"

/**
 * @brief Keyboard interrupt handler.
 * 
 * Reads the output of the Keyboard Controller.
 * 
 * @return Returns 0 on success, 1 on error.
 */
void (keyboard_ih)();

/**
 * @brief Handles Mouse interrupts.
 * 
 * Reads the output of the Mouse Controller.
 */
void (mouse_interrupt_handler)();

/**
 * @brief Handles the serial port interrupts.
 * @return Returns 0 on success, 1 otherwise.
 */
int (sp_interrupt_handler)();



#endif
