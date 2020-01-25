/*
 * Author:          Pramuka Perera
 * Last Updated:    23 January 2020
 * Description:     Test UART0 facility
 */

#include "uart0Test.h"

#define STR_SIZE 100
#define STR_LEN 50

char str[STR_SIZE];

void uart0Test_longIntString (void) {
    uart0_putString ("The following number should be 1234567890: ");
    uart0_putString ( intToString ((uintptr_t)1234567890, str, STR_LEN));   
    uart0_putString ("\n\r");
    uart0_putString ("The following number is 123456789012, but will be something else because the processor doesn't support >32 bit: ");
    uart0_putString ( intToString ((uintptr_t)123456789012, str, STR_LEN));   
    uart0_putString ("\n\r");
}
