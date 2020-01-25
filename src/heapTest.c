/*
 * Author:          Pramuka Perera
 * Last Updated:    9 December 2019
 * Description:     Functions to validate heap
 */

#include "heapTest.h"

#define STR_SIZE 100
#define STR_LEN 50 

char str[STR_SIZE];

void heapTest_dataAlignment (void) {

}

/*
 * Allocate a 10 byte array, and write to the first byte
 * Free the array
 * Create a new 10 byte array, and read the first byte
 * The read value should be equal to the write value
 */
void heapTest_recycleMemory (void) {
    uint8_t *arr1 = NULL, *arr2 = NULL;
    uint32_t arr1Addr, arr2Addr;
    uint8_t arr1Val;

    uart0_putString ("Running \"Recycle Memory\" Test:\n\r");

    arr1 = (uint8_t *)(heap_allocate (10*sizeof(uint8_t)));
    arr1Addr = (uint32_t)arr1;
    arr1[0] = arr1Val = 5;

    heap_free (arr1);
    arr1 = NULL;

    arr2 = (uint8_t *)(heap_allocate (10*sizeof(uint8_t)));
    arr2Addr = (uint32_t)arr2;

    if (arr2Addr != arr1Addr) {
        uart0_putString ("Test failed!\n\r");

        uart0_putString ("arr1[0] address: ");
        uart0_putString (intToString (arr1Addr, str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("arr1[0]: ");
        uart0_putChar (arr1Val + '0');
        uart0_putString ("\n\r");

        uart0_putString ("arr2[0] address: ");
        uart0_putString (intToString (arr2Addr, str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("arr2[0]: ");
        uart0_putChar (arr2[0] + '0');
        uart0_putString ("\n\r");

        heap_free (arr2);
        arr2 = NULL;

        return;
    }
        
    heap_free (arr2);
    arr2 = NULL;

    uart0_putString ("Test passed!\n\r");
}


void heapTest_twoArrays (void) {
    uint8_t *arr1 = NULL, *arr2 = NULL;
    uint32_t arr1Addr, arr2Addr;

    uart0_putString ("Running \"Two Arrays\" Test:\n\r");

    arr1 = (uint8_t *)(heap_allocate (10 * sizeof(uint8_t)));
    arr1Addr = (uint32_t)arr1;

    arr2 = (uint8_t *)(heap_allocate (10 * sizeof(uint8_t)));
    arr2Addr = (uint32_t)arr2;
    
    heap_free (arr1);
    arr1 = NULL;
    heap_free (arr2);
    arr2 = NULL;

    if (arr2Addr != (arr1Addr + (10 * sizeof (uint8_t)) + sizeof(heapData))) {
        uart0_putString ("Test failed!\n\r");

        uart0_putString ("arr1[0] address: ");
        uart0_putString (intToString (arr1Addr, str, STR_LEN));
        uart0_putString ("\n\r");

        uart0_putString ("Expected arr2[0] address: ");
        uart0_putString (intToString (arr1Addr + (10 * sizeof (uint8_t)) + sizeof(heapData), str, STR_LEN));
        uart0_putString ("\n\r");

        uart0_putString ("Actual arr2[0] address: ");
        uart0_putString (intToString (arr2Addr, str, STR_LEN));
        uart0_putString ("\n\r");

        return;
    }

    uart0_putString ("Test passed!\n\r");
}


void heapTest_freeBlockTooSmall (void) {
    uint8_t *arr1 = NULL, *arr2 = NULL, *arr3 = NULL, *arr4 = NULL;
    uint32_t arr1Addr, arr2Addr, arr3Addr, arr4Addr;

    uart0_putString ("Running \"Free Block Too Small\" Test:\n\r");

    arr1 = (uint8_t *)(heap_allocate (10 * sizeof(uint8_t)));
    arr1Addr = (uint32_t)arr1;

    arr2 = (uint8_t *)(heap_allocate (10 * sizeof(uint8_t)));
    arr2Addr = (uint32_t)arr2;

    arr3 = (uint8_t *)(heap_allocate (10 * sizeof(uint8_t)));
    arr3Addr = (uint32_t)arr3;

    heap_free (arr2);
    arr2 = NULL;

    arr4 = (uint8_t *)(heap_allocate (11 * sizeof(uint8_t)));
    arr4Addr = (uint32_t)arr4;

    heap_free (arr1);
    arr1 = NULL;
    heap_free (arr2);
    arr2 = NULL;
    heap_free (arr3);
    arr3 = NULL;
    heap_free (arr4);
    arr4 = NULL;

    if (arr4Addr != arr3Addr + (8 * sizeof (uint8_t)) + sizeof(heapData)) {
        uart0_putString ("Test failed!\n\r");

        uart0_putString ("arr1[0] address: ");
        uart0_putString (intToString (arr1Addr, str, STR_LEN));
        uart0_putString ("\n\r");

        uart0_putString ("arr2[0] address: ");
        uart0_putString (intToString (arr2Addr, str, STR_LEN));
        uart0_putString ("\n\r");

        uart0_putString ("arr3[0] address: ");
        uart0_putString (intToString (arr3Addr, str, STR_LEN));
        uart0_putString ("\n\r");

        uart0_putString ("Expected arr4[0] address: ");
        uart0_putString (intToString (arr3Addr + (10 * sizeof (uint8_t)) + sizeof(heapData), str, STR_LEN));
        uart0_putString ("\n\r");

        uart0_putString ("Actual arr4[0] address: ");
        uart0_putString (intToString (arr4Addr, str, STR_LEN));
        uart0_putString ("\n\r");

        return;
    }

    uart0_putString ("Test passed!\n\r");
}


void heapTest_currAbsorbsNext (void) {
    uint8_t *arr1 = NULL, *arr2 = NULL, *arr3 = NULL;
    uint32_t arr1Addr, arr2Addr, arr3Addr;

    uart0_putString ("Running \"Free Block Too Small\" Test:\n\r");

    arr1 = (uint8_t *)(heap_allocate (10 * sizeof(uint8_t)));
    arr1Addr = (uint32_t)arr1;

    arr2 = (uint8_t *)(heap_allocate (10 * sizeof(uint8_t)));
    arr2Addr = (uint32_t)arr2;

    arr2[0] = 'd';

    // arr2 block absorbs free block that comes after
    heap_free (arr2);
    arr2 = NULL;

    // arr1 (current) absorbs free block that includes the old arr2 block
    heap_free (arr1);
    arr1 = NULL;

    // arr3 should be made of arr1 and half of arr2
    arr3 = (uint8_t *)(heap_allocate ((10 + sizeof(heapData) + 5) * sizeof(uint8_t)));
    arr3Addr = (uint32_t)arr3;

    if (arr3[arr1Addr + (10 * sizeof(uint8_t)) + sizeof(heapData)] != 'd') {
        uart0_putString ("Test failed!\n\r");

        uart0_putString ("arr1[0] address: ");
        uart0_putString (intToString (arr1Addr, str, STR_LEN));
        uart0_putString ("\n\r");

        uart0_putString ("arr2[0] address: ");
        uart0_putString (intToString (arr2Addr, str, STR_LEN));
        uart0_putString ("\n\r");

        uart0_putString ("arr3[0] address: ");
        uart0_putString (intToString (arr3Addr, str, STR_LEN));
        uart0_putString ("\n\r");

        uart0_putString ("Expected value in arr3 at arr2 start index: d");
        uart0_putString ("\n\r");

        uart0_putString ("Actual value in arr3 at arr2 start index: ");
        uart0_putChar (arr3[arr2Addr + (10 * sizeof(uint8_t)) + sizeof(heapData)]);
        uart0_putString ("\n\r");

        heap_free (arr3);
        arr3 = NULL;

        return;
    }

    heap_free (arr3);
    arr3 = NULL;

    uart0_putString ("Test passed!\n\r");
}
