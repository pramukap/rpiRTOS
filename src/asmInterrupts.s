/*
 * Author:          Pramuka Perera
 * Last Updated:    2 March 2020
 * Description:     Interrupt vector table
 */

#include "interrupts.h"

.section ".text"
.globl interruptVectorTable 
interruptVectorTable:
    ldr pc, interrupts_defaultHandlerAddr 
    ldr pc, interrupts_defaultHandlerAddr 
    ldr pc, interrupts_defaultHandlerAddr 
    ldr pc, interrupts_defaultHandlerAddr 
    ldr pc, interrupts_defaultHandlerAddr 
    nop
    ldr pc, interrupts_defaultHandlerAddr 
    ldr pc, interrupts_defaultHandlerAddr 

interrupts_defaultHandlerAddr: .word interrupts_defaultHandler

.globl asmInterrupts_initVectorTable
asmInterrupts_initVectorTable:
    push    {r4, r5, r6, r7, r8, r9}

    // move vector table to address 0
    ldr     r0, =interruptVectorTable
    mov     r1, #0
    ldmia   r0!, {r2, r3, r4, r5, r6, r7, r8, r9} 
    stmia   r1!, {r2, r3, r4, r5, r6, r7, r8, r9}

    // move interrupt handler addresses next to vector table
    ldmia   r0!, {r2}
    stmia   r1!, {r2}

    pop     {r4, r5, r6, r7, r8, r9}
    blx     lr

