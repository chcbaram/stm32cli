/*
 * ap.c
 *
 *  Created on: Dec 6, 2020
 *      Author: baram
 */


#include "ap.h"



cmd_t cmd;


void apInit(void)
{
  logPrintf("stm32cli v1.0\n\n");

  cliOpen(_DEF_UART1, 57600);

  cmdInit(&cmd);
}

void apMain(int argc, char *argv[])
{
  uint8_t  uart_ch;
  char    *uart_port;
  uint32_t uart_baud;


  if (argc != 3)
  {
    logPrintf("wrong args\n");
    apExit();
  }

  uart_ch   = _DEF_UART2;
  uart_port = argv[1];
  uart_baud = (int32_t)strtoul(argv[2], (char **)NULL, (int) 0);

  logPrintf("uart ch   : %d\n", uart_ch);
  logPrintf("uart port : %s\n", uart_port);
  logPrintf("uart baud : %d bps\n", uart_baud);

  if (uartOpenPort(uart_ch, uart_port, uart_baud) == true)
  {
    logPrintf("uart open : OK\n");
  }
  else
  {
    logPrintf("uart open : Fail\n");
    apExit();
  }

  cmdOpen(&cmd, _DEF_UART2, 57600);


  while(1)
  {
    //cliMain();

    if (uartAvailable(_DEF_UART1) > 0)
    {
      uint8_t rx_data;

      rx_data = uartRead(_DEF_UART1);

      if (rx_data == '1')
      {
        uint8_t tx_data;

        tx_data = 1;
        cmdSendCmd(&cmd, 0x10, &tx_data, 1);
        printf("LED ON\n");
      }

      if (rx_data == '2')
      {
        uint8_t tx_data;

        tx_data = 0;
        cmdSendCmd(&cmd, 0x10, &tx_data, 1);
        printf("LED OFF\n");
      }
    }
  }
}

void apExit(void)
{
  for (int i=0; i<UART_MAX_CH; i++)
  {
    uartClose(i);
  }
  printf("\ncli exit\n");
  exit(0);
}

