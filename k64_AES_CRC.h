/*
 * k64_AES_CRC.h
 *
 *  Created on: Sep 5, 2018
 *      Author: Team Redes Alejandro, Bernardo, Felipe, Luis... Ingenieros.
 */

#ifndef K64_AES_CRC_H_
#define K64_AES_CRC_H_

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_port.h"

#include "fsl_uart_freertos.h"
#include "fsl_uart.h"

#include "pin_mux.h"
#include "clock_config.h"

#include "test.h"
#include "crc.h"

#include "lwip/opt.h"

#include "lwip/sys.h"
#include "lwip/api.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#include "FreeRTOSConfig.h"
/* UART instance and clock */
#define DEMO_UART UART1
#define DEMO_UART_CLKSRC UART1_CLK_SRC
#define DEMO_UART_CLK_FREQ CLOCK_GetFreq(UART1_CLK_SRC)
#define DEMO_UART_RX_TX_IRQn UART1_RX_TX_IRQn
/* Task priorities. */
#define uart_task_PRIORITY (configMAX_PRIORITIES - 1)

void k64_aes_crc_send_uart(uint8_t *msg);

void k64_aes_crc_recv_uart();

void k64_aes_crc_send_tcp(uint8_t *msg, uint8_t msg_size, uint16_t app_port);

void k64_aes_crc_recv_tcp(uint16_t app_port);

#endif /* K64_AES_CRC_H_ */
