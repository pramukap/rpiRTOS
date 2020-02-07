/*
 * Author:          Pramuka Perera
 * Last Updated:    5 August 2019
 * Description:     Commonly used code
 */

#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdint.h>

#define SUCCESS 0
#define FAILURE 1

#define DISABLE 0
#define ENABLE	1

#define OFF 	0
#define ON		1

#define CLR		0
#define SET		1

uint32_t power (uint32_t base, uint32_t exp); 

char bitToChar (uint32_t bit);

// base 10 only
char *intToString (uintptr_t num, char *buff, int32_t size);

// base 10 only
// make sure the number fits in a u32
uint32_t stringToInt (char *str); 
#endif 

