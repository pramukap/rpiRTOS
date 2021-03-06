/*
 * Author:          Pramuka Perera
 * Last Updated:    5 August 2019
 * Description:     OS Kernel
 */

#include "kernel.h"

int main () {
   char c; 

	uart0_init ();
	led_init ();	

	while (1) {
        c = uart0_getChar ();

        // modify output if enter or backspace is pressed
        switch (c) {
            // enter
            case '\r':
                uart0_putString ("\n\r");
                break;

            // backspace
            case '\b':
                uart0_putString ("\b \b");
                break;

            // everthing else
            default:
                uart0_putChar (c);
        };

		led_toggle ();
        for (delayCount = 0; delayCount < 500000; delayCount++);
	}

	return 0;
}


