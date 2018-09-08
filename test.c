/*
 * test.h
 *
 *  Created on: Aug 28, 2018
 *      Author: Team Redes Alejandro, Bernardo, Felipe, Luis... Ingenieros.
 */
#include <stdio.h>
#include <string.h>
#include "test.h"

const uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
const uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

void test_decrypt_cbc(uint8_t *buffer, uint32_t size)
{

    struct AES_ctx ctx;

    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_decrypt_buffer(&ctx, buffer, size);
    printf("CBC decrypt: ");
    printf("\n%s\n",buffer);
}

void test_encrypt_cbc(uint8_t *buffer, uint32_t size)
{
    
    struct AES_ctx ctx;

    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, buffer, size);

    printf("CBC encrypt: ");
    printf("\n%s\n",buffer);
}

