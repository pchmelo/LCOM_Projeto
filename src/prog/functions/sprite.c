#include "sprite.h"

Sprite* criar_sprite(xpm_map_t ficheiro_xpm){
    Sprite *res = (Sprite*) malloc(sizeof(Sprite));
    xpm_image_t img;

    if(res == NULL){
        fprintf(stderr, "Error: %s\n", "nao foi possivel alocar memoria da Sprite - malloc error");
        return NULL;
    }

    res->pixels = (uint32_t*) xpm_load(ficheiro_xpm, XPM_8_8_8_8, &img);
    if(res->pixels == NULL){
        fprintf(stderr, "Error: %s\n", "nao foi possivel carregar a imagem - xpm_load error");
        free(res);
        return NULL;
    }

    res->comprimento = img.width;
    res->altura = img.height;

    return res;
}

void destruir_sprite(Sprite *sprite){
    if(sprite == NULL){
        fprintf(stderr, "Error: %s\n", "sprite nao existe");
        return;
    }

    if(sprite->pixels != NULL){
        free(sprite->pixels);
    }

    free(sprite);
    sprite = NULL;
}

void alocar_sprite_mem(){
    sprite_mouse = criar_sprite((xpm_map_t) mouse);
    sprite_mouse_click = criar_sprite((xpm_map_t) mouse_click);
    sprite_mouse_hand = criar_sprite((xpm_map_t) mouse_hand);
    sprite_mouse_grab = criar_sprite((xpm_map_t) mouse_grab);

    sprite_pikachu = criar_sprite((xpm_map_t) pikachu);

    sprite_main_menu_background = criar_sprite((xpm_map_t) main_menu_background);
    sprite_title = criar_sprite((xpm_map_t) title);
    sprite_button_start = criar_sprite((xpm_map_t) button_start);
    sprite_button_start_pressed = criar_sprite((xpm_map_t) button_start_pressed);
    sprite_button_exit = criar_sprite((xpm_map_t) button_exit);
    sprite_button_exit_pressed = criar_sprite((xpm_map_t) button_exit_pressed);
    sprite_button_multi = criar_sprite((xpm_map_t) button_multi);
    sprite_button_multi_pressed = criar_sprite((xpm_map_t) button_multi_pressed);

    sprite_button_cancel = criar_sprite((xpm_map_t) button_cancel);
    sprite_main_menu_connection = criar_sprite((xpm_map_t) main_menu_connection);
    sprite_button_cancel_selected = criar_sprite((xpm_map_t) button_cancel_selected);

    sprite_menu_invited = criar_sprite((xpm_map_t) main_menu_invited);
    sprite_button_accept = criar_sprite((xpm_map_t) button_accept);
    sprite_button_accept_selected = criar_sprite((xpm_map_t) button_accept_selected);
    sprite_button_decline = criar_sprite((xpm_map_t) button_decline);
    sprite_button_decline_selected = criar_sprite((xpm_map_t) button_decline_selected);

    sprite_table_top = criar_sprite((xpm_map_t) table_top);
    sprite_score_board = criar_sprite((xpm_map_t) score_board);
    sprite_round_end = criar_sprite((xpm_map_t) round_end);
    sprite_round_end_red = criar_sprite((xpm_map_t) round_end_red);
    sprite_round_end_blue = criar_sprite((xpm_map_t) round_end_blue);

    sprite_menu_pausa = criar_sprite((xpm_map_t) menu_pausa);
    sprite_button_restart = criar_sprite((xpm_map_t) butao_restart);
    sprite_button_restart_selected = criar_sprite((xpm_map_t) butao_restart_selected);
    sprite_button_resume = criar_sprite((xpm_map_t) butao_resume);
    sprite_button_resume_selected = criar_sprite((xpm_map_t) butao_resume_selected);

    sprite_back_1 = criar_sprite((xpm_map_t) back_1);
    sprite_back_2 = criar_sprite((xpm_map_t) back_2);

    sprite_clubs_2 = criar_sprite((xpm_map_t) clubs_2);
    sprite_clubs_3 = criar_sprite((xpm_map_t) clubs_3);
    sprite_clubs_4 = criar_sprite((xpm_map_t) clubs_4);
    sprite_clubs_5 = criar_sprite((xpm_map_t) clubs_5);
    sprite_clubs_6 = criar_sprite((xpm_map_t) clubs_6);
    sprite_clubs_7 = criar_sprite((xpm_map_t) clubs_7);
    sprite_clubs_j = criar_sprite((xpm_map_t) clubs_j);
    sprite_clubs_q = criar_sprite((xpm_map_t) clubs_q);
    sprite_clubs_k = criar_sprite((xpm_map_t) clubs_k);
    sprite_clubs_ace = criar_sprite((xpm_map_t) clubs_ace);

    sprite_diamonds_2 = criar_sprite((xpm_map_t) diamonds_2);
    sprite_diamonds_3 = criar_sprite((xpm_map_t) diamonds_3);
    sprite_diamonds_4 = criar_sprite((xpm_map_t) diamonds_4);
    sprite_diamonds_5 = criar_sprite((xpm_map_t) diamonds_5);
    sprite_diamonds_6 = criar_sprite((xpm_map_t) diamonds_6);
    sprite_diamonds_7 = criar_sprite((xpm_map_t) diamonds_7);
    sprite_diamonds_j = criar_sprite((xpm_map_t) diamonds_j);
    sprite_diamonds_q = criar_sprite((xpm_map_t) diamonds_q);
    sprite_diamonds_k = criar_sprite((xpm_map_t) diamonds_k);
    sprite_diamonds_ace = criar_sprite((xpm_map_t) diamonds_ace);

    sprite_hearts_2 = criar_sprite((xpm_map_t) hearts_2);
    sprite_hearts_3 = criar_sprite((xpm_map_t) hearts_3);
    sprite_hearts_4 = criar_sprite((xpm_map_t) hearts_4);
    sprite_hearts_5 = criar_sprite((xpm_map_t) hearts_5);
    sprite_hearts_6 = criar_sprite((xpm_map_t) hearts_6);
    sprite_hearts_7 = criar_sprite((xpm_map_t) hearts_7);
    sprite_hearts_j = criar_sprite((xpm_map_t) hearts_j);
    sprite_hearts_q = criar_sprite((xpm_map_t) hearts_q);
    sprite_hearts_k = criar_sprite((xpm_map_t) hearts_k);
    sprite_hearts_ace = criar_sprite((xpm_map_t) hearts_ace);

    sprite_spades_2 = criar_sprite((xpm_map_t) spades_2);
    sprite_spades_3 = criar_sprite((xpm_map_t) spades_3);
    sprite_spades_4 = criar_sprite((xpm_map_t) spades_4);
    sprite_spades_5 = criar_sprite((xpm_map_t) spades_5);
    sprite_spades_6 = criar_sprite((xpm_map_t) spades_6);
    sprite_spades_7 = criar_sprite((xpm_map_t) spades_7);
    sprite_spades_j = criar_sprite((xpm_map_t) spades_j);
    sprite_spades_q = criar_sprite((xpm_map_t) spades_q);
    sprite_spades_k = criar_sprite((xpm_map_t) spades_k);
    sprite_spades_ace = criar_sprite((xpm_map_t) spades_ace);

    sprite_num0 = criar_sprite((xpm_map_t) num0);
    sprite_num1 = criar_sprite((xpm_map_t) num1);
    sprite_num2 = criar_sprite((xpm_map_t) num2);
    sprite_num3 = criar_sprite((xpm_map_t) num3);
    sprite_num4 = criar_sprite((xpm_map_t) num4);
    sprite_num5 = criar_sprite((xpm_map_t) num5);
    sprite_num6 = criar_sprite((xpm_map_t) num6);
    sprite_num7 = criar_sprite((xpm_map_t) num7);
    sprite_num8 = criar_sprite((xpm_map_t) num8);
    sprite_num9 = criar_sprite((xpm_map_t) num9);

    sprite_card_deck = criar_sprite((xpm_map_t) card_deck);
    sprite_select_bot_btn = criar_sprite((xpm_map_t) select_bot_btn);
    sprite_select_bot_btn_pressed = criar_sprite((xpm_map_t) select_bot_btn_pressed);
    sprite_select_top_btn = criar_sprite((xpm_map_t) select_top_btn);
    sprite_select_top_btn_pressed = criar_sprite((xpm_map_t) select_top_btn_pressed);
    sprite_select_card_bg = criar_sprite((xpm_map_t) select_card_bg);
    sprite_select_card_arrow = criar_sprite((xpm_map_t) select_card_arrow);
    sprite_select_card_arrow_inv = criar_sprite((xpm_map_t) select_card_arrow_inv);

    sprite_slider = criar_sprite((xpm_map_t) slider);
    sprite_split_deck_bg = criar_sprite((xpm_map_t) split_deck_bg);
    sprite_split_deck_btn = criar_sprite((xpm_map_t) split_deck_btn);
    sprite_split_deck_btn_pressed = criar_sprite((xpm_map_t) split_deck_btn_pressed);

    sprite_time_tracker = criar_sprite((xpm_map_t) time_tracker);
    sprite_minutes = criar_sprite((xpm_map_t) minutes);

}

