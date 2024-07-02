#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>
#include "i8254.h"



/**
 * @brief Changes the operating frequency of a timer.
 * 
 * @param timer The timer to change the frequency of.
 * @param freq The frequency to set.
 * @return Returns 0 on success, 1 on error.
 */
int (timer_set_frequency)(uint8_t timer, uint32_t freq);


