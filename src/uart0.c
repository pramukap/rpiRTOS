#include "common.h"
#include "uart0.h"
#include "gpio.h"

void uart0_init (void) {
    // Disable UART0
	UART0_CR &= ~(1 << 0);		

	// disable pull-down/pull up resistors on tx/rx pins
//	GPIO_PUD.fields.pud = PUD_DISABLE;  
//	for (int i = 0; i < 200; i++) {}	// wait 150 cycles
//	GPIO_PUDCLK0.fields.pudclk14 = ON;
//	GPIO_PUDCLK0.fields.pudclk15 = ON;
//	for (int i = 0; i < 200; i++) {}	// wait 150 cycles
//	GPIO_PUDCLK0.fields.pudclk14 = OFF;
//	GPIO_PUDCLK0.fields.pudclk15 = OFF;

    // set alternate function 0
    GPIO_FSEL1 |= FSEL_ALT0 << FSEL_FIELD4; 
    GPIO_FSEL1 |= FSEL_ALT0 << FSEL_FIELD5; 

	// set baud rate (115200 baud, 3078144 Hz)
	UART0_IBRD = 1;
	UART0_FBRD = 40;

	// set packet options
	UART0_LCRH = 0x00000000;	// start with everything off
	UART0_LCRH |= WLEN_8 << 5;	// data length 8 bits

// 	UART0_IMSC.reg = 0x00000000; // start with everything off
// 	UART0_IMSC.reg = 0x0000007F2; // mask all interrupts

//	UART0_ICR.reg = 0x0000007F2; // clear all interrupts

	// flush fifos in order to program ctrl reg
	UART0_LCRH &= ~(1 << 4);
	// reenable fifos
	UART0_LCRH |= 1 << 4;

    // disable sticky parity, parity, and break
    UART0_LCRH &= ~(1 << 7);
    UART0_LCRH &= ~(1 << 1);
    UART0_LCRH &= ~(1 << 0);

	// program ctrl reg
	UART0_CR = 0x00000000;	// start with everything off
	UART0_CR |= 1 << 9;	// enable rx 
	UART0_CR |= 1 << 8;	// enable tx 
//    UART0_CR |= 1 << 7;	// enable loopback
	UART0_CR |= 1 << 0; // enable uart

}

void uart0_putChar (char c) {
	while (UART0_FR & (1 << 5));

	UART0_DR = c;
}

char uart0_getChar (void) {
	while (UART0_FR & (1 << 4));

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
	for (uint32_t i = 0; i < maxLength && (str[i] = uart0_getChar ()) != '\0'; i++);
}

