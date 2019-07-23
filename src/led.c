#include "led.h"

void led_init (void) {
	GPIO_FSEL4 = FSEL_OUTPUT << FSEL_FIELD7; // set pin 47 as output
}

void led_toggle (void) {
	if (GPIO_LEV1 & (1 << LED_BIT)) {		// read state of led
		GPIO_CLR1 |= 1 << LED_BIT;	// turn led on
	} else {
		GPIO_SET1 |= 1 << LED_BIT;	// turn led off
	}
}

