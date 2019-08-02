#include "kernel.h"

int main () {
	uart0_init ();
	led_init ();	

	while (1) {
//		uart0_putString ("Hello World!\n\r");
//		c = uart0_getChar ();
		uart0_putChar ('c');
		led_toggle ();
        for (delayCount = 0; delayCount < 500000; delayCount++);
	}

	return 0;
}


