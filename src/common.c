/*
 * Author:          Pramuka Perera
 * Last Updated:    5 August 2019
 * Description:     Commonly used code
 */

#include "common.h"

uint32_t power (uint32_t base, uint32_t exp) {
    uint32_t result = 1; 
    
    for (uint32_t i = 0; i < exp; i++) {
        result *= base;
    }

    return result;
}

char bitToChar (uint32_t bit) {
    return (char)(bit + '0');
}

// base 10 only
char *intToString (uintptr_t num, char *buff, int32_t size) {
    int i;
   
    i = size - 1;
    buff[i] = '\0';
    i--;

    if (num == 0) {
        buff[i] = '0';
        return &buff[i];
    }

    // convert int to string starting with the one's place digit
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

// base 10 only
// make sure the number fits in a u32
uint32_t stringToInt (char *str) {
    uint32_t result = 0;

    // number of digits in the string number
    int i = 0;
    while (str[i] != '\0') { 
        i++; 
    }
    
    // cancel the increment for going from last character to null terminator
    i--;

    // convert string to int, starting with the largest place digit
    int j = 0;
    while (i >= 0) {
        result += (str[j] - '0') * power (10, i);
        j++;
        i--;
    }

    return result;
}
