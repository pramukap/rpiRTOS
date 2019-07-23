#ifndef GPIO_H
#define GPIO_H

#include "common.h"
#include "gpio_regmap.h"

// pull-up/down enable/disable
#define PUD_DISABLE	0
#define PUD_ENPD	1
#define PUD_ENPU	2

// use with GPIO_FSELx
// configure pin as input or output
#define FSEL_INPUT 	0
#define FSEL_OUTPUT	1

// configure pin's alternate function
#define FSEL_ALT0 	4
#define FSEL_ALT1 	5
#define FSEL_ALT2 	6
#define FSEL_ALT3 	7
#define FSEL_ALT4 	3
#define FSEL_ALT5 	2 

#define FSEL_FIELD9	27
#define FSEL_FIELD8	24
#define FSEL_FIELD7	21
#define FSEL_FIELD6	18
#define FSEL_FIELD5	15
#define FSEL_FIELD4	12
#define FSEL_FIELD3	9
#define FSEL_FIELD2	6
#define FSEL_FIELD1	3
#define FSEL_FIELD0	0
#endif

