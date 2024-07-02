#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <lcom/lcf.h>
#include "rtc_macros.h"
#include "../util.h"
#include "../aux_dispositivos.h"

/**
 * @brief Structure to hold RTC time data.
 */
typedef struct {
    uint8_t seconds; /**< Seconds part of the time. */
    uint8_t minutes; /**< Minutes part of the time. */
    uint8_t hours;   /**< Hours part of the time. */
} rtc_struct;

/**
 * @brief Reads and sets the RTC time.
 * @return Returns 0 on success, 1 otherwise.
 */
int (rtc_read_set)();


/**
 * @brief Gets the current time from the RTC.
 * @return Returns 0 on success, 1 otherwise.
 */
int (rtc_get_time)(rtc_struct *rtc_time_dis);


#endif 
