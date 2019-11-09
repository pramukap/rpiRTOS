/*
 * Author:          Pramuka Perera
 * Last Updated:    31 October 2019
 * Description:     Manage dynamic memory allocation
 */

#ifndef _HEAP_
#define _HEAP_

#include <stddef.h>
#include <stdint.h>

void heap_init (void);

void *heap_allocate (uint32_t size);

void heap_free (void *ptr);

#endif
