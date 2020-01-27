/*
 * Author:          Pramuka Perera
 * Last Updated:    9 December 2019
 * Description:     Functions to validate heap
 */

#include "heapTest.h"

#define STR_SIZE 100
#define STR_LEN 50 

char str[STR_SIZE];


// Tests fail allocate memory
void heapTest_allocFail (void) {
    uint8_t *arr1 = NULL;

    uart0_putString ("Running \"Allocation Failed\" Test:\n\r");

    arr1 = (uint8_t *)(heap_allocate ((HEAP_SIZE + 1) * sizeof(uint8_t)));

    if (arr1 != NULL) {
        uart0_putString ("Test failed!\n\r");

        uart0_putString ("arr1 should point null\n\r");
        uart0_putString ("arr1 address: ");
        uart0_putString (intToString ((uintptr_t)arr1, str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("\n\r");

        heap_free (arr1);
        arr1 = NULL;

        return;
    }

    uart0_putString ("Test passed!\n\r");
    uart0_putString ("\n\r");
}

// Tests allocate and padding
void heapTest_dataAlignment (void) {
    uint8_t *arr1, *arr2, *arr3, *arr4, *arr5 = NULL;
    uint8_t testFailed = 0;

    uart0_putString ("Running \"Data Alignment\" Test:\n\r");

    // adds 3 bytes of padding
    arr1 = (uint8_t *)(heap_allocate (1 * sizeof(uint8_t)));
    // adds 2 bytes of padding
    arr2 = (uint8_t *)(heap_allocate (2 * sizeof(uint8_t)));
    // adds 1 bytes of padding
    arr3 = (uint8_t *)(heap_allocate (3 * sizeof(uint8_t)));
    // adds 4 bytes of padding
    arr4 = (uint8_t *)(heap_allocate (4 * sizeof(uint8_t)));
    arr5 = (uint8_t *)(heap_allocate (4 * sizeof(uint8_t)));

    if (arr2 != arr1 + (4 * sizeof(uint8_t)) + sizeof(heapData)) {
        uart0_putString ("Test failed!\n\r");
        uart0_putString ("Arr1 didn't get expected padding: ");
        uart0_putString ("\n\r");
        uart0_putString ("Arr1 Address: ");
        uart0_putString (intToString ((uintptr_t)arr1, str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("Arr2 Address: ");
        uart0_putString (intToString ((uintptr_t)arr2, str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("Expected Arr1 size was 4\n\r");
        uart0_putString ("Actual Arr1 size was ");
        uart0_putString (intToString ((uintptr_t)arr2 - (uintptr_t)arr1 - sizeof(heapData), str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("\n\r");

        testFailed = 1;
    }

    if (arr3 != arr2 + (4 * sizeof(uint8_t)) + sizeof(heapData)) {
        uart0_putString ("Test failed!\n\r");

        uart0_putString ("Arr2 didn't get expected padding: \n\r");
        uart0_putString ("Arr2 Address: ");
        uart0_putString (intToString ((uintptr_t)arr2, str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("Arr3 Address: ");
        uart0_putString (intToString ((uintptr_t)arr3, str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("Expected Arr2 size was 4\n\r");
        uart0_putString ("Actual Arr2 size was ");
        uart0_putString (intToString ((uintptr_t)arr3 - (uintptr_t)arr2 - sizeof(heapData), str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("\n\r");

        testFailed = 1;
    }

    if (arr4 != arr3 + (4 * sizeof(uint8_t)) + sizeof(heapData)) {
        uart0_putString ("Test failed!\n\r");

        uart0_putString ("Arr3 didn't get expected padding: \n\r");
        uart0_putString ("Arr3 Address: ");
        uart0_putString (intToString ((uintptr_t)arr3, str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("Arr4 Address: ");
        uart0_putString (intToString ((uintptr_t)arr4, str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("Expected Arr3 size was 4\n\r");
        uart0_putString ("Actual Arr3 size was ");
        uart0_putString (intToString ((uintptr_t)arr4 - (uintptr_t)arr3 - sizeof(heapData), str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("\n\r");

        testFailed = 1;
    }

    if (arr5 != arr4 + (8 * sizeof(uint8_t)) + sizeof(heapData)) {
        uart0_putString ("Test failed!\n\r");

        uart0_putString ("Arr4 didn't get expected padding: \n\r");
        uart0_putString ("Arr4 Address: ");
        uart0_putString (intToString ((uintptr_t)arr4, str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("Arr5 Address: ");
        uart0_putString (intToString ((uintptr_t)arr5, str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("Expected Arr4 size was 8\n\r");
        uart0_putString ("Actual Arr4 size was ");
        uart0_putString (intToString ((uintptr_t)arr5 - (uintptr_t)arr4 - sizeof(heapData), str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("\n\r");

        testFailed = 1;
    }

    heap_free (arr1);
    heap_free (arr2);
    heap_free (arr3);
    heap_free (arr4);
    heap_free (arr5);

    arr1 = NULL;
    arr2 = NULL;
    arr3 = NULL;
    arr4 = NULL;
    arr5 = NULL;

    if (testFailed == 0) {
        uart0_putString ("Test passed!\n\r");
        uart0_putString ("\n\r");
    }
}

// Allocate a 10 byte array, and write to the first byte
// Free the array
// Create a new 10 byte array, and read the first byte
// The read value should be equal to the write value
// Tests allocate and free
void heapTest_recycleMemory (void) {
    uint8_t *arr1, *arr2 = NULL;
    uint32_t arr1Addr, arr2Addr;
    uint8_t arr1Val;

    uart0_putString ("Running \"Recycle Memory\" Test:\n\r");

    arr1 = (uint8_t *)(heap_allocate (10 * sizeof(uint8_t)));
    arr1Addr = (uint32_t)arr1;
    arr1[0] = arr1Val = 5;

    heap_free (arr1);
    arr1 = NULL;

    arr2 = (uint8_t *)(heap_allocate (10 * sizeof(uint8_t)));
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
        uart0_putString ("\n\r");

        heap_free (arr2);
        arr2 = NULL;

        return;
    }
        
    heap_free (arr2);
    arr2 = NULL;

    uart0_putString ("Test passed!\n\r");
    uart0_putString ("\n\r");
}


// Allocate two arrays 
// Tests allocate and create new block
void heapTest_twoArrays (void) {
    uint8_t *arr1, *arr2 = NULL;
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

    if (arr2Addr != (arr1Addr + (12 * sizeof (uint8_t)) + sizeof(heapData))) {
        uart0_putString ("Test failed!\n\r");

        uart0_putString ("arr1[0] address: ");
        uart0_putString (intToString (arr1Addr, str, STR_LEN));
        uart0_putString ("\n\r");

        uart0_putString ("Expected arr2[0] address: ");
        uart0_putString (intToString (arr1Addr + (12 * sizeof (uint8_t)) + sizeof(heapData), str, STR_LEN));
        uart0_putString ("\n\r");

        uart0_putString ("Actual arr2[0] address: ");
        uart0_putString (intToString (arr2Addr, str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("\n\r");

        return;
    }

    uart0_putString ("Test passed!\n\r");
    uart0_putString ("\n\r");
}

// Allocates three 10-byte arrays 
// Frees middle array
// Attempts to allocate 11-byte array 
// 11 byte array should be allocated after the third array
// and not in the block the second array used to occupy
// Tests allocate, block size measuring, create new block, and free
void heapTest_freeBlockTooSmall (void) {
    uint8_t *arr1, *arr2, *arr3, *arr4 = NULL;
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

    arr4 = (uint8_t *)(heap_allocate (13 * sizeof(uint8_t)));
    arr4Addr = (uint32_t)arr4;

    heap_free (arr1);
    arr1 = NULL;
    heap_free (arr2);
    arr2 = NULL;
    heap_free (arr3);
    arr3 = NULL;
    heap_free (arr4);
    arr4 = NULL;

    if (arr4Addr != arr3Addr + (12 * sizeof(uint8_t)) + sizeof(heapData)) {
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
        uart0_putString (intToString (arr3Addr + (12 * sizeof(uint8_t)) + sizeof(heapData), str, STR_LEN));
        uart0_putString ("\n\r");

        uart0_putString ("Actual arr4[0] address: ");
        uart0_putString (intToString (arr4Addr, str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("\n\r");

        return;
    }

    uart0_putString ("Test passed!\n\r");
    uart0_putString ("\n\r");
}

// Allocates three 10-byte arrays 
// Frees middle array
// Attempts to allocate 8-byte array 
// 11 byte array should be allocated after the third array
// and not in the block the second array used to occupy
// Tests allocate, block size measuring, create new block, and free
void heapTest_freeBlockGoldilocks (void) {
    uint8_t *arr1, *arr2, *arr3, *arr4 = NULL;
    uint32_t arr1Addr, arr2Addr, arr3Addr, arr4Addr;

    uart0_putString ("Running \"Free Block Goldilocks\" Test:\n\r");

    arr1 = (uint8_t *)(heap_allocate (10 * sizeof(uint8_t)));
    arr1Addr = (uint32_t)arr1;

    arr2 = (uint8_t *)(heap_allocate (10 * sizeof(uint8_t)));
    arr2Addr = (uint32_t)arr2;

    arr3 = (uint8_t *)(heap_allocate (10 * sizeof(uint8_t)));
    arr3Addr = (uint32_t)arr3;

    heap_free (arr2);
    arr2 = NULL;

    arr4 = (uint8_t *)(heap_allocate (8 * sizeof(uint8_t)));
    arr4Addr = (uint32_t)arr4;

    heap_free (arr1);
    arr1 = NULL;
    heap_free (arr2);
    arr2 = NULL;
    heap_free (arr3);
    arr3 = NULL;
    heap_free (arr4);
    arr4 = NULL;

    if (arr4Addr != arr1Addr + (12 * sizeof (uint8_t)) + sizeof(heapData)) {
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
        uart0_putString (intToString (arr1Addr + (12 * sizeof (uint8_t)) + sizeof(heapData), str, STR_LEN));
        uart0_putString ("\n\r");

        uart0_putString ("Actual arr4[0] address: ");
        uart0_putString (intToString (arr4Addr, str, STR_LEN));
        uart0_putString ("\n\r");
        uart0_putString ("\n\r");

        return;
    }

    uart0_putString ("Test passed!\n\r");
    uart0_putString ("\n\r");
}

// Tests allocate, free, and absorbs next neighbor
void heapTest_currAbsorbsNext (void) {
    uint8_t *arr1, *arr2, *arr3 = NULL;
    uint32_t arr1Addr, arr2Addr, arr3Addr;

    uart0_putString ("Running \"Current Absorbs Next\" Test:\n\r");

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

    if (arr3[(12 * sizeof(uint8_t)) + sizeof(heapData)] != 'd') {
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
        uart0_putChar (arr3[arr2Addr + (12 * sizeof(uint8_t)) + sizeof(heapData)]);
        uart0_putString ("\n\r");
        uart0_putString ("\n\r");

        heap_free (arr3);
        arr3 = NULL;

        return;
    }

    heap_free (arr3);
    arr3 = NULL;

    uart0_putString ("Test passed!\n\r");
    uart0_putString ("\n\r");
}

// Tests allocate, free, absorbs next neighbor, and absorbed by previous neighbor
void heapTest_currAbsorbedByPrev (void) {
    uint8_t *arr1, *arr2, *arr3 = NULL;
    uint32_t arr1Addr, arr2Addr, arr3Addr;

    uart0_putString ("Running \"Current Absorbed by Previous\" Test:\n\r");

    arr1 = (uint8_t *)(heap_allocate (10 * sizeof(uint8_t)));
    arr1Addr = (uint32_t)arr1;

    arr2 = (uint8_t *)(heap_allocate (10 * sizeof(uint8_t)));
    arr2Addr = (uint32_t)arr2;

    arr2[0] = 'd';

    heap_free (arr1);
    arr1 = NULL;

    // arr1 block absorbs arr2 once it's freed
    heap_free (arr2);
    arr2 = NULL;

    // arr3 should be made of arr1 and half of arr2
    arr3 = (uint8_t *)(heap_allocate ((10 + sizeof(heapData) + 5) * sizeof(uint8_t)));
    arr3Addr = (uint32_t)arr3;

    if (arr3[(12 * sizeof(uint8_t)) + sizeof(heapData)] != 'd') {
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
        uart0_putChar (arr3[arr2Addr + (12 * sizeof(uint8_t)) + sizeof(heapData)]);
        uart0_putString ("\n\r");
        uart0_putString ("\n\r");

        heap_free (arr3);
        arr3 = NULL;

        return;
    }

    heap_free (arr3);
    arr3 = NULL;

    uart0_putString ("Test passed!\n\r");
    uart0_putString ("\n\r");
}
