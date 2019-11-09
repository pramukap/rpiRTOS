/*
 * Author:          Pramuka Perera
 * Last Updated:    31 October 2019
 * Description:     Manage dynamic memory allocation
*/

#include "heap.h"
#include "uart0.h"

#define HEAP_SIZE 10000

#define FREE 0
#define ALLOCATED 1

typedef struct heapMetaData heapData;

struct heapMetaData {
    uint32_t size;
    uint8_t state;
    heapData *prev;
    heapData *next;
};

uint8_t heap[HEAP_SIZE] = {0};

void heap_init (void) {
    heapData *initBlock = (heapData *)heap;

    initBlock->size = HEAP_SIZE - sizeof(heapData);
    initBlock->state = FREE;
    initBlock->next = NULL;
    initBlock->prev = NULL;
}

// first available block policy
void *heap_allocate (uint32_t size) {
    heapData *currBlock = (heapData *)heap; 
    heapData *nextBlock;
   
    // if block does not exist, then you've hit the end of the heap
    while (currBlock != NULL) {
        if (currBlock->state == FREE) {
            // if the block is too small, 
            // go to the next block
            if (currBlock->size < size) {
                currBlock = currBlock->next; 
            }
            // if the block is just the right size,
            // allocate the block and return its pointer
            else if (currBlock->size >= size && currBlock->size <= size + sizeof(heapData)) {
                currBlock->state = ALLOCATED;

                return (void *)(currBlock + sizeof(heapData));
            }
            // if the block has more than enough memory,
            // allocate the necessary memory and return its pointer
            // create a new block for the extra memory
            else if (currBlock->size > (size + sizeof(heapData))) {
                nextBlock = (heapData *)(currBlock + sizeof(heapData) + size);

                nextBlock->size = currBlock->size - (size + sizeof(heapData));
                nextBlock->state = FREE;
                nextBlock->next = currBlock->next;
                nextBlock->prev = currBlock;

                currBlock->size = size;
                currBlock->state = ALLOCATED;
                currBlock->next = nextBlock;

                return (void *)(currBlock + sizeof(heapData));
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
        currBlock->size = currBlock->size + sizeof(heapData) + nextBlock->size;
        currBlock->next = nextBlock->next;
    }

    // prev block absorbs curr block if prev block is also free
    if (prevBlock != NULL && prevBlock->state == FREE) {  
        prevBlock->size = prevBlock->size + sizeof(heapData) + currBlock->size;
        prevBlock->next = currBlock->next;
    }

    return;
}

