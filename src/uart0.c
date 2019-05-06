#include "common.h"
#include "uart0.h"
#include "gpio.h"

void uart0_init (void) {
	UART0_CR.fields.uarten = OFF;		
	UART0_CR.fields.txe = OFF;

	// disable pull-down/pull up resistors on tx/rx pins
	GPIO_PUD.fields.pud = PUD_DISABLE;  
	for (int i = 0; i < 200; i++) {}	// wait 150 cycles
	GPIO_PUDCLK0.fields.pudclk14 = ON;
	GPIO_PUDCLK0.fields.pudclk15 = ON;
	for (int i = 0; i < 200; i++) {}	// wait 150 cycles
	GPIO_PUDCLK0.fields.pudclk14 = OFF;
	GPIO_PUDCLK0.fields.pudclk15 = OFF;

	// set baud rate (115200 baud, 3078144 Hz)
	UART0_IBRD.fields.ibrd = 1;
	UART0_FBRD.fields.fbrd = 40;
	// set packet options
	UART0_LCRH.reg = 0x00000000;	// start with everything off
	UART0_LCRH.fields.wlen = WLEN_8;	// data length 8 bits

	UART0_IMSC.reg = 0x00000000; // start with everything off
	UART0_IMSC.reg = 0x0000007F2; // mask all interrupts

	UART0_ICR.reg = 0x0000007F2; // clear all interrupts

	// flush fifos in order to program ctrl reg
	UART0_LCRH.fields.fen = OFF;

	// program ctrl reg
	UART0_CR.reg = 0x00000000;	// start with everything off
	UART0_CR.fields.rxe = ON;	// enable rx 
	UART0_CR.fields.txe = ON;	// enable tx 
	UART0_CR.fields.uarten = ON;

	// reenable fifos
	UART0_LCRH.fields.fen = ON;
}

void uart0_putChar (char c) {
	while (UART0_FR.fields.txff) {}

	UART0_DR.fields.data = c;
}

char uart0_getChar (void) {
	while (UART0_FR.fields.rxfe) {}

	return UART0_DR.fields.data;
}

void uart0_putString (char *str) {
	uint32_t i;

	for (i = 0; str[i] != '\0'; i++) {
		uart0_putChar (str[i]);
	}

	uart0_putChar (str[i]);
}

void uart0_getString (char *str, uint32_t maxLength) {
	for (uint32_t i = 0; i < maxLength && (str[i] = uart0_getChar ()) != '\0'; i++) {}
}

