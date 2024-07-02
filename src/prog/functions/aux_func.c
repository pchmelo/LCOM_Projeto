#include "aux_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern rtc_struct rtc_time;
uint8_t seed = 0;
uint32_t count = 0;

int* time_to_int(){
    int* res = (int*) malloc(sizeof(int) * 3);

    res[0] = rtc_time.hours / 10;
    res[1] = rtc_time.hours % 10;
    res[2] = rtc_time.minutes / 10;
    res[3] = rtc_time.minutes % 10;
    res[4] = rtc_time.seconds / 10;
    res[5] = rtc_time.seconds % 10;

    return res;
}

Sprite* num_to_sprite(int num) {
    if (num == 0) return sprite_num0;
    else if (num == 1) return sprite_num1;
    else if (num == 2) return sprite_num2;
    else if (num == 3) return sprite_num3;
    else if (num == 4) return sprite_num4;
    else if (num == 5) return sprite_num5;
    else if (num == 6) return sprite_num6;
    else if (num == 7) return sprite_num7;
    else if (num == 8) return sprite_num8;
    else if (num == 9) return sprite_num9;
    else return NULL;
}

uint8_t get_seed() {
    uint8_t seed = time(NULL) & 0xFF;
    srand(seed); 
    return seed;
}

uint32_t lcg_rand() {
    uint32_t a;
    do {
        a = ((seed * count) * 1103515245 + 12345) & 0x7fffffff;
        count++;
    } while (a < 0x01);
    return a;
}

void set_seed(uint8_t seed_res) {
    seed = seed_res;

    for(int i = 0; i < 10; i++){
        uint32_t j  = lcg_rand() % 40;
        printf("%d number - %d\n", i,  j);
    }

}

int* score_to_int(int score){
    int* res = (int*) malloc(sizeof(int) * 3);

    res[0] = score / 100;
    res[1] = (score % 100) / 10;
    res[2] = score % 10;

    return res;
}

int get_slider_pos(int x){
    int max_pos = 278;
    int inicial_pos = 247;

    int pos = x - inicial_pos;

    if(pos < 0) return 0;
    if(pos > max_pos) return 39;

    return (pos * 39) / max_pos;
}

int get_time_spent(rtc_struct start, rtc_struct end){
    int start_seconds = start.hours * 3600 + start.minutes * 60 + start.seconds;
    int end_seconds = end.hours * 3600 + end.minutes * 60 + end.seconds;

    int time_spent = end_seconds - start_seconds;

    if(time_spent < 0){
        time_spent *= -1;
    }

    return (time_spent / 60) + 1;
}

int* time_spent_to_array(int time_spent, int* size){
    char str[7];
    sprintf(str, "%d", time_spent);

    *size = strlen(str);
    int* time_array = malloc(sizeof(int) * (*size));

    for(int i = 0; i < *size; i++){
        time_array[i] = str[i] - '0';
    }

    return time_array;
}
