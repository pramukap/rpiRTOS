#ifndef __UART0__
#define __UART0__

#include <stdint.h>
#include "uart0_regmap.h"

#define WLEN_8 3
#define WLEN_7 2
#define WLEN_6 1
#define WLEN_5 0

void uart0_init (void);

void uart0_putChar (char c);

char uart0_getChar (void);

void uart0_putString (char *str);

void uart0_getString (char *str, uint32_t maxLength);

#endif

