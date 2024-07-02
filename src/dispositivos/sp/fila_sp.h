#ifndef __FILA_SP_H_
#define __FILA_SP_H_

#include <lcom/lcf.h>
#include "sp_macros.h"
#include "../aux_dispositivos.h"
#include "../utils.h"

#define MAX_SIZE 100




/**
 * @brief Creates a new serial port queue.
 * @return Returns a pointer to the created queue.
 */
fila_sp* (criar_fila_sp)();


/**
 * @brief Inserts a value into the serial port queue.
 * 
 * Checks if the data is available by using the status parameter. 
 * If the data is available, it calls the colocar_fila_sp function to insert the value into the queue.
 * 
 * @param f Pointer to the queue. This is the queue where the value will be inserted.
 * @param rbr The value to insert. This is the data that will be inserted into the queue.
 * @param status The status of the serial port. This is used to check if the data is available for insertion.
 * @return Returns 0 if the value was successfully inserted into the queue, 1 otherwise.
 */
int (inserir_fila_sp)(fila_sp* f, int rbr, uint8_t status);



/**
 * @brief Clears the serial port queue.
 * @param f Pointer to the queue.
 */
void (limpar_fila_sp)(fila_sp* f);

/**
 * @brief Pops a value from the serial port queue.
 * @param f Pointer to the queue.
 * @return Returns the popped value.
 */
int (pop_fila_sp)(fila_sp* f);



#endif 
