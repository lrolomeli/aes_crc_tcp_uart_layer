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
#define CHKSUM_SIZE_BYTES 4

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function sends a buffer of data through UART 1 using PORTC PIN 3 AND 4.
 	 \This only works inside of a FreeRTOS TASK and the only thing you need is a pointer
 	 \to a buffer and the size of that buffer, and the initialization of LWIP.
 	 \It uses AES encrypt CBC of 128 bytes and CRC32 for security reasons but also to be
 	 \sure that the message is correct and there is no corruption on it.
 	 \param[in] pointer to a uint8_t buffer.
 	 \param[in] number of elements in the message or array buffer, plus the size of CRC32
 	 \checksum variable measured in [BYTES]. example 32 bits variable are 4 bytes.
 	 \NOTE: the array size should be the same as the [message size] + [checksum size].
 	 \If the size of the message is 64 bytes and the size of checksum is 4 bytes. Then the
 	 \array must be 68 bytes length.
 	 \return void
 */
void k64_aes_crc_send_uart(uint8_t *msg, uint8_t size);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function uses UART for receiving a buffer of data.
 	 \This buffer contains an encrypted message and the CRC32 validation,
 	 \to prevent receiving a corrupted data buffer. Using AES CBC 128
 	 \decryption to obtain the real message. (it has to be contained on a FreeRTOS TASK)
 	 \param[in] none.
 	 \return void
 */
void k64_aes_crc_recv_uart();

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function sends a buffer of data over LWIP stack using TCP transport layer.
 	 \This only works inside of a FreeRTOS TASK and the only thing you need is a pointer
 	 \to a buffer and the size of that buffer, and the initialization of LWIP.
 	 \It uses AES encrypt CBC of 128 bytes and CRC32 for security reasons but also to be
 	 \sure that the message is correct and there is no corruption on it.
 	 \param[in] pointer to a uint8_t buffer.
 	 \param[in] number of elements in the message or array buffer, plus the size of CRC32
 	 \checksum variable measured in [BYTES]. example 32 bits variable are 4 bytes.
 	 \NOTE: the array size should be the same as the [message size] + [checksum size].
 	 \If the size of the message is 64 bytes and the size of checksum is 4 bytes. Then the
 	 \array must be 68 bytes length.
 	 \param[in] the number of port application you want to connect with.
 	 \return void. Works as a TCP CLIENT.
 */
void k64_aes_crc_send_tcp(uint8_t *msg, uint8_t msg_size, uint16_t app_port);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function uses TCP for receiving a buffer of data. It works as a SERVER.
 	 \This buffer contains an encrypted message and the CRC32 validation,
 	 \to prevent receiving a corrupted data buffer. Using AES CBC 128
 	 \decryption to obtain the real message. (has to be contained on a FreeRTOS TASK)
 	 \param[in] none.
 	 \return void
 */
void k64_aes_crc_recv_tcp(uint16_t app_port);

#endif /* K64_AES_CRC_H_ */
