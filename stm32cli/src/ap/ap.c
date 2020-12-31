/*
 * ap.c
 *
 *  Created on: Dec 6, 2020
 *      Author: baram
 */


#include "ap.h"
#include <conio.h>





void apInit(void)
{
  logPrintf("stm32cli v1.0\n\n");

  cliOpen(_DEF_UART1, 57600);
}

void apMain(int argc, char *argv[])
{

  while(1)
  {
    cliMain();
  }
}

void apExit(void)
{
  printf("cli exit\n");
  exit(0);
}
