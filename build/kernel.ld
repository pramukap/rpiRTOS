/*
 * Author:          Pramuka Perera
 * Last Updated:    17 Feb 2020
 * Description:     Memory Layout
 */

start = main;

SECTIONS
{
    /* 
     * * means all files, 
     * (.ivt) means .ivt sections in those files 
     */
    . = 0x00000000;
    .ivt : { *(.ivt) }  

    . = 0x00008000;
    .text.startup : { *(.text.startup) }
    .text : { *(.text) }
    .rodata : { *(.rodata) }
    .got : { *(.got) }
    .data : { *(.data) }
    .bss : { *(.bss) }
}


