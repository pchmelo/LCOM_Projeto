#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <lcom/lcf.h>
#include "../../assets/pikachu.xpm"

#include "../../assets/main_menu/main_menu_background.xpm"
#include "../../assets/main_menu/title.xpm"
#include "../../assets/main_menu/button_start.xpm"
#include "../../assets/main_menu/button_start_pressed.xpm"
#include "../../assets/main_menu/button_exit.xpm"
#include "../../assets/main_menu/button_exit_pressed.xpm"
#include "../../assets/main_menu/button_multi.xpm"
#include "../../assets/main_menu/button_multi_pressed.xpm"

#include "../../assets/connection/main_menu_connection.xpm"
#include "../../assets/connection/button_cancel.xpm"
#include "../../assets/connection/button_cancel_selected.xpm"

#include "../../assets/connection/main_menu_invited.xpm"
#include "../../assets/connection/button_accept.xpm"
#include "../../assets/connection/button_accept_selected.xpm"
#include "../../assets/connection/button_decline.xpm"
#include "../../assets/connection/button_decline_selected.xpm"

#include "../../assets/game_table/table_top.xpm"
#include "../../assets/game_table/score_board.xpm"
#include "../../assets/game/menu_pausa.xpm"

#include "../../assets/game/butao_resume.xpm"
#include "../../assets/game/butao_resume_selected.xpm"
#include "../../assets/game/butao_restart.xpm"
#include "../../assets/game/butao_restart_selected.xpm"
#include "../../assets/game/round_end.xpm"
#include "../../assets/game/round_end_red.xpm"
#include "../../assets/game/round_end_blue.xpm"


#include "../../assets/cards/back_1.xpm"
#include "../../assets/cards/back_2.xpm"

#include "../../assets/cards/clubs_2.xpm"
#include "../../assets/cards/clubs_3.xpm"
#include "../../assets/cards/clubs_4.xpm"
#include "../../assets/cards/clubs_5.xpm"
#include "../../assets/cards/clubs_6.xpm"
#include "../../assets/cards/clubs_7.xpm"
#include "../../assets/cards/clubs_j.xpm"
#include "../../assets/cards/clubs_q.xpm"
#include "../../assets/cards/clubs_k.xpm"
#include "../../assets/cards/clubs_ace.xpm"

#include "../../assets/cards/diamonds_2.xpm"
#include "../../assets/cards/diamonds_3.xpm"
#include "../../assets/cards/diamonds_4.xpm"
#include "../../assets/cards/diamonds_5.xpm"
#include "../../assets/cards/diamonds_6.xpm"
#include "../../assets/cards/diamonds_7.xpm"
#include "../../assets/cards/diamonds_j.xpm"
#include "../../assets/cards/diamonds_q.xpm"
#include "../../assets/cards/diamonds_k.xpm"
#include "../../assets/cards/diamonds_ace.xpm"

#include "../../assets/cards/hearts_2.xpm"
#include "../../assets/cards/hearts_3.xpm"
#include "../../assets/cards/hearts_4.xpm"
#include "../../assets/cards/hearts_5.xpm"
#include "../../assets/cards/hearts_6.xpm"
#include "../../assets/cards/hearts_7.xpm"
#include "../../assets/cards/hearts_j.xpm"
#include "../../assets/cards/hearts_q.xpm"
#include "../../assets/cards/hearts_k.xpm"
#include "../../assets/cards/hearts_ace.xpm"

#include "../../assets/cards/spades_2.xpm"
#include "../../assets/cards/spades_3.xpm"
#include "../../assets/cards/spades_4.xpm"
#include "../../assets/cards/spades_5.xpm"
#include "../../assets/cards/spades_6.xpm"
#include "../../assets/cards/spades_7.xpm"
#include "../../assets/cards/spades_j.xpm"
#include "../../assets/cards/spades_q.xpm"
#include "../../assets/cards/spades_k.xpm"
#include "../../assets/cards/spades_ace.xpm"

#include "../../assets/mouse/mouse.xpm"
#include "../../assets/mouse/mouse_click.xpm"
#include "../../assets/mouse/mouse_hand.xpm"
#include "../../assets/mouse/mouse_grab.xpm"

#include "../../assets/numbers/num0.xpm"
#include "../../assets/numbers/num1.xpm"
#include "../../assets/numbers/num2.xpm"
#include "../../assets/numbers/num3.xpm"
#include "../../assets/numbers/num4.xpm"
#include "../../assets/numbers/num5.xpm"
#include "../../assets/numbers/num6.xpm"
#include "../../assets/numbers/num7.xpm"
#include "../../assets/numbers/num8.xpm"
#include "../../assets/numbers/num9.xpm"

#include "../../assets/auxiliary_menus/card_deck.xpm"
#include "../../assets/auxiliary_menus/select_bot_btn.xpm"
#include "../../assets/auxiliary_menus/select_bot_btn_pressed.xpm"
#include "../../assets/auxiliary_menus/select_top_btn.xpm"
#include "../../assets/auxiliary_menus/select_top_btn_pressed.xpm"
#include "../../assets/auxiliary_menus/select_card_bg.xpm"
#include "../../assets/auxiliary_menus/select_card_arrow.xpm"
#include "../../assets/auxiliary_menus/select_card_arrow_inv.xpm"

#include "../../assets/auxiliary_menus/slider.xpm"
#include "../../assets/auxiliary_menus/split_deck_bg.xpm"
#include "../../assets/auxiliary_menus/split_deck_btn.xpm"
#include "../../assets/auxiliary_menus/split_deck_btn_pressed.xpm"

