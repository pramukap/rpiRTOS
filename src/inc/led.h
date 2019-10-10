/*
 * Author:          Pramuka Perera
 * Last Updated:    5 August 2019
 * Description:     
 */

#ifndef LED_H
#define LED_H

#include "gpio.h"

#define LED_BIT 15

void led_init (void);

void led_toggle (void);

#endif
