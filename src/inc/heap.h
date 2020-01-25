/*
 * Author:          Pramuka Perera
 * Last Updated:    31 October 2019
 * Description:     Manage dynamic memory allocation
 */

#ifndef _HEAP_
#define _HEAP_

#include "common.h"
#include "uart0.h"

#define HEAP_SIZE 10000

#define FREE 0
#define ALLOCATED 1

#define DATA_ALIGN_SIZE 4

typedef struct heapMetaData heapData;

struct heapMetaData {
    uint32_t size;  // size of block, excluding space for metadata
    uint8_t state;
    heapData *prev;
    heapData *next;
};

void heap_init (void);

void *heap_allocate (uint32_t size);

void heap_free (void *ptr);

#endif