#include "../../assets/auxiliary_menus/time_tracker.xpm"
#include "../../assets/auxiliary_menus/minutes.xpm"

/**
 * @brief Structure representing a sprite.
 *
 * Contains the x and y coordinates of the sprite, its width and height, and a pointer to its pixel data.
 */
typedef struct Sprite{
  int x, y;
  uint16_t comprimento, altura;
  uint32_t *pixels;
} Sprite;



Sprite *sprite_pikachu;
Sprite *sprite_main_menu_background;
Sprite *sprite_title;

Sprite *sprite_button_start;
Sprite *sprite_button_start_pressed;
Sprite *sprite_button_exit;
Sprite *sprite_button_exit_pressed;
Sprite *sprite_button_multi;
Sprite *sprite_button_multi_pressed;

Sprite *sprite_main_menu_connection;
Sprite *sprite_button_cancel;
Sprite *sprite_button_cancel_selected;

Sprite *sprite_menu_invited;
Sprite *sprite_button_accept;
Sprite *sprite_button_accept_selected;
Sprite *sprite_button_decline;
Sprite *sprite_button_decline_selected;

Sprite *sprite_table_top;
Sprite *sprite_score_board;
Sprite *sprite_menu_pausa;
Sprite *sprite_round_end;
Sprite *sprite_round_end_red;
Sprite *sprite_round_end_blue;


Sprite *sprite_button_resume;
Sprite *sprite_button_resume_selected;
Sprite *sprite_button_restart;
Sprite *sprite_button_restart_selected;

Sprite *sprite_back_1;
Sprite *sprite_back_2;

Sprite *sprite_clubs_2;
Sprite *sprite_clubs_3;
Sprite *sprite_clubs_4;
Sprite *sprite_clubs_5;
Sprite *sprite_clubs_6;
Sprite *sprite_clubs_7;
Sprite *sprite_clubs_j;
Sprite *sprite_clubs_q;
Sprite *sprite_clubs_k;
Sprite *sprite_clubs_ace;

Sprite *sprite_diamonds_2;
Sprite *sprite_diamonds_3;
Sprite *sprite_diamonds_4;
Sprite *sprite_diamonds_5;
Sprite *sprite_diamonds_6;
Sprite *sprite_diamonds_7;
Sprite *sprite_diamonds_j;
Sprite *sprite_diamonds_q;
Sprite *sprite_diamonds_k;
Sprite *sprite_diamonds_ace;

Sprite *sprite_hearts_2;
Sprite *sprite_hearts_3;
Sprite *sprite_hearts_4;
Sprite *sprite_hearts_5;
Sprite *sprite_hearts_6;
Sprite *sprite_hearts_7;
Sprite *sprite_hearts_j;
Sprite *sprite_hearts_q;
Sprite *sprite_hearts_k;
Sprite *sprite_hearts_ace;

Sprite *sprite_spades_2;
Sprite *sprite_spades_3;
Sprite *sprite_spades_4;
Sprite *sprite_spades_5;
Sprite *sprite_spades_6;
Sprite *sprite_spades_7;
Sprite *sprite_spades_j;
Sprite *sprite_spades_q;
Sprite *sprite_spades_k;
Sprite *sprite_spades_ace;

Sprite *sprite_mouse;
Sprite *sprite_mouse_click;
Sprite *sprite_mouse_hand;
Sprite *sprite_mouse_grab;

Sprite *sprite_num0;
Sprite *sprite_num1;
Sprite *sprite_num2;
Sprite *sprite_num3;
Sprite *sprite_num4;
Sprite *sprite_num5;
Sprite *sprite_num6;
Sprite *sprite_num7;
Sprite *sprite_num8;
Sprite *sprite_num9;

Sprite *sprite_card_deck;
Sprite *sprite_select_bot_btn;
Sprite *sprite_select_bot_btn_pressed;
Sprite *sprite_select_top_btn;
Sprite *sprite_select_top_btn_pressed;
Sprite *sprite_select_card_bg;
Sprite *sprite_select_card_arrow;
Sprite *sprite_select_card_arrow_inv;

Sprite *sprite_slider;
Sprite *sprite_split_deck_bg;
Sprite *sprite_split_deck_btn;
Sprite *sprite_split_deck_btn_pressed;

Sprite *sprite_time_tracker;
Sprite *sprite_minutes;


/**
 * @brief Creates a sprite from an XPM file.
 *
 * Creates a sprite by loading an XPM file into memory.
 * Allocates memory for the sprite, loads the XPM file, and sets the sprite's width and height.
 * If there is an error during memory allocation or loading the XPM file, the function prints an error message and returns NULL.
 *
 * @param ficheiro_xpm The XPM file to load.
 * @return A pointer to the created sprite, or NULL if there was an error.
 */
Sprite* criar_sprite(xpm_map_t ficheiro_xpm);

/**
 * @brief Destroys a sprite.
 *
 * Frees the memory allocated for a sprite and its pixel data.
 * If the sprite is NULL, the function prints an error message and returns.
 * After freeing the memory, it sets the sprite pointer to NULL.
 *
 * @param sprite The sprite to destroy.
 */
void destruir_sprite(Sprite *sprite);


/**
 * @brief Allocates memory for sprites.
 *
 * Calls the criar_sprite function for each sprite in the game or application.
 * Each sprite is loaded from an XPM file and stored in memory.
 */
void alocar_sprite_mem();

/**
 * @brief Removes sprites from memory.
 *
 * Calls the destruir_sprite function for each sprite in the game or application.
 * Each sprite is removed from memory to free up resources.
 */
void remover_sprite_mem();

#endif

