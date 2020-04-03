/*
 * Author:          Pramuka Perera
 * Last Updated:    17 Feb 2020
 * Description:     Interrupt vector table and handlers
 */

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stddef.h>
#include <stdint.h>

#include "led.h"
#include "uart0.h"

#define NUM_INTERRUPTS 20

void interrupts_defaultHandler (void) __attribute__((interrupt ("SWI")));

void interrupts_enable (void);

void interrupts_disable (void);

void interrupts_svc (void);

void asmInterrupts_initVectorTable (void);
#endif

