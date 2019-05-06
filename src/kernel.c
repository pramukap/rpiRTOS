#include "uart0.h"

int kernel_main () {
	char c;
	uart0_init ();
	
	while (1) {
		uart0_putString ("Hello World!\n\r");
		// c = uart0_getChar ();
		// uart0_putChar (c);
	}
	return 0;
}


