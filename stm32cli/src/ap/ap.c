/*
 * ap.c
 *
 *  Created on: Dec 6, 2020
 *      Author: baram
 */


#include "ap.h"
#include "boot/boot.h"





void apInit(void)
{
  logPrintf("stm32cli v1.0\n\n");

  cliOpen(_DEF_UART1, 57600);
}

void apMain(int argc, char *argv[])
{
  bool ret;
  uint8_t errcode;
  uint8_t  uart_ch;
  char    *uart_port;
  uint32_t uart_baud;
  uint8_t boot_ver[32];
  uint8_t boot_name[32];
  uint8_t firm_ver[32];
  uint8_t firm_name[32];



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


  ret = bootInit(uart_ch, uart_port, uart_baud);
  if (ret != true)
  {
    logPrintf("bootInit Fail\n");
    apExit();
  }

  logPrintf("\n\nboot start...\n");

  while(1)
  {
    //-- 부트로더 버전 읽기
    //
    errcode = bootCmdReadBootVersion(boot_ver);
    if (errcode != CMD_OK)
    {
      logPrintf("bootCmdReadBootVersion fail : %d\n", errcode);
      break;
    }
    logPrintf("boot ver \t: %s\n",  boot_ver);


    //-- 부트로더 이름 읽기
    //
    errcode = bootCmdReadBootName(boot_name);
    if (errcode != CMD_OK)
    {
      logPrintf("bootCmdReadBootName fail : %d\n", errcode);
      break;
    }
    logPrintf("boot name \t: %s\n", boot_name);


    //-- 펌웨어 버전 읽기
    //
    errcode = bootCmdReadFirmVersion(firm_ver);
    if (errcode != CMD_OK)
    {
      logPrintf("bootCmdReadFirmVersion fail : %d\n", errcode);
      break;
    }
    logPrintf("firm ver \t: %s\n",  firm_ver);


    //-- 펌웨어 이름 읽기
    //
    errcode = bootCmdReadFirmName(firm_name);
    if (errcode != CMD_OK)
    {
      logPrintf("bootCmdReadFirmName fail : %d\n", errcode);
      break;
    }
    logPrintf("firm name \t: %s\n", firm_name);




    break;
  }


  apExit();
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