void remover_sprite_mem(){
    destruir_sprite(sprite_mouse);
    sprite_mouse = NULL;

    destruir_sprite(sprite_mouse_click);
    sprite_mouse_click = NULL;

    destruir_sprite(sprite_mouse_hand);
    sprite_mouse_hand = NULL;

    destruir_sprite(sprite_mouse_grab);
    sprite_mouse_grab = NULL;

    destruir_sprite(sprite_menu_invited);
    sprite_menu_invited = NULL;

    destruir_sprite(sprite_button_accept);
    sprite_button_accept = NULL;

    destruir_sprite(sprite_button_accept_selected);
    sprite_button_accept_selected = NULL;

    destruir_sprite(sprite_button_decline);
    sprite_button_decline = NULL;

    destruir_sprite(sprite_button_decline_selected);
    sprite_button_decline_selected = NULL;


    destruir_sprite(sprite_pikachu);
    sprite_pikachu = NULL;

    destruir_sprite(sprite_main_menu_connection);
    sprite_main_menu_background = NULL;

    destruir_sprite(sprite_button_cancel);
    sprite_button_cancel = NULL;

    destruir_sprite(sprite_button_cancel_selected);
    sprite_button_cancel_selected = NULL;

    destruir_sprite(sprite_main_menu_background);
    sprite_main_menu_background = NULL;

    destruir_sprite(sprite_title);
    sprite_title = NULL;

    destruir_sprite(sprite_button_start);
    sprite_button_start = NULL;

    destruir_sprite(sprite_button_start_pressed);
    sprite_button_start_pressed = NULL;

    destruir_sprite(sprite_button_exit);
    sprite_button_exit = NULL;

    destruir_sprite(sprite_button_exit_pressed);
    sprite_button_exit_pressed = NULL;

    destruir_sprite(sprite_button_multi);
    sprite_button_multi = NULL;

    destruir_sprite(sprite_button_multi_pressed);
    sprite_button_multi_pressed = NULL;

    destruir_sprite(sprite_table_top);
    sprite_table_top = NULL;

    destruir_sprite(sprite_score_board);
    sprite_score_board = NULL;

    destruir_sprite(sprite_round_end);
    sprite_round_end = NULL;

    destruir_sprite(sprite_round_end_red);
    sprite_round_end_red = NULL;

    destruir_sprite(sprite_round_end_blue);
    sprite_round_end_blue = NULL;

    destruir_sprite(sprite_button_exit);
    sprite_menu_pausa = NULL;



    destruir_sprite(sprite_back_1);
    sprite_back_1 = NULL;

    destruir_sprite(sprite_back_2);
    sprite_back_2 = NULL;


    destruir_sprite(sprite_clubs_2);
    sprite_clubs_2 = NULL;

    destruir_sprite(sprite_clubs_3);
    sprite_clubs_3 = NULL;

    destruir_sprite(sprite_clubs_4);
    sprite_clubs_4 = NULL;

    destruir_sprite(sprite_clubs_5);
    sprite_clubs_5 = NULL;

    destruir_sprite(sprite_clubs_6);
    sprite_clubs_6 = NULL;

    destruir_sprite(sprite_clubs_7);
    sprite_clubs_7 = NULL;

    destruir_sprite(sprite_clubs_j);
    sprite_clubs_j = NULL;

    destruir_sprite(sprite_clubs_q);
    sprite_clubs_q = NULL;

    destruir_sprite(sprite_clubs_k);
    sprite_clubs_k = NULL;

    destruir_sprite(sprite_clubs_ace);
    sprite_clubs_ace = NULL;


    destruir_sprite(sprite_diamonds_2);
    sprite_diamonds_2 = NULL;

    destruir_sprite(sprite_diamonds_3);
    sprite_diamonds_3 = NULL;

    destruir_sprite(sprite_diamonds_4);
    sprite_diamonds_4 = NULL;

    destruir_sprite(sprite_diamonds_5);
    sprite_diamonds_5 = NULL;

    destruir_sprite(sprite_diamonds_6);
    sprite_diamonds_6 = NULL;

    destruir_sprite(sprite_diamonds_7);
    sprite_diamonds_7 = NULL;

    destruir_sprite(sprite_diamonds_j);
    sprite_diamonds_j = NULL;

    destruir_sprite(sprite_diamonds_q);
    sprite_diamonds_q = NULL;

    destruir_sprite(sprite_diamonds_k);
    sprite_diamonds_k = NULL;

    destruir_sprite(sprite_diamonds_ace);
    sprite_diamonds_ace = NULL;


    destruir_sprite(sprite_hearts_2);
    sprite_hearts_2 = NULL;

    destruir_sprite(sprite_hearts_3);
    sprite_hearts_3 = NULL;

    destruir_sprite(sprite_hearts_4);
    sprite_hearts_4 = NULL;

    destruir_sprite(sprite_hearts_5);
    sprite_hearts_5 = NULL;

    destruir_sprite(sprite_hearts_6);
    sprite_hearts_6 = NULL;

    destruir_sprite(sprite_hearts_7);
    sprite_hearts_7 = NULL;

    destruir_sprite(sprite_hearts_j);
    sprite_hearts_j = NULL;

    destruir_sprite(sprite_hearts_q);
    sprite_hearts_q = NULL;

    destruir_sprite(sprite_hearts_k);
    sprite_hearts_k = NULL;

    destruir_sprite(sprite_hearts_ace);
    sprite_hearts_ace = NULL;


    destruir_sprite(sprite_spades_2);
    sprite_spades_2 = NULL;

    destruir_sprite(sprite_spades_3);
    sprite_spades_3 = NULL;

    destruir_sprite(sprite_spades_4);
    sprite_spades_4 = NULL;

    destruir_sprite(sprite_spades_5);
    sprite_spades_5 = NULL;

    destruir_sprite(sprite_spades_6);
    sprite_spades_6 = NULL;

    destruir_sprite(sprite_spades_7);
    sprite_spades_7 = NULL;

    destruir_sprite(sprite_spades_j);
    sprite_spades_j = NULL;

    destruir_sprite(sprite_spades_q);
    sprite_spades_q = NULL;

    destruir_sprite(sprite_spades_k);
    sprite_spades_k = NULL;

    destruir_sprite(sprite_spades_ace);
    sprite_spades_ace = NULL;


    destruir_sprite(sprite_num0);
    sprite_num0 = NULL;

    destruir_sprite(sprite_num1);
    sprite_num1 = NULL;

    destruir_sprite(sprite_num2);
    sprite_num2 = NULL;

    destruir_sprite(sprite_num3);
    sprite_num3 = NULL;

    destruir_sprite(sprite_num4);
    sprite_num4 = NULL;

    destruir_sprite(sprite_num5);
    sprite_num5 = NULL;

    destruir_sprite(sprite_num6);
    sprite_num6 = NULL;

    destruir_sprite(sprite_num7);
    sprite_num7 = NULL;

    destruir_sprite(sprite_num8);
    sprite_num8 = NULL;

    destruir_sprite(sprite_num9);
    sprite_num9 = NULL;

    destruir_sprite(sprite_card_deck);
    sprite_card_deck = NULL;

    destruir_sprite(sprite_select_bot_btn);
    sprite_select_bot_btn = NULL;

    destruir_sprite(sprite_select_bot_btn_pressed);
    sprite_select_bot_btn_pressed = NULL;

    destruir_sprite(sprite_select_top_btn);
    sprite_select_top_btn = NULL;

    destruir_sprite(sprite_select_top_btn_pressed);
    sprite_select_top_btn_pressed = NULL;

    destruir_sprite(sprite_select_card_bg);
    sprite_select_card_bg = NULL;

    destruir_sprite(sprite_select_card_arrow);
    sprite_select_card_arrow = NULL;

    destruir_sprite(sprite_select_card_arrow_inv);
    sprite_select_card_arrow_inv = NULL;


    destruir_sprite(sprite_slider);
    sprite_slider = NULL;

    destruir_sprite(sprite_split_deck_bg);
    sprite_split_deck_bg = NULL;

    destruir_sprite(sprite_split_deck_btn);
    sprite_split_deck_btn = NULL;

    destruir_sprite(sprite_split_deck_btn_pressed);
    sprite_split_deck_btn_pressed = NULL;



    destruir_sprite(sprite_time_tracker);
    sprite_time_tracker = NULL;

    destruir_sprite(sprite_minutes);
    sprite_minutes = NULL;
}
