//SBUS FUNCTION DECLARATIONS AND STRUCTS

#ifndef SBUS_H
#define SBUS_H

#include "stm32f3xx_hal.h"

typedef struct _sbusportdata{
  int channels[18];
  uint8_t failsafe;
  uint8_t lastendbyte;
  uint8_t laststartbyte;
  long lostframes;
  long goodframes;
  long lastframetime;
} sbusportdata_t;

int sbusDecode(char * buffer, sbusportdata_t *tar_sbus);

void sbusPrint(UART_HandleTypeDef *chan, sbusportdata_t *tar_sbus);
#endif
