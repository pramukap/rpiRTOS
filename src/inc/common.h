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

char bitToChar (uint32_t bit);

char *intToString (uintptr_t num, char *buff, int32_t size);
#endif 

