/*
 * crc.h
 *
 *  Created on: Sep 4, 2018
 *      Author: luisr
 */

#ifndef CRC_H_
#define CRC_H_

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "fsl_crc.h"

#include "pin_mux.h"
#include "clock_config.h"

uint32_t get_crc32(char *msg, uint16_t size);
uint8_t checkup_crc32(char *msg, uint16_t size, uint32_t expected);

#endif /* CRC_H_ */
