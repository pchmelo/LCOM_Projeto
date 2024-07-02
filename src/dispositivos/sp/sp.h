#ifndef __SP_H_
#define __SP_H_

#include <lcom/lcf.h>
#include "sp_macros.h"
#include "fila_sp.h"
#include "../utils.h"
#include "../aux_dispositivos.h"

/**
 * @brief Exits the serial port.
 */
void (exit_serial_port)();

/**
 * @brief Sends a byte through the serial port.
 * @param byte The byte to send.
 * @return Returns 0 on success, 1 otherwise.
 */
int (enviar_byte)(uint8_t byte);

/**
 * @brief Receives a byte from the serial port.
 * @return Returns 0 on success, 1 otherwise.
 */
int (receber_byte)();


/**
 * @brief Gets the value from the serial port.
 */
void (get_value)();


#endif 
