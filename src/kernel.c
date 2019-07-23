//#include "uart0.h"
#include "led.h"

volatile uint32_t i;

int main () {
//	char c;
//	uart0_init ();
	led_init ();	

	while (1) {
//		uart0_putString ("Hello World!\n\r");
//		c = uart0_getChar ();
//		uart0_putChar (c);
//		led_toggle ();
		for (i = 0; i < 500000; i++);
		GPIO_SET1 = 1 << 15;
		for (i = 0; i < 500000; i++);
		GPIO_CLR1 = 1 << 15;
	}

	return 0;
}


