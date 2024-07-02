#include "aux_dispositivos.h"


int (desenhar_pixel)(uint16_t x, uint16_t y, uint32_t cor){

    if(cor == 0x00ff00){
        return 0;
    }

    if(x >= modInf.XResolution){        //verifica se o valor de x ultrapassa a resolicao colocado no modo grafico
        fprintf(stderr, "Error: %s\n", "O valor da posicao de x ultrapassa a resolucao predefenida");
        return 0;
    }

    if(y >= modInf.YResolution){         //verifica se o valor de y ultrapassa a resolicao colocado no modo grafico
        fprintf(stderr, "Error: %s\n", "O valor da posicao de y ultrapassa a resolucao predefenida");
        return 0;
    }


    unsigned int indice = (modInf.XResolution * y + x) * bytesInAPixel;     //indice na zona do buffer onde colorir

    if(memcpy(bufferSetDesenho + indice, &cor, bytesInAPixel) == NULL){          //coloca no bufferFrame a cor pretendida
        fprintf(stderr, "Error: %s\n", "Problema em alocar a memoria fisica com a memcpy function");
        return 1;
    }

    //printf("(%u, %u)\n", x, y);

    return 0;
}


int (ler_status_KBC)(uint8_t* status) {
    if(util_sys_inb(KBC_REG_STATUS, status)){
        fprintf(stderr, "Error: %s\n", "util_sys_inb function error.");
        return 1;
    }
    return 0;
}

int (serial_status)(uint8_t* status) {
  if (util_sys_inb(UART_LSR, status)) {
    printf("Error in util_sys_inb()\n");
    return 1;
  }
  return 0;
}

int colocar_fila_sp(fila_sp* f, int valor){
    if((int) f->capacidade == f->tamanho){
        return 1;
    }

    f->fim = (f->fim + 1) % f->capacidade;
    f->valores[f->fim] = valor;
    f->tamanho++;

    return 0;
}

//le a o output do RTC com base no comando que lhe é enviado 
int (rtc_read_output)(uint8_t *data, uint8_t comando){
    if(sys_outb(RTC_IN_ADDR_REG, comando)){
        printf("Error in rtc_read_output() sys_outb\n");
        return 1;
    }

    if(util_sys_inb(RTC_OUT_ADDR_REG, data)){
        printf("Error in rtc_read_output() sys_inb\n");
        return 1;
    }

    return 0;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {

  if(timer < 0 || timer > 2){
    fprintf(stderr, "Error: %s\n", "timer out of bounds.");
    return 1;
  }
  
  uint32_t cmd = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  
  if(sys_outb(TIMER_CTRL, cmd)){
    fprintf(stderr, "Error: %s\n", "sys_outb function error.");
    return 1;
  }


  if(util_sys_inb(TIMER_0 + timer, st)){
    fprintf(stderr, "Error: %s\n", "util_sys_inb function error.");
    return 1;
  }

  return 0;
}

