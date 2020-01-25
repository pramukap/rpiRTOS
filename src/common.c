/*
 * Author:          Pramuka Perera
 * Last Updated:    5 August 2019
 * Description:     Commonly used code
 */

#include "common.h"

char bitToChar (uint32_t bit) {
    return (char)(bit + '0');
}

// modify function to return 
// start index of new string if successful
// and -1 if unsuccessful
char *intToString (uintptr_t num, char *buff, int32_t size) {
    int i;
   
    i = size - 1;
    buff[i] = '\0';
    i--;

    // convert int to string starting with least place digit
    while (num != 0 && i > -1) {
        buff[i] = (num % 10) + '0';        
        num /= 10;
        i--;
    }

    if (num != 0) {
        return NULL;
    }

    i++;
    return &buff[i];
}
