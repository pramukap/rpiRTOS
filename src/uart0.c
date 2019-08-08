/*
 * Author:          Pramuka Perera
 * Last Updated:    5 August 2019
 * Description:     Talk to laptop console via UART
 */

#include "common.h"
#include "uart0.h"
#include "gpio.h"

void uart0_init (void) {
    // Disable UART0
	UART0_CR &= ~(1 << UART0_CR_UARTEN);		

    // set alternate function 0
    GPIO_FSEL1 |= FSEL_ALT0 << FSEL_FIELD4; 
    GPIO_FSEL1 |= FSEL_ALT0 << FSEL_FIELD5; 

	// set baud rate (115200 baud, 3078144 Hz)
	UART0_IBRD = 1;
	UART0_FBRD = 40;

	// set packet options
	UART0_LCRH = 0x00000000;	// start with everything off
	UART0_LCRH |= WLEN_8 << UART0_LCRH_WLEN;	// data length 8 bits

	// flush fifos in order to program ctrl reg
	UART0_LCRH &= ~(1 << UART0_LCRH_FEN);

	// reenable fifos
	UART0_LCRH |= 1 << UART0_LCRH_FEN;

    // disable sticky parity, parity, and break
    UART0_LCRH &= ~(1 << UART0_LCRH_STICKY_PARITY);
    UART0_LCRH &= ~(1 << UART0_LCRH_PARITY);
    UART0_LCRH &= ~(1 << UART0_LCRH_BREAK);

	// program ctrl reg
	UART0_CR = 0x00000000;	// start with everything off
	UART0_CR |= 1 << UART0_CR_RXE;	// enable rx 
	UART0_CR |= 1 << UART0_CR_TXE;	// enable tx 
	UART0_CR |= 1 << UART0_CR_UARTEN; // enable uart
}

void uart0_putChar (char c) {
	while (UART0_FR & (1 << UART0_FR_TXFF));

	UART0_DR = c;
}

char uart0_getChar (void) {
	while (UART0_FR & (1 << UART0_FR_RXFE));

	return UART0_DR & 0x0FF; // Return 8 bits of data, and exclude error bits
}

void uart0_putString (char *str) {
	uint32_t i;

	for (i = 0; str[i] != '\0'; i++) {
		uart0_putChar (str[i]);
	}

	uart0_putChar (str[i]);
}

void uart0_getString (char *str, uint32_t maxLength) {
	for (uint32_t i = 0; i < maxLength && (str[i] = uart0_getChar ()) != '\r'; i++);
}

