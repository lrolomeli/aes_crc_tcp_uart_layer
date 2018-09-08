/*
 * test.h
 *
 *  Created on: Aug 28, 2018
 *      Author: Team Redes Alejandro, Bernardo, Felipe, Luis... Ingenieros.
 */

#ifndef TEST_H_
#define TEST_H_

#include <stdint.h>

// Enable ECB, CTR and CBC mode. Note this can be done before including aes.h or at compile-time.
// E.g. with GCC by using the -D flag: gcc -c aes.c -DCBC=0 -DCTR=1 -DECB=1
#define CBC 1
#define CTR 0
#define ECB 0

#define BUFSIZE 64

#include "aes.h"

void test_encrypt_cbc(uint8_t *buffer, uint32_t size);
void test_decrypt_cbc(uint8_t *buffer, uint32_t size);

#endif /* TEST_H_ */
