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
  setbuf(stdout, NULL);

  cliOpen(_DEF_UART1, 57600);
}

void apMain(int argc, char *argv[])
{

  while(1)
  {
    cliMain();
  }
}

