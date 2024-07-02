#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include <lcom/lcf.h>
#include "timer/i8254.h"
#include <stdint.h>
#include <minix/sysutil.h>
#include "i8042.h"
#include "teclado/kbc.h"
#include "util.h"
#include "rtc/rtc_macros.h"
#include "sp/sp_macros.h"
#include "sp/fila_sp.h"
#include "sp/sp.h"
#include "grafica/grafica.h"

/**
 * @brief Subscribes and enables Timer 0 interrupts.
 * 
 * @param bit_no Pointer to store the bit number to set in the mask returned upon an interrupt.
 * @return Returns 0 on success, 1 on error.
 */
int (timer_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes Timer 0 interrupts.
 * 
 * @return Returns 0 on success, 1 on error.
 */
int (timer_unsubscribe_int)();

/**
 * @brief Subscribes and enables Keyboard interrupts.
 * 
 * @param bit_no Pointer to store the bit number to set in the mask returned upon an interrupt.
 * @return Returns 0 on success, 1 on error.
 */
int (keyboard_subscribe_interrupt)(uint8_t *bit_no);

/**
 * @brief Unsubscribes Keyboard interrupts.
 * 
 * @return Returns 0 on success, 1 on error.
 */
int (keyboard_unsubscribe_interrupt)();



/**
 * @brief Subscribes and enables Mouse interrupts.
 * 
 * @param bit_no Pointer to store the bit number to set in the mask returned upon an interrupt.
 * @return Returns 0 on success, 1 on error.
 */
int (mouse_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes Mouse interrupts.
 * 
 * @return Returns 0 on success, 1 on error.
 */
int (mouse_unsubscribe_int)();

/**
 * @brief Subscribes to serial port interrupts.
 * @param bit_no Pointer to store the bit number to set in the mask returned upon an interrupt.
 * @return Returns 0 on success, 1 otherwise.
 */
int (serial_port_subscribe_interrupt)(uint8_t *bit_no);

/**
 * @brief Unsubscribes from serial port interrupts.
 * @return Returns 0 on success, 1 otherwise.
 */
int (serial_port_unsubscribe_interrupt)();

/**
 * @brief Starts the serial port.
 * @return Returns 0 on success, 1 otherwise.
 */
int (start_serial_port)();

/**
 * @brief Sets Minix in graphic mode.
 * @param submode The submode to set.
 * @return Returns 0 on success, 1 otherwise.
 */
int (modo_grafico)(uint16_t submode);

/**
 * @brief Creates a physical and virtual buffer for the frame.
 * @param mode The mode to set.
 * @return Returns 0 on success, 1 otherwise.
 */
int (const_buffer_frame)(uint16_t mode);

/**
 * @brief Cleans the serial port interrupts.
 * @return Returns 0 on success, 1 otherwise.
 */
int (sp_clean_interrupts)();



#endif 

