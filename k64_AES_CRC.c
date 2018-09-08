/*
 * k64_AES_CRC.c
 *
 *  Created on: Sep 5, 2018
 *      Author: Team Redes Alejandro, Bernardo, Felipe, Luis... Ingenieros.
 */
#include "k64_AES_CRC.h"

uart_rtos_handle_t handle;
struct _uart_handle t_handle;
uint8_t background_buffer[68];
uint8_t recv_buffer[68];

uart_rtos_config_t uart_config = {
    .baudrate = 115200,
    .parity = kUART_ParityDisabled,
    .stopbits = kUART_OneStopBit,
    .buffer = background_buffer,
    .buffer_size = sizeof(background_buffer),
};

void k64_aes_crc_send_uart(uint8_t *msg)
{

	uint32_t chksum;
	uint8_t * buffer = (uint8_t *) pvPortMalloc(64 * sizeof(uint8_t));

	strncpy((char *) buffer, (char *) msg, 64);

	chksum = get_crc32((char *)buffer, 64);
	test_encrypt_cbc(buffer, 64);

	memcpy(&buffer[64], &chksum, 4);

	uart_config.srcclk = DEMO_UART_CLK_FREQ;
	uart_config.base = DEMO_UART;

	if (0 > UART_RTOS_Init(&handle, &t_handle, &uart_config)) {
		vTaskSuspend(NULL);
	}

	/* Send introduction message. */
	if (0 > UART_RTOS_Send(&handle, buffer, 68)) {
		vTaskSuspend(NULL);
	}

	vPortFree(buffer);

	UART_RTOS_Deinit(&handle);
}

void k64_aes_crc_recv_uart()
{

	uint32_t checksum_crc_32;
    size_t n;

    uart_config.srcclk = DEMO_UART_CLK_FREQ;
    uart_config.base = DEMO_UART;
	if (0 > UART_RTOS_Init(&handle, &t_handle, &uart_config)) {
		vTaskSuspend(NULL);
	}
	UART_RTOS_Receive(&handle, recv_buffer, sizeof(recv_buffer), &n);

	memcpy(&checksum_crc_32,&recv_buffer[64],4);

	test_decrypt_cbc(recv_buffer, n);

	if(checkup_crc32((char *)recv_buffer, 64, checksum_crc_32))
	{
		printf("CRC32 Correct\n");
	}
	UART_RTOS_Deinit(&handle);

}

void k64_aes_crc_send_tcp(uint8_t *msg, uint8_t msg_size, uint16_t app_port)
{
	struct netconn *conn;
		ip_addr_t dst_ip;
	//	err_t err;
	//	uint32_t chksum;
	//	struct netbuf *buf;
	//	void *data;
	//	u16_t len;
		uint32_t chksum;



		uint8_t * buffer = (uint8_t *)pvPortMalloc(msg_size * sizeof(uint8_t));

		strncpy((char *)buffer, (char *)msg, msg_size);

		chksum = get_crc32((char *)buffer, msg_size-4);

		test_encrypt_cbc(buffer, msg_size);

		memcpy(&buffer[msg_size-4], &chksum, 4);

		IP4_ADDR(&dst_ip, 192, 168, 0, 100);

		/* Create a new connection identifier. */
		conn = netconn_new(NETCONN_TCP);

		LWIP_ERROR("tcpecho: invalid conn", (conn != NULL), return;);

		netconn_connect(conn, &dst_ip, app_port);
		/* Process the new connection. */
		/*err = */netconn_write(conn,(void *) buffer, msg_size, NETCONN_COPY);

	//	if ((err = netconn_recv(conn, &buf)) == ERR_OK)
	//	{
	//		netbuf_data(buf, &data, &len);
	//		printf("%s", (char *) data);
	//	}
		netconn_close(conn);
		netconn_delete(conn);

		vPortFree(buffer);

}

void k64_aes_crc_recv_tcp(uint16_t app_port) {
	struct netconn *conn, *newconn;
	uint32_t checksum_crc_32;
	err_t err;
	struct netbuf *buf;
	void *data;
	uint8_t *p;
	u16_t len;

	/* Create a new connection identifier. */
	conn = netconn_new(NETCONN_TCP);
	netconn_bind(conn, IP_ADDR_ANY, app_port);
	LWIP_ERROR("tcpecho: invalid conn", (conn != NULL), return;);

	/* Tell connection to go into listening mode. */
	netconn_listen(conn);

	while (1) {
		/* Grab new connection. */
		err = netconn_accept(conn, &newconn);
		printf("C.A.\n");
		/* Process the new connection. */
		if (err == ERR_OK) {

			while ((err = netconn_recv(newconn, &buf)) == ERR_OK) {
				do {
					netbuf_data(buf, &data, &len);
					p = (uint8_t*)data;
					memcpy(&checksum_crc_32, &(p[len-4]), 4);
					test_decrypt_cbc(p, (uint8_t) len);
					if(checkup_crc32((char *)data, len-4, checksum_crc_32))
					{
						printf("CRC32 Correct\n");
					}
					//err = netconn_write(newconn, data, len, NETCONN_COPY);
				} while (netbuf_next(buf) >= 0);
				netbuf_delete(buf);
			}
			/* Close connection and discard connection identifier. */
			netconn_close(newconn);
			netconn_delete(newconn);
		}
	}
}

