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

void uart0_putString (char *str) {
	uint32_t i;
    
    if (str == NULL) {
        return;
    }

	for (i = 0; str[i] != '\0'; i++) {
		uart0_putChar (str[i]);
	}

//	uart0_putChar (str[i]);
}

char uart0_getChar (void) {
	while (UART0_FR & (1 << UART0_FR_RXFE));

	return UART0_DR & 0x0FF; // Return 8 bits of data, and exclude error bits
}

char uart0_echoChar (void) {
    char c;
    c = uart0_getChar ();
    
    // modify output if enter or backspace is pressed
    switch (c) {
        // enter
        case CR:
            uart0_putString ("\n\r");
            break;
    
        // backspace
        case BS:
            uart0_putString ("\b \b");
            break;
    
        // everthing else
        default:
            uart0_putChar (c);
    };

    return c;
}

void uart0_getString (char *str, uint32_t maxLength) {
    uint32_t i;

    // remember i is the index
    i = 0;
	while (i < maxLength && (str[i] = uart0_echoChar ()) != CR) {
        if (str[i] == BS) {
            // go back two characters to 
            // overwrite the character that was deleted 
            // as well as the backspace character
            // that was just entered
            i -= 2; 
        }

        i++;
    }

    str[i] = '\0';  // null terminate the string
}

