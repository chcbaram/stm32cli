/*
 * boot.c
 *
 *  Created on: 2021. 2. 6.
 *      Author: baram
 */


#include "boot.h"



#define BOOT_CMD_READ_BOOT_VERSION      0x00
#define BOOT_CMD_READ_BOOT_NAME         0x01
#define BOOT_CMD_READ_FIRM_VERSION      0x02
#define BOOT_CMD_READ_FIRM_NAME         0x03
#define BOOT_CMD_LED_CONTROL            0x10




static cmd_t cmd;



bool bootInit(uint8_t channel, char *port_name, uint32_t baud)
{
  bool ret = true;


  cmdInit(&cmd);

  uartSetPortName(channel, port_name);

  ret = cmdOpen(&cmd, channel, baud);


  return ret;
}

bool bootDeInit(uint8_t channel)
{
  return true;
}

uint8_t bootCmdReadBootVersion(uint8_t *p_version)
{
  bool ret;
  uint8_t errcode = CMD_OK;
  cmd_t *p_cmd = &cmd;

  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_READ_BOOT_VERSION, NULL, 0, 500);
  if (ret == true && p_cmd->error == CMD_OK)
  {
    for (int i=0; i<p_cmd->rx_packet.length; i++)
    {
      p_version[i] = p_cmd->rx_packet.data[i];
    }
  }
  else
  {
    errcode = p_cmd->error;
  }

  return errcode;
}

uint8_t bootCmdReadBootName(uint8_t *p_str)
{
  bool ret;
  uint8_t errcode = CMD_OK;
  cmd_t *p_cmd = &cmd;

  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_READ_BOOT_NAME, NULL, 0, 500);
  if (ret == true && p_cmd->error == CMD_OK)
  {
    for (int i=0; i<p_cmd->rx_packet.length; i++)
    {
      p_str[i] = p_cmd->rx_packet.data[i];
    }
  }
  else
  {
    errcode = p_cmd->error;
  }

  return errcode;
}

uint8_t bootCmdReadFirmVersion(uint8_t *p_version)
{
  bool ret;
  uint8_t errcode = CMD_OK;
  cmd_t *p_cmd = &cmd;

  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_READ_FIRM_VERSION, NULL, 0, 500);
  if (ret == true && p_cmd->error == CMD_OK)
  {
    for (int i=0; i<p_cmd->rx_packet.length; i++)
    {
      p_version[i] = p_cmd->rx_packet.data[i];
    }
  }
  else
  {
    errcode = p_cmd->error;
  }

  return errcode;
}

uint8_t bootCmdReadFirmName(uint8_t *p_str)
{
  bool ret;
  uint8_t errcode = CMD_OK;
  cmd_t *p_cmd = &cmd;

  ret = cmdSendCmdRxResp(p_cmd, BOOT_CMD_READ_FIRM_NAME, NULL, 0, 500);
  if (ret == true && p_cmd->error == CMD_OK)
  {
    for (int i=0; i<p_cmd->rx_packet.length; i++)
    {
      p_str[i] = p_cmd->rx_packet.data[i];
    }
  }
  else
  {
    errcode = p_cmd->error;
  }

  return errcode;
}
