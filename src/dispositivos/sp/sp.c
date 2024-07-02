#include "sp.h"

fila_sp* f;
uint8_t value_sp = 0;

void (exit_serial_port)(){
    limpar_fila_sp(f);
}

int (enviar_byte)(uint8_t byte){
    uint8_t status;
    int attempts = TENTATIVAS;

    while(attempts > 0){
        if(serial_status(&status)){
            printf("Error in serial_status()\n");
            return 1;
        }

        int i = status & BIT(5);


        if(i){
            printf("Sending: %d\n", byte);
            if(sys_outb(UART_BASE, byte)){
                printf("Error in sys_outb()\n");
                return 1;
            }
            return 0;
        }

        attempts--;
    }

    return 1;
}

int (receber_byte)(){
    uint8_t status;
    uint8_t rbr;

    if(serial_status(&status)){
        printf("Error in serial_status()\n");
        return 1;
    }

    int i = status & BIT(0);    //data está disponível

    if(i){
        if(util_sys_inb(UART_BASE, &rbr)){
            printf("Error in util_sys_inb()\n");
            return 1;
        }


        if(inserir_fila_sp(f, rbr, status)){
            printf("Error in inserir_fila_sp()\n");
            return 1;
        }

        return 0;
    }

    return 1;
}


void (get_value)(){
    value_sp = pop_fila_sp(f);
}


