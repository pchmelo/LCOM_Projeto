#include "interrupts.h"

int timer_hook_id = 0;
int keyboard_hook_id = 1;
int mouse_hook_id = 3; 
int rtc_hook_id = RTC_IRQ;
int hook_id_sp = 7;

extern fila_sp* f;

int (timer_subscribe_int)(uint8_t *bit_no) {
  if(bit_no == NULL){
    fprintf(stderr, "Error: %s\n", "bit_no NULL Pointer");
    return 1;
  }
  
  *bit_no = BIT(timer_hook_id);

  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id)){
    fprintf(stderr, "Error: %s\n", "sys_irqsetpolicy function error");
    return 1;
  }

  return 0;
}

int (timer_unsubscribe_int)() {
  if (sys_irqrmpolicy(&timer_hook_id)){
    fprintf(stderr, "Error: %s\n", "sys_irqrmpolicy function error");
    return 1;
  } 

  return 0;
}


int (keyboard_subscribe_interrupt)(uint8_t *bit_no) {
    if (bit_no == NULL){
        fprintf(stderr, "Error: %s\n", "bit_no NULL Pointer");
        return 1;
    } 
    
    *bit_no = BIT(keyboard_hook_id);

    if(sys_irqsetpolicy(IRQ_KBD, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id)){
        fprintf(stderr, "Error: %s\n", "sys_irqsetpolicy function error");
         return 1; 
    }

    return 0;
}

int (keyboard_unsubscribe_interrupt)() {
    return sys_irqrmpolicy(&keyboard_hook_id);
}


int (mouse_subscribe_int)(uint8_t *bit_no){
    if (bit_no == NULL){
        fprintf(stderr, "Error: %s\n", "bit_no NULL Pointer");
        return 1;
    } 
    *bit_no = BIT(mouse_hook_id);

    if(sys_irqsetpolicy(IRQ_MOUSE, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id)){
        fprintf(stderr, "Error: %s\n", "sys_irqsetpolicy function error");
         return 1;
         
    }

    return 0;
}

int (mouse_unsubscribe_int)(){
    return sys_irqrmpolicy(&mouse_hook_id);

}



int (serial_port_subscribe_interrupt)(uint8_t *bit_no) {
  *bit_no = BIT(hook_id_sp);
  if (sys_irqsetpolicy(PORT_COM1, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_sp)) {
    printf("Error in sys_irqsetpolicy()\n");
    return 1;
  }
  return 0;
}

int (serial_port_unsubscribe_interrupt)() {
  if (sys_irqrmpolicy(&hook_id_sp)) {
    printf("Error in sys_irqrmpolicy()\n");
    return 1;
  }
  return 0;
}


int (start_serial_port)(){
    uint8_t ier_value;

    if (util_sys_inb(UART_IER, &ier_value)) {
        printf("Error in util_sys_inb()\n");
        return 1;
    }

    ier_value = IER(ier_value);

    if (sys_outb(UART_IER, IER_OUT(ier_value))) {
        printf("Error in sys_outb()\n");
        return 1;
    }

    f = criar_fila_sp();

    return 0;
}

int (modo_grafico)(uint16_t submodo){
    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86));

    reg86.intno = REG86_INTNO;
    reg86.ah = REG86_AH;
    reg86.al = REG86_AL;

    uint16_t bx = submodo | REG86_BX;
    reg86.bx = bx;

    if(sys_int86(&reg86)){
        fprintf(stderr, "Error: %s\n", "sys_int86 function error.");
        return 1;
    }


    return 0;
}

int (const_buffer_frame)(uint16_t modo){

    memset(&modInf, 0, sizeof(modInf));
    if(vbe_get_mode_info(modo, &modInf)){       //obter as informações sobre o mode que está a operar
        fprintf(stderr, "Error: %s\n", "vbe_get_mode_info function error.");
        return 1;
    }

    struct minix_mem_range enderecosFisicos;

    //formula para calcular o tamanho, em bytes, da frame do buffer
    bytesInAPixel = BYTES_NUM_PIXEL(modInf.BitsPerPixel);
    frameTamanho = modInf.XResolution * modInf.YResolution * bytesInAPixel;

    enderecosFisicos.mr_base = modInf.PhysBasePtr;      //cria um pontador para o começo da memória física para o buffer
    enderecosFisicos.mr_limit = enderecosFisicos.mr_base + frameTamanho;    //cria  o fim do buffer físico com base no tamanho da frame e o começo do mesmo

    if(sys_privctl(SELF, SYS_PRIV_ADD_MEM, &enderecosFisicos)){     //função para criar o local na memoria onde vai ser colocado o frame buffer
        fprintf(stderr, "Error: %s\n", "vbe_get_mode_info function error. Problema em alocar a memoria fisica");
        return 1;
    }
    

    bufferGrafico = vm_map_phys(SELF, (void*) enderecosFisicos.mr_base, frameTamanho);    //cria um pontador para o começo da memória virtual para o buffer
    if(bufferGrafico == NULL){
        fprintf(stderr, "Error: %s\n", "vm_map_phys function error. Problema em alocar a memoria fisica");
        return 1;
    }


    return 0;
}

int (sp_clean_interrupts)(){

    if(sys_outb(UART_FCR, FCR_LIMPAR)){
        printf("Error in util_sys_inb()\n");
        return 1;
    }

    int flag = 1;

    while(flag){
        if(f->tamanho == 0){
            flag = 0;
        }
        else{
            pop_fila_sp(f);
        }
    }

    return 0;
}

