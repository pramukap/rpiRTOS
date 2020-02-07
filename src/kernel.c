/*
 * Author:          Pramuka Perera
 * Last Updated:    5 August 2019
 * Description:     OS Kernel
 */

#include "kernel.h"

int main () {
    char str[150];
    str[149] = '\0';

    uart0_init ();
	led_init ();	
    heap_init ();

//    uart0Test_longIntString ();

    heapTest_allocFail ();
    heapTest_dataAlignment ();
    heapTest_recycleMemory ();
    heapTest_twoArrays ();
    heapTest_freeBlockTooSmall ();
    heapTest_freeBlockGoldilocks ();
    heapTest_currAbsorbsNext (); 
    heapTest_currAbsorbedByPrev (); 

//    heap_dump();
    uart0_putString (
        intToString (stringToInt ("1221221221"), str, 100)
    );
    uart0_putString ("\n\r");

	while (1) {
        uart0_getString (str, 100);

 		led_toggle ();
        for (delayCount = 0; delayCount < 500000; delayCount++);
	}

	return 0;
}

