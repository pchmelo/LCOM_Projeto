#ifndef __GRAFICA_H
#define __GRAFICA_H

#include <lcom/lcf.h>
#include "vbe.h"
#include "../../prog/functions/sprite.h"
#include "../aux_dispositivos.h"

vbe_mode_info_t modInf;
uint8_t* bufferGrafico;
uint8_t *bufferSetDesenho;
int bytesInAPixel;
int frameTamanho;



/**
 * @brief Prints a form from an XPM.
 * @param x The x-coordinate of the form.
 * @param y The y-coordinate of the form.
 * @param xpm The XPM to print.
 * @return Returns 0 on success, 1 otherwise.
 */
int (printar_form_xpm)(uint16_t x, uint16_t y, xpm_map_t xpm);

/**
 * @brief Prints a form from an XPM sprite.
 * @param x The x-coordinate of the form.
 * @param y The y-coordinate of the form.
 * @param sprite The sprite to print.
 * @return Returns 0 on success, 1 otherwise.
 */
int (printar_form_xpm_sprite)(uint16_t x, uint16_t y, Sprite *sprite);

/**
 * @brief Prints a rotated form from an XPM sprite.
 * @param x The x-coordinate of the form.
 * @param y The y-coordinate of the form.
 * @param sprite The sprite to print.
 * @return Returns 0 on success, 1 otherwise.
 */
int (printar_form_xpm_sprite_rotated)(uint16_t x, uint16_t y, Sprite *sprite);

/**
 * @brief Draws a card frame.
 * @param x The x-coordinate of the frame.
 * @param y The y-coordinate of the frame.
 * @param cor The color of the frame.
 * @return Returns 0 on success, 1 otherwise.
 */
int molduraCarta(int x, int y, uint32_t cor);

/**
 * @brief Creates a drawing set buffer.
 */
void criarBufferSetDesenho();

/**
 * @brief Copies the drawing set buffer to the graphic buffer.
 */
void copiarbufferSetDesenhoToBufferGrafico();

/**
 * @brief Clears the graphic buffer.
 */
void limparBufferGrafico();

int drawSpiltSecondBar(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);



#endif 
