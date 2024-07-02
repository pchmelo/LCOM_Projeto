#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#define IRQ_KBD    1

#define IRQ_MOUSE  12


#define ESC_BREAK              0x81
#define ENTER_BREAK            0x9C

#define LEFT_ARROW_BREAK       0xCB
#define RIGHT_ARROW_BREAK      0xCD
#define UP_ARROW_BREAK         0xC8
#define DOWN_ARROW_BREAK       0xD0

#define MAKE_CODE              BIT(7)

#define DOIS_BYTES             0xE0

#define INTERRUPTOR            BIT(0)

#define ERRO_TIMEOUT           BIT(6)

#define ERRO_PARIDADE          BIT(7)

#define OUTPUT_BUFFER_CHEIO    BIT(0)

#define INPUT_BUFFER_CHEIO     BIT(1)


#define KBC_REG_STATUS          0x64

#define KBC_INPUT_COMMAND       0x64

#define KBC_OUTPUT_COMMAND      0x60

#define KBC_READ_COMMAND        0x20

#define KBC_WRITE_COMMAND       0x60


#define KBC_TEMPO_ESPERA    20000

#define MAX_TENTATIVAS      10


#define LEFT_BUTTON     BIT(0)

#define RIGHT_BUTTON    BIT(1)

#define MIDDLE_BUTTON   BIT(2)

#define PRIMEIRO_BYTE   BIT(3)

#define MOUSE_X         BIT(4)

#define MOUSE_Y         BIT(5)

#define X_OVERFLOW      BIT(6)

#define Y_OVERFLOW      BIT(7)


#define DESLIGAR_DATA_REPORT    0xF5
#define LIGAR_DATA_REPORT       0xF4
#define LIGAR_STREAM_MODE       0xEA
#define LER_MOUSE_DATA          0xEB

#define WRITE_MOUSE_BYTE        0xD4


#define ACKNOWLEDGED         0xFA

#define NOT_ACKNOWLEDGED     0xFE


#endif 
