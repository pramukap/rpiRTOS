/*
 * Author:          Pramuka Perera
 * Last Updated:    09 December 2019
 * Description:     Functions to validate heap
 */

#include "common.h"
#include "heap.h"
#include "uart0.h"

// Allocate specific tests
void heapTest_dataAlignment (void); 

void heapTest_allocFail (void);

void heapTest_recycleMemory (void); 

void heapTest_twoArrays (void); 

void heapTest_freeBlockTooSmall (void); 

void heapTest_freeBlockGoldilocks (void); 

// Free specific tests
void heapTest_currAbsorbsNext (void); 

void heapTest_currAbsorbedByPrev (void); 
