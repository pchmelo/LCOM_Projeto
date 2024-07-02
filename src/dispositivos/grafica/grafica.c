#include <lcom/lcf.h>
#include "grafica.h"

int (printar_form_xpm)(uint16_t x, uint16_t y, xpm_map_t xpm){
    xpm_image_t new_xpm;

    //obtem as cores do ficheiro do xpm
    uint32_t *cores = (uint32_t*) xpm_load(xpm, XPM_8_8_8_8, &new_xpm);

    int altura = 0;
    int comprimento = 0;

    bool flag = true;
    
    //desenha a imagem xpm a começar na posição (x, y) atraves do print pixel a pixel com uma matrix de dois whiles
    while(altura < new_xpm.height){
        while(comprimento < new_xpm.width){
            if(desenhar_pixel(x + comprimento, y + altura, *cores)){
                fprintf(stderr, "Error: %s\n", "desenhar_pixel function error.");
                return 1;
            }
            cores = cores + 1;
            comprimento = comprimento + 1;
        }

        if(flag){
            printf("comprimento: %d\n", comprimento);
            flag = false;
        }
        
        comprimento = 0;
        altura = altura + 1;
    }

    return 0;
}

int (printar_form_xpm_sprite)(uint16_t x, uint16_t y, Sprite *sprite){
    uint32_t *cores = sprite->pixels;
    
    uint16_t sprite_altura = sprite->altura;
    uint16_t sprite_comprimento = sprite->comprimento;

    uint16_t altura = 0;
    uint16_t comprimento = 0;

    //desenha a imagem xpm a começar na posição (x, y) atraves do print pixel a pixel com uma matrix de dois whiles
    while(altura < sprite_altura){
        while(comprimento < sprite_comprimento){
            if(desenhar_pixel(x + comprimento, y + altura, *cores)){
                fprintf(stderr, "Error: %s\n", "desenhar_pixel function error.");
                return 1;
            }
            cores = cores + 1;
            comprimento = comprimento + 1;
        }
        comprimento = 0;
        altura = altura + 1;
    }

    return 0;
}

int (printar_form_xpm_sprite_rotated)(uint16_t x, uint16_t y, Sprite *sprite){
    uint32_t *cores = sprite->pixels;
    
    uint16_t sprite_altura = sprite->altura;
    uint16_t sprite_comprimento = sprite->comprimento;

    uint16_t altura = 0;
    uint16_t comprimento = 0;

    //desenha a imagem xpm a começar na posição (x, y) atraves do print pixel a pixel com uma matrix de dois whiles com rotação de 90 graus
    while(altura < sprite_altura){
        while(comprimento < sprite_comprimento){
            // Transpose and reverse each row to rotate the sprite by 90 degrees counterclockwise
            if(desenhar_pixel(x + sprite_altura - altura - 1, y + comprimento, cores[comprimento + altura * sprite_comprimento])){
                fprintf(stderr, "Error: %s\n", "desenhar_pixel function error.");
                return 1;
            }
            comprimento = comprimento + 1;
        }
        comprimento = 0;
        altura = altura + 1;
    }

    return 0;
}

void criarBufferSetDesenho(){

    bufferSetDesenho = (uint8_t*) malloc(frameTamanho);
    if(bufferSetDesenho == NULL){
        fprintf(stderr, "Error: %s\n", "Problema em alocar a memoria fisica para o bufferSetDesenho");
    }
}

void copiarbufferSetDesenhoToBufferGrafico(){
    memcpy(bufferGrafico, bufferSetDesenho, frameTamanho);
}

void limparBufferGrafico(){
    memset(bufferSetDesenho, 0, frameTamanho);
}

int drawSpiltSecondBar(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
    for(int i = x; i < x + width; i++){
        for(int j = y; j < y + height; j++){
            desenhar_pixel(i, j, color);
        }
    }

    return 0;
}

int molduraCarta(int x, int y, uint32_t color){
    int card_comprimento = 76;
    int card_altura = 106; 

    //uint32_t color = 0xffbf00;

    for(int i = x; i < x + card_comprimento; i++){
        for(int j = y; j < y + 4; j++){
            desenhar_pixel(i, j, color);
        }
    }

    for(int i = x; i < x + card_comprimento; i++){
        for(int j = y + card_altura - 4; j < y + card_altura; j++){
            desenhar_pixel(i, j, color);
        }
    }

    for(int j = y; j < y + card_altura; j++){
        for(int i = x; i < x + 4; i++){
            desenhar_pixel(i, j, color);
        }
    }

    for(int j = y; j < y + card_altura; j++){
        for(int i = x + card_comprimento - 4; i < x + card_comprimento; i++){
            desenhar_pixel(i, j, color);
        }
    }

    return 0;
}

