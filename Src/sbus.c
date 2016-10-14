//SBUS FUNCTIONS

#include "sbus.h"
int sbusDecode(char * buffer, sbusportdata_t *tar_sbus)
{
  tar_sbus->channels[0]  = ((buffer[1]    |buffer[2]<<8)                 & 0x07FF);
  tar_sbus->channels[1]  = ((buffer[2]>>3 |buffer[3]<<5)                 & 0x07FF);
  tar_sbus->channels[2]  = ((buffer[3]>>6 |buffer[4]<<2 |buffer[5]<<10)  & 0x07FF);
  tar_sbus->channels[3]  = ((buffer[5]>>1 |buffer[6]<<7)                 & 0x07FF);
  tar_sbus->channels[4]  = ((buffer[6]>>4 |buffer[7]<<4)                 & 0x07FF);
  tar_sbus->channels[5]  = ((buffer[7]>>7 |buffer[8]<<1 |buffer[9]<<9)   & 0x07FF);
  tar_sbus->channels[6]  = ((buffer[9]>>2 |buffer[10]<<6)                & 0x07FF);
  tar_sbus->channels[7]  = ((buffer[10]>>5|buffer[11]<<3)                & 0x07FF);
  tar_sbus->channels[8]  = ((buffer[12]   |buffer[13]<<8)                & 0x07FF);
  tar_sbus->channels[9]  = ((buffer[13]>>3|buffer[14]<<5)                & 0x07FF);
  tar_sbus->channels[10] = ((buffer[14]>>6|buffer[15]<<2|buffer[16]<<10) & 0x07FF);
  tar_sbus->channels[11] = ((buffer[16]>>1|buffer[17]<<7)                & 0x07FF);
  tar_sbus->channels[12] = ((buffer[17]>>4|buffer[18]<<4)                & 0x07FF);
  tar_sbus->channels[13] = ((buffer[18]>>7|buffer[19]<<1|buffer[20]<<9)  & 0x07FF);
  tar_sbus->channels[14] = ((buffer[20]>>2|buffer[21]<<6)                & 0x07FF);
  tar_sbus->channels[15] = ((buffer[21]>>5|buffer[22]<<3)                & 0x07FF);

  if ((buffer[23] >> 3) & 0x0001) {
    tar_sbus->failsafe = 1;
  } else {
    tar_sbus->failsafe = 0;
  }

  if ((buffer[23] >> 2) & 0x0001) {
    tar_sbus->lostframes++;
  } else{
    tar_sbus->goodframes++;
  }

}
void sbusPrint(UART_HandleTypeDef *chan, sbusportdata_t *tar_sbus)
{
  {
    char bufsend[50];
    int len;
    sprintf(bufsend,"Current Data: ");
    len=strlen(bufsend);
    HAL_UART_Transmit(chan, bufsend, len, 1000);
  }

  for(int i = 0; i < 6; i++){
    //print out variable
    char bufsend[50];
    int len;
    sprintf(bufsend,"ch %d: %04d",i+1, tar_sbus->channels[i]);
    len=strlen(bufsend);
    HAL_UART_Transmit(chan, bufsend, len, 1000);
  }
  {
  char bufsend[50];
  int len;
  sprintf(bufsend,"Goodpk: %05d", tar_sbus->goodframes);
  len=strlen(bufsend);
  HAL_UART_Transmit(chan, bufsend, len, 1000);
  }
  {
    char bufsend[50];
    int len;
    sprintf(bufsend," Droppedpk: %05d", tar_sbus->lostframes);
    len=strlen(bufsend);
    HAL_UART_Transmit(chan, bufsend, len, 1000);
  }
  if(tar_sbus->failsafe){
    char bufsend[50];
    int len;
    sprintf(bufsend," FAILSAFE\n\r");
    len=strlen(bufsend);
    HAL_UART_Transmit(chan, bufsend, len, 1000);
  }else{
    char bufsend[50];
    int len;
    sprintf(bufsend," NOFAIL\n\r");
    len=strlen(bufsend);
    HAL_UART_Transmit(chan, bufsend, len, 1000);
  }

}
