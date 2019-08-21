/*
 * Author:          Pramuka Perera
 * Last Updated:    5 August 2019
 * Description:     
 */

#ifndef UART0_H
#define UART0_H

#include <stdint.h>
#include "uart0_regmap.h"

#define WLEN_8 3
#define WLEN_7 2
#define WLEN_6 1
#define WLEN_5 0

#define UART0_LCRH_WLEN 5
#define UART0_LCRH_FEN 4
#define UART0_LCRH_STICKY_PARITY 7
#define UART0_LCRH_PARITY 1
#define UART0_LCRH_BREAK 0

#define UART0_CR_RXE 9
#define UART0_CR_TXE 8
#define UART0_CR_UARTEN 0

#define UART0_FR_RXFE 4
#define UART0_FR_TXFF 5
#define UART0_FR_RXFF 6
#define UART0_FR_TXFE 7

#define BS 0x08 // \b
#define CR 0x0D // \r
#define NL 0x0A // \n

void uart0_init (void);

char uart0_getChar (void);

char uart0_echoChar (void);

void uart0_getString (char *str, uint32_t maxLength);

void uart0_putChar (char c);

void uart0_putString (char *str);

#endif

