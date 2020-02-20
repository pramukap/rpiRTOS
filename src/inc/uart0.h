/*
 * Author:          Pramuka Perera
 * Last Updated:    5 August 2019
 * Description:     
 */

#ifndef UART0_H
#define UART0_H

#include <stdint.h>

#include "common.h"
#include "gpio.h"
#include "uart0_regmap.h"
#include "compile.h"

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

#define UART0_IMSC_OEIM 10
#define UART0_IMSC_BEIM 9
#define UART0_IMSC_PEIM 8
#define UART0_IMSC_FEIM 7
#define UART0_IMSC_RTIM 6
#define UART0_IMSC_TXIM 5
#define UART0_IMSC_RXIM 4
#define UART0_IMSC_DCDMIM 2
#define UART0_IMSC_CTSMIM 1

#define UART0_IFLS_RXIFLSEL 3
#define UART0_IFLS_TXIFLSEL 0

#define EIGHTH_FULL 0
#define QUARTER_FULL 1
#define HALF_FULL 2
#define THREE_QUARTERS_FULL 3
#define SEVEN_EIGHTHS_FULL 4

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

