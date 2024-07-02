#include "collision.h"

Collision* array_collision_main_menu;
Collision* array_collision_pause_menu;

int size_array_collision_main_menu = 3;
int size_array_collision_pause_menu = 3;

extern int num_cards;

extern int square_x;
extern int square_y;

int allocate_collision_array(){
    if(allocate_collision_array_main_menu()){
        fprintf(stderr, "Error: %s\n", "allocate_collision_array_main_menu function error.");
        return 1;
    }

    if(allocate_collision_array_pause_menu()){
        fprintf(stderr, "Error: %s\n", "allocate_collision_array_pause_menu function error.");
        return 1;
    }
    return 0;
}

int allocate_collision_array_main_menu(){
    array_collision_main_menu = (Collision*) malloc(size_array_collision_main_menu * sizeof(Collision));

    if(array_collision_main_menu == NULL){
        fprintf(stderr, "Error: %s\n", "malloc function to allocate array_colosion_main_menu error.");
        return 1;
    }

    Collision collision = {120, 383, 330, 426};
    array_collision_main_menu[0] = collision;

    collision.xi = 255;
    collision.xf = 518;
    collision.yi = 460;
    collision.yf = 556;
    array_collision_main_menu[1] = collision;

    collision.xi = 433;
    collision.xf = 696;
    collision.yi = 330;
    collision.yf = 426;
    array_collision_main_menu[2] = collision;

    return 0;
}

int allocate_collision_array_pause_menu(){
    array_collision_pause_menu = (Collision*) malloc(size_array_collision_pause_menu * sizeof(Collision));

    if(array_collision_pause_menu == NULL){
        fprintf(stderr, "Error: %s\n", "malloc function to allocate array_colosion_pause_menu error.");
        return 1;
    }

    Collision collision = {275, 538, 115, 211};
    array_collision_pause_menu[0] = collision;

    collision.xi = 275;
    collision.xf = 538;
    collision.yi = 240;
    collision.yf = 336;
    array_collision_pause_menu[1] = collision;

    collision.xi = 275;
    collision.xf = 538;
    collision.yi = 365;
    collision.yf = 461;
    array_collision_pause_menu[2] = collision;

    return 0;
}



void free_collision_array(){
    free(array_collision_main_menu);
    free(array_collision_pause_menu);
}

int isCollision(int x, int y, Collision collision){
    x += 18;
    y += 13;

    if(x >= collision.xi && x <= collision.xf && y >= collision.yi && y <= collision.yf){
        return 1;
    }

    return 0;
}

int testStartButtonCollision(int x, int y){
    return isCollision(x, y, array_collision_main_menu[0]);
}

int testExitButtonCollision(int x, int y){
    return isCollision(x, y, array_collision_main_menu[1]);
}

int testMultiButtonCollision(int x, int y){
    return isCollision(x, y, array_collision_main_menu[2]);
}

int testResumeButtonCollision(int x, int y){
    return isCollision(x, y, array_collision_pause_menu[0]);
}

int testRestartButtonCollision(int x, int y){
    return isCollision(x, y, array_collision_pause_menu[1]);
}

int testExitButtonCollisionPause(int x, int y){
    return isCollision(x, y, array_collision_pause_menu[2]);
}

int selected_card(int x, int y){
    int space = (730 - 73 * num_cards) / 2;
    int x_width = 0;
    int y_height = 490;
    Collision collision;
    collision.yi = y_height;
    collision.yf = y_height + 106;

    for(int i = 0; i < num_cards; i++){
        x_width = 73*i + space + 34;
        collision.xi = x_width;
        collision.xf = x_width + 74;
        
        if(isCollision(x, y, collision)){
            return i;
        }
    }

    return -1;
}

int testCardGrabCollision(int x, int y){
    Collision collision;

    collision.xi = 370;
    collision.xf = 446;
    collision.yi = 330;
    collision.yf = 436;

    if(isCollision(x, y, collision)){
        return 1;
    }

    return 0;
}

int testCancelButtonCollision(int x, int y){
    Collision collision;

    collision.xi = 275;
    collision.xf = 538;
    collision.yi = 330;
    collision.yf = 426;

    if(isCollision(x, y, collision)){
        return 1;
    }

    return 0;
}


int testAcceptButtonCollision(int x, int y){
    Collision collision;

    collision.xi = 250;
    collision.xf = 518;
    collision.yi = 240;
    collision.yf = 336;

    if(isCollision(x, y, collision)){
        return 1;
    }

    return 0;
}

int testDeclineButtonCollision(int x, int y){
    Collision collision;

    collision.xi = 250;
    collision.xf = 518;
    collision.yi = 365;
    collision.yf = 461;

    if(isCollision(x, y, collision)){
        return 1;
    }

    return 0;
}

int testTopButton(int x, int y){
    Collision collision;

    collision.xi = 249;
    collision.xf = 380;
    collision.yi = 392;
    collision.yf = 448;

    if(isCollision(x, y, collision)){
        return 1;
    }

    return 0;
}

int testBotButton(int x, int y){
    Collision collision;

    collision.xi = 412;
    collision.xf = 543;
    collision.yi = 392;                 //173 horizontal --- 73 vertical
    collision.yf = 448;

    if(isCollision(x, y, collision)){
        return 1;
    }

    return 0;
}

int testSlideButton(int x, int y){
    Collision collision;

    collision.xi = 274;
    collision.xf = 537;
    collision.yi = 413;
    collision.yf = 509;

    if(isCollision(x, y, collision)){
        return 1;
    }

    return 0;
}

int testSquareCollision(int x, int y){
    Collision collision;

    collision.xi = square_x;
    collision.xf = square_x + 21;
    collision.yi = square_y;
    collision.yf = square_y + 21;

    if(isCollision(x, y, collision)){
        return 1;
    }

    return 0;
}

int testTimerTrackerCollision(int x, int y){
    Collision collision;

    collision.xi = 274;
    collision.xf = 537;
    collision.yi = 283;
    collision.yf = 379;

    if(isCollision(x, y, collision)){
        return 1;
    }

    return 0;
}


