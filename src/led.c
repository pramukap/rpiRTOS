#include "led.h"

void led_init (void) {
	GPIO_FSEL4 = FSEL_OUTPUT << FSEL_FIELD7; // set pin 47 as output
}

void led_toggle (void) {
//	if ((GPIO_LEV1 & (1 << 15))) {		// read state of led
//		GPIO_CLR1 |= 1 << 15;	// turn led on
//	} else {
//		GPIO_SET1 |= 1 << 15;	// turn led off
//	}

	GPIO_CLR1 |= 1 << 15;
	for (int i = 0; i < 500000; i++) {}
	GPIO_SET1 |= 1 << 15;
	for (int i = 0; i < 500000; i++) {}
}

