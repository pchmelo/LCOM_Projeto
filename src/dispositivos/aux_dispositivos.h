#ifndef __AUX_DISPOSITIVOS_H
#define __AUX_DISPOSITIVOS_H

#include <lcom/lcf.h>
#include "grafica/grafica.h"
#include "i8042.h"
#include "sp/sp_macros.h"
#include "sp/fila_sp.h"
#include "utils.h"
#include "rtc/rtc_macros.h"
#include "timer/i8254.h"

/**
 * @brief Draws a pixel based on the received parameters.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param cor The color of the pixel.
 * @return Returns 0 on success, 1 otherwise.
 */
int (desenhar_pixel)(uint16_t x, uint16_t y, uint32_t cor);

/**
 * @brief Reads the status of the Keyboard Controller.
 * 
 * @param status Pointer to store the status.
 * @return Returns 0 on success, 1 on error.
 */
int (ler_status_KBC)(uint8_t* status);

/**
 * @brief Reads the status of the serial port.
 * @param status Pointer to store the status.
 * @return Returns 0 on success, 1 otherwise.
 */
int (serial_status)(uint8_t* status);

/**
 * @brief Places a value into the serial port queue.
 * 
 * Inserts a value into the queue at the position indicated by the end index (fim). 
 * Increments the end index and the size of the queue. 
 * If the queue is full (i.e., the size of the queue is equal to its capacity), the function returns 1 to indicate an error.
 * 
 * @param f Pointer to the queue. This is the queue where the value will be placed.
 * @param valor The value to place. This is the data that will be placed into the queue.
 * @return Returns 0 if the value was successfully placed into the queue, 1 if the queue is full.
 */
int colocar_fila_sp(fila_sp* f, int valor);

/**
 * @brief Reads the output of the RTC based on the sent command.
 * @param data Pointer to store the read data.
 * @param comando The command to send to the RTC.
 * @return Returns 0 on success, 1 otherwise.
 */
int (rtc_read_output)(uint8_t *data, uint8_t comando);

/**
 * @brief Reads the input timer configuration via Read-Back command.
 * 
 * @param timer The timer to get the configuration from.
 * @param st Pointer to store the configuration.
 * @return Returns 0 on success, 1 on error.
 */
int (timer_get_conf)(uint8_t timer, uint8_t *st);



#endif
