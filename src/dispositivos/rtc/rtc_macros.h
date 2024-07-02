#ifndef _LCOM_RTC_MACROS_H_
#define _LCOM_RTC_MACROS_H_

#include <lcom/lcf.h>

#define RTC_IRQ 8
#define RTC_IN_ADDR_REG 0x70
#define RTC_OUT_ADDR_REG 0x71

#define SECONDS_BIT     0
#define MINUTES_BIT     2
#define HOURS_BIT       4
#define DAY_BIT         7
#define MONTH_BIT       8
#define YEAR_BIT        9
#define UPDATE_BIT      10
#define COUNTING_BIT    11

#define UPDATE_MODE     BIT(7)
#define BINARY_MODE     BIT(2)

#define BINARY(number)  (((number >> 4) * 10) + ((number & 0xF)))

#endif 
