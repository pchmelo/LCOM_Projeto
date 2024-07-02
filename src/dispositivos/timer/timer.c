#include "timer.h"





int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
 
 if(timer < 0 || timer > 2){
    fprintf(stderr, "Error: %s\n", "timer out of bounds.");
    return 1;
  }

  if(freq < 19 || freq > TIMER_FREQ){
    fprintf(stderr, "Error: %s\n", "freq out of bounds.");
    return 1;
  }

  uint8_t c_lsb;
  uint8_t c_msb;

  uint16_t c = TIMER_FREQ / freq;
  
  if(util_get_LSB(c, &c_lsb)){
    fprintf(stderr, "Error: %s\n", "util_get_LSB func error.");
    return 1;
  }

  if(util_get_MSB(c, &c_msb)){
    fprintf(stderr, "Error: %s\n", "util_get_MSB func error.");
    return 1;
  }

  uint8_t conf = 0;
  if(timer_get_conf(timer, &conf)){
    fprintf(stderr, "Error: %s\n", "timer_get_conf function error.");
    return 1;
  }

  conf &= 0xF;

  conf |= TIMER_LSB_MSB;
  conf |=  timer << 6;

  if(sys_outb(TIMER_CTRL, conf)){
    fprintf(stderr, "Error: %s\n", "sys_outb error.");
    return 1;
  }

  if(sys_outb(TIMER_0 + timer, c_lsb)){
    fprintf(stderr, "Error: %s\n", "sys_outb error.");
    return 1;
  }

  if(sys_outb(TIMER_0 + timer, c_msb)){
    fprintf(stderr, "Error: %s\n", "sys_outb error.");
    return 1;
  }


  return 0;
}


