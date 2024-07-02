#ifndef __UTILS_H_
#define __UTILS_H_

#include <lcom/lcf.h>
#include <stdint.h>


/**
 * @brief Structure to hold the serial port queue data.
 */
typedef struct {
  int* valores; /**< Array of values in the queue. */
  unsigned capacidade; /**< Maximum capacity of the queue. */
  int inicio; /**< Start index of the queue. */
  int fim; /**< End index of the queue. */
  int tamanho; /**< Current size of the queue. */
} fila_sp;


/**
 * @brief Gets the least significant byte (LSB) of a 16-bit value.
 * 
 * @param val The 16-bit value.
 * @param lsb Pointer to store the LSB.
 * @return Returns 0 on success, 1 if the pointer is NULL.
 */
int (util_get_LSB)(uint16_t val, uint8_t *lsb);

/**
 * @brief Gets the most significant byte (MSB) of a 16-bit value.
 * 
 * @param val The 16-bit value.
 * @param msb Pointer to store the MSB.
 * @return Returns 0 on success, 1 if the pointer is NULL.
 */
int (util_get_MSB)(uint16_t val, uint8_t *msb);

/**
 * @brief Reads a byte from a specified port.
 * 
 * @param port The port to read from.
 * @param value Pointer to store the read value.
 * @return Returns 0 on success, 1 if the pointer is NULL or if the sys_inb function fails.
 */
int (util_sys_inb)(int port, uint8_t *value);


#endif
