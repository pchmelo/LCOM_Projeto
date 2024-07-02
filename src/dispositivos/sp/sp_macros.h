#ifndef __SP_MACROS_H_
#define __SP_MACROS_H_

#include <lcom/lcf.h>

#define   IRQ_SP       BIT(7)
#define   PORT_COM1    4

#define   UART_BASE    0x3F8
#define   UART_LSR     0x3FD         //0x3F8 + 0x05 
#define   UART_IER     0x3F9         //0x3F8 + 0x01
#define   UART_FCR     0x3FA         //0x3F8 + 0x02 

#define   FCR_LIMPAR  0x7

#define   INSERT_QUEUE 0xE

#define   IER(n)      (n & 0xF0)     
#define   IER_OUT(n)  (n | BIT(0))  
#define   IER_IN(n)   (!(n & BIT(0)))   

#define   TENTATIVAS   30

#define IIR_ID          BIT(1) | BIT(2) | BIT(3)
#define IIR_FIFO_CT BIT(3) | BIT(2)

#endif 
