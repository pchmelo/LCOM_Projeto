#include "handler.h"

int counter = 0;
uint8_t scancode = 0;

extern uint8_t current_byte;

void (timer_int_handler)() {
  counter++;
}

void (keyboard_ih)(){
    if(ler_output_KBC(KBC_OUTPUT_COMMAND, &scancode, 0)){
        fprintf(stderr, "Error: %s\n", "ler_output_KBC function error");
    }
}

void (mouse_interrupt_handler)() {
    if (ler_output_KBC(KBC_WRITE_COMMAND, &current_byte, 1)){
        fprintf(stderr, "Error: %s\n", "ler_output_KBC function error");
    }
}


int (sp_interrupt_handler)(){
    uint8_t iir;

    if(util_sys_inb(UART_FCR, &iir)){
        printf("Error in util_sys_inb()\n");
        return 1;
    }

    int i = IER_IN(iir);

    if(i){
        //int check = iir & 0xE;
        
        if(iir & IIR_ID == IIR_FIFO_CT){
            while(1){
                int r = receber_byte();
                if(r){
                    break;
                }
            }
        }
    }

    return 0;
}

