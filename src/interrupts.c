/*
 * Author:          Pramuka Perera
 * Last Updated:    17 Feb 2020
 * Description:     Interrupt vector table and handlers
 */

#include "interrupts.h"

// setting PRIMASK[PM] to 1 raises the priority
// of the currently running thread to 0,
// preventing anything other than a reset, hard fault,
// or NMI from interrupting it
void interrupts_enable (void) {
    asm ("cpsie if");   // masks IRQs and FIQs
}

void interrupts_disable (void) {
    asm ("cpsid if");   // unmaks IRQs and FIQs
}

void interrupts_svc (void) {
    asm ("svc 0");
}

void interrupts_defaultHandler (void) {
    int i;

    uart0_putString ("hiiiiiiiiiiiiiiiiiiiiii\n");

    while (1) {
        led_toggle ();

        for (i = 0; i < 500000; i++) {}
    }

    return;
}

