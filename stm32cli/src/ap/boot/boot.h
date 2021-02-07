/*
 * boot.h
 *
 *  Created on: 2021. 2. 6.
 *      Author: baram
 */

#ifndef SRC_AP_BOOT_BOOT_H_
#define SRC_AP_BOOT_BOOT_H_

#include "hw.h"


bool bootInit(uint8_t channel, char *port_name, uint32_t baud);
bool bootDeInit(uint8_t channel);


uint8_t bootCmdReadBootVersion(uint8_t *p_version);
uint8_t bootCmdReadBootName(uint8_t *p_str);
uint8_t bootCmdReadFirmVersion(uint8_t *p_version);
uint8_t bootCmdReadFirmName(uint8_t *p_str);
uint8_t bootCmdFlashErase(uint32_t addr, uint32_t length, uint32_t timeout);


#endif /* SRC_AP_BOOT_BOOT_H_ */
