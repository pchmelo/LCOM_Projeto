#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "../i8042.h"
#include "../teclado/kbc.h"



/**
 * @brief Synchronizes the bytes received from the Mouse.
 * 
 * Ensures the first byte of the packet has BIT(3) set.
 */
void (mouse_sync_bytes)();

/**
 * @brief Converts the array of bytes into a packet structure.
 * 
 * Transforms the mouse_bytes array into a mouse_packet structure.
 */
void (mouse_bytes_to_packet)();

/**
 * @brief Writes a command directly to the Mouse.
 * 
 * @param command The command byte to write.
 * @return Returns 0 on success, 1 on error.
 */
int (write_mouse)(uint8_t command);


#endif
