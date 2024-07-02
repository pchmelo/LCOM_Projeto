
#include "utils.h"


int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if(lsb == NULL){
    fprintf(stderr, "Error: %s\n", "NULL pointer error.");
    return 1;
  }
  
  *lsb = val & 0xFF;

  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if(msb == NULL){
    fprintf(stderr, "Error: %s\n", "NULL pointer error.");
    return 1;
  }

  *msb = (val >> 8) & 0xFF;

  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  if(value == NULL){
    fprintf(stderr, "Error: %s\n", "NULL pointer error.");
    return 1;
  }
  
  uint32_t n = 0;

  if(sys_inb(port, &n)){
    fprintf(stderr, "Error: %s\n", "sys_inb error.");
    return 1;
  } 

  *value = n & 0xFF;


  return 0;
}
