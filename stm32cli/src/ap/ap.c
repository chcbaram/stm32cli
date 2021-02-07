/*
 * ap.c
 *
 *  Created on: Dec 6, 2020
 *      Author: baram
 */


#include "ap.h"
#include "boot/boot.h"


enum
{
  FILE_TYPE_FW,
  FILE_TYPE_BIN,
};



int32_t getFileSize(char *file_name);



void apInit(void)
{
  logPrintf("stm32cli v1.0\n\n");

  cliOpen(_DEF_UART1, 57600);
}

void apMain(int argc, char *argv[])
{
  bool ret;
  uint8_t err_code;
  uint8_t  uart_ch;
  char    *uart_port;
  uint32_t uart_baud;
  uint8_t boot_ver[32];
  uint8_t boot_name[32];
  uint8_t firm_ver[32];
  uint8_t firm_name[32];
  uint32_t pre_time;
  uint32_t exe_time;
  uint8_t  file_type;
  uint32_t file_addr;
  int32_t  file_size;
  char     file_name[256];
  bool     file_run;


  if (argc != 7)
  {
    logPrintf("stm32cli com1 57600 type[fw:bin] 0x8010000 file_name run[0:1]\n");
    apExit();
  }


  //-- 파라메터 처리
  //
  uart_ch   = _DEF_UART2;
  uart_port = argv[1];
  uart_baud = (int32_t)strtoul(argv[2], (char **)NULL, (int) 0);

  logPrintf("uart ch   : %d\n", uart_ch);
  logPrintf("uart port : %s\n", uart_port);
  logPrintf("uart baud : %d bps\n", uart_baud);


  if (strcmp(argv[3], "fw") == 0)
  {
    file_type = FILE_TYPE_FW;
    logPrintf("file type : firmware\n");
  }
  else if (strcmp(argv[3], "bin") == 0)
  {
    file_type = FILE_TYPE_BIN;
    logPrintf("file type : binary\n");
  }
  else
  {
    logPrintf("file type error\n");
    apExit();
  }

  file_addr = (uint32_t)strtoul(argv[4], (char **)NULL, (int) 0);
  logPrintf("file addr : 0x%X\n", file_addr);

  strcpy(file_name, argv[5]);
  logPrintf("file name : %s\n", file_name);

  file_size = getFileSize(file_name);
  if (file_size <= 0)
  {
    logPrintf("file size error\n");
    apExit();
  }
  logPrintf("file size : %d bytes\n", file_size);


  //-- boot 시작
  //
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
    err_code = bootCmdReadBootVersion(boot_ver);
    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdReadBootVersion fail : %d\n", err_code);
      break;
    }
    logPrintf("boot ver \t: %s\n",  boot_ver);


    //-- 부트로더 이름 읽기
    //
    err_code = bootCmdReadBootName(boot_name);
    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdReadBootName fail : %d\n", err_code);
      break;
    }
    logPrintf("boot name \t: %s\n", boot_name);


    //-- 펌웨어 버전 읽기
    //
    err_code = bootCmdReadFirmVersion(firm_ver);
    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdReadFirmVersion fail : %d\n", err_code);
      break;
    }
    logPrintf("firm ver \t: %s\n",  firm_ver);


    //-- 펌웨어 이름 읽기
    //
    err_code = bootCmdReadFirmName(firm_name);
    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdReadFirmName fail : %d\n", err_code);
      break;
    }
    logPrintf("firm name \t: %s\n", firm_name);


    //-- Flash Erase
    //
    pre_time = millis();
    err_code = bootCmdFlashErase(0x8010000, (512-64)*1024, 5000);
    exe_time = millis()-pre_time;
    if (err_code != CMD_OK)
    {
      logPrintf("bootCmdFlashErase fail : %d\n", err_code);
      break;
    }
    logPrintf("flash erase \t: OK (%dms)\n", exe_time);



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

int32_t getFileSize(char *file_name)
{
  int32_t ret = -1;
  FILE *fp;

  if ((fp = fopen( file_name, "rb")) == NULL)
  {
    fprintf( stderr, "Unable to open %s\n", file_name );
    return -1;
  }
  else
  {
    fseek( fp, 0, SEEK_END );
    ret = ftell( fp );
    fclose(fp);
  }

  return ret;
}
