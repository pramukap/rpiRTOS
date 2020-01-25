/*
 * Author:          Pramuka Perera
 * Last Updated:    31 October 2019
 * Description:     Manage dynamic memory allocation
 */

#include "heap.h"

#define STR_SIZE 100
#define STR_LEN 50

uint8_t heap[HEAP_SIZE] = {0};
char str[STR_SIZE];

void heap_init (void) {
    heapData *initBlock = (heapData *)heap;

    uart0_putString ("Initializing Heap\n\r");
    
    initBlock->size = HEAP_SIZE - sizeof(heapData);
    initBlock->state = FREE;
    initBlock->next = NULL;
    initBlock->prev = NULL;
    
    uart0_putString ("Heap Start Address: ");
    uart0_putString (intToString ((uint32_t)heap, str, STR_LEN));
    uart0_putString ("\n\r");

    uart0_putString ("Heap Size: ");
    uart0_putString (intToString (HEAP_SIZE, str, STR_LEN));
    uart0_putString ("\n\r");
}

// first fit policy
void *heap_allocate (uint32_t size) {
    heapData *currBlock = (heapData *)heap; 
    heapData *nextBlock = NULL;

    uint32_t newBlockSize = size + sizeof(heapData) + (DATA_ALIGN_SIZE - ((size + sizeof(heapData)) % DATA_ALIGN_SIZE)); // desired space, space for metadata, padding
   
    // if block does not exist, then you've hit the end of the heap
    while (currBlock != NULL) {
        uart0_putString ("Heap CurrBlock Address: ");
        uart0_putString (intToString ((uint32_t)currBlock, str, STR_LEN));
        uart0_putString ("\n\r");
        
        if (currBlock->state == FREE) {
            // if the block is too small, 
            // go to the next block
            if (currBlock->size < size) {
                currBlock = currBlock->next; 
            }
            // if the block can provide the required space 
            // but there isn't enough space remaining for a new block,
            // allocate the entire block and return its pointer.
            // data alignment padding is not a worry here because
            // we're not allocating a new block
            else if (currBlock->size > size && currBlock->size <= newBlockSize) {
                currBlock->state = ALLOCATED;

//                uart0_putString ("Allocated Mem Start Address: ");
//                uart0_putString (intToString ((uint32_t)currBlock, str, STR_LEN));
//                uart0_putString ("/ heap_allocate Return Address: ");
//                uart0_putString (intToString ((uint32_t)((uint8_t *)currBlock + sizeof(heapData)), str, STR_LEN));
//                uart0_putString ("/ heapData size: ");
//                uart0_putString (intToString ((uint32_t)(sizeof(heapData)), str, STR_LEN));
//                uart0_putString ("\n\r");
                
                return (void *)(((uint8_t *)currBlock) + sizeof(heapData)); // currBlock must be cast as uint8_t ptr because of pointer arithmetic
            }
            // if the block has more than enough memory,
            // allocate the necessary memory and return its pointer
            // create a new block for the extra memory.
            // this is where padding matters since we're creating new blocks
            else if (currBlock->size > newBlockSize) {
                nextBlock = (heapData *)((uint8_t *)currBlock + newBlockSize);

                nextBlock->size = currBlock->size - newBlockSize; // what remains after allocating space for allocated block and this block's metadata
                nextBlock->state = FREE;
                nextBlock->next = currBlock->next;
                nextBlock->prev = currBlock;

                currBlock->size = newBlockSize - sizeof(heapData); // desired size + padding
                currBlock->state = ALLOCATED;
                currBlock->next = nextBlock;

                uart0_putString ("currBlock->next address: ");
                uart0_putString (intToString ((uint32_t)(currBlock->next), str, STR_LEN));
                uart0_putString ("| currBlock->prev address: ");
                uart0_putString (intToString ((uint32_t)(currBlock->prev), str, STR_LEN));
                uart0_putString ("| nextBlock->next address: ");
                uart0_putString (intToString ((uint32_t)(nextBlock->next), str, STR_LEN));
                uart0_putString ("| nextBlock->prev address: ");
                uart0_putString (intToString ((uint32_t)(nextBlock->prev), str, STR_LEN));
                uart0_putString ("\n\r");

                uart0_putString ("Allocated Mem Start Address: ");
                uart0_putString (intToString ((uint32_t)currBlock, str, STR_LEN));
                uart0_putString ("/ heap_allocate Return Address: ");
                uart0_putString (intToString ((uint32_t)((uint8_t *)currBlock + sizeof(heapData)), str, STR_LEN));
                uart0_putString ("/ heapData size: ");
                uart0_putString (intToString ((uint32_t)(sizeof(heapData)), str, STR_LEN));
                uart0_putString ("\n\r");
                
                return (void *)(((uint8_t *)currBlock) + sizeof(heapData)); // currBlock must be cast as uint8_t ptr because of pointer arithmetic
            }
        }
        else {
            currBlock = currBlock->next;
        }
    } 

    return NULL;
}

void heap_free (void *ptr) { 
    heapData *currBlock = (heapData *)(ptr - sizeof(heapData));
    heapData *nextBlock = currBlock->next;
    heapData *prevBlock = currBlock->prev;

    currBlock->state = FREE;
    
    // curr block absorbs next block if next block is also free
    if (nextBlock != NULL && nextBlock->state == FREE) {
        uart0_putString ("Current block absorbing next block\n\r");
        uart0_putString ("Address of next block: ");
        uart0_putString (intToString ((uint32_t)nextBlock, str, STR_LEN));
        uart0_putString ("\n\r");
        currBlock->size = currBlock->size + sizeof(heapData) + nextBlock->size;
        currBlock->next = nextBlock->next;
    }

    // prev block absorbs curr block if prev block is also free
    if (prevBlock != NULL && prevBlock->state == FREE) {  
        uart0_putString ("Previous block absorbing current block\n\r");
        uart0_putString ("Address of previous block: ");
        uart0_putString (intToString ((uint32_t)prevBlock, str, STR_LEN));
        uart0_putString ("\n\r");
        prevBlock->size = prevBlock->size + sizeof(heapData) + currBlock->size;
        prevBlock->next = currBlock->next;
    }

    return;
}

