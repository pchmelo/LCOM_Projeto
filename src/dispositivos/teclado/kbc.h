#ifndef _LCOM_KBC_H_
#define _LCOM_KBC_H_

#include <minix/sysutil.h>
#include "../i8042.h"
#include <lcom/lcf.h>
#include "util.h"
#include "../aux_dispositivos.h"




/**
 * @brief Reads the output of the Keyboard Controller.
 * 
 * @param port The port to read from.
 * @param output Pointer to store the output.
 * @param mouse Flag to indicate if the output is from a mouse.
 * @return Returns 0 on success, 1 on error.
 */
int (ler_output_KBC)(uint8_t port, uint8_t *output, uint8_t mouse);

/**
 * @brief Writes a command byte to the Keyboard Controller.
 * 
 * @param port The port to write to.
 * @param commandByte The command byte to write.
 * @return Returns 0 on success, 1 on error.
 */
int (write_command_KBC)(uint8_t port, uint8_t commandByte);


#endif 
