#include "kbc.h"



int ler_output_KBC(uint8_t port, uint8_t *output, uint8_t mouse) {
    uint8_t status;
    
    for(int i = 0; i < MAX_TENTATIVAS; i++){
        if(ler_status_KBC(&status)){
            fprintf(stderr, "Error: %s\n", "ler_status_KBC function error.");
            return 1;
        }

        if(status & OUTPUT_BUFFER_CHEIO){
            if(util_sys_inb(port, output)){
                fprintf(stderr, "Error: %s\n", "util_sys_inb read error.");
                return 1;
            }

            if(status & ERRO_TIMEOUT){
                fprintf(stderr, "Error: %s\n", "timeout error.");
                return 1;
            }

             if(status & ERRO_PARIDADE){
                fprintf(stderr, "Error: %s\n", "parity error.");
                return 1;
            }

            uint8_t bit_5 = status & BIT(5);

            if(mouse && !bit_5){
                fprintf(stderr, "Error: %s\n", "status recebido não é mouse.");
                return 1;
            }


            if(!mouse && bit_5){
                fprintf(stderr, "Error: %s\n", "status recebido não é teclado.");
                return 1;
            }

            return 0;
        }

        tickdelay(micros_to_ticks(KBC_TEMPO_ESPERA));
    }

    fprintf(stderr, "Error: %s\n", "ultrapassou o numero de tentativas.");
    return 1;
}

int (write_command_KBC)(uint8_t port, uint8_t commandByte) {
    uint8_t status;
    
    for(int i = 0; i < MAX_TENTATIVAS; i++){
        if(ler_status_KBC(&status)){
            fprintf(stderr, "Error: %s\n", "ler_status_KBC function error.");
            return 1;
        }

        if((status & INPUT_BUFFER_CHEIO) == 0){
            if(sys_outb(port, commandByte)){
                fprintf(stderr, "Error: %s\n", "sys_outb write error.");
                return 1;
            }

            return 0;
        }

        tickdelay(micros_to_ticks(KBC_TEMPO_ESPERA));
    }

    fprintf(stderr, "Error: %s\n", "ultrapassou o numero de tentativas.");
    return 1;
}
