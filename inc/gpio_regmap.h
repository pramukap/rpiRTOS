#ifndef GPIO_REGMAP_H
#define GPIO_REGMAP_H

#include <stdint.h>

#define GPIO_BASE 		0x20200000UL
#define GPIO_FSEL0		(*(volatile uint32_t*) 	(GPIO_BASE + 0x00))
#define GPIO_FSEL1		(*(volatile uint32_t*) 	(GPIO_BASE + 0x04)) 
#define GPIO_FSEL2		(*(volatile uint32_t*) 	(GPIO_BASE + 0x08))
#define GPIO_FSEL3 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x0c))
#define GPIO_FSEL4 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x10))
#define GPIO_FSEL5 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x14))
#define GPIO_SET0		(*(volatile uint32_t*) 	(GPIO_BASE + 0x1c))
#define GPIO_SET1 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x20))
#define GPIO_CLR0 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x28))
#define GPIO_CLR1 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x2c))
#define GPIO_LEV0		(*(volatile uint32_t*) 	(GPIO_BASE + 0x34))
#define GPIO_LEV1		(*(volatile uint32_t*) 	(GPIO_BASE + 0x38))
#define GPIO_EDS0 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x40))
#define GPIO_EDS1		(*(volatile uint32_t*) 	(GPIO_BASE + 0x44))
#define GPIO_REN0 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x4c))
#define GPIO_REN1 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x50))
#define GPIO_FEN0 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x58))
#define GPIO_FEN1 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x5c))
#define GPIO_HEN0 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x64))
#define GPIO_HEN1		(*(volatile uint32_t*) 	(GPIO_BASE + 0x68))
#define GPIO_LEN0 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x70))
#define GPIO_LEN1 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x74))
#define GPIO_AREN0 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x7c))
#define GPIO_AREN1		(*(volatile uint32_t*) 	(GPIO_BASE + 0x80))
#define GPIO_AFEN0 		(*(volatile uint32_t*) 	(GPIO_BASE + 0x88))
#define GPIO_AFEN1		(*(volatile uint32_t*) 	(GPIO_BASE + 0x8c))
#define GPIO_PUD		(*(volatile uint32_t*) 	(GPIO_BASE + 0x94))
#define GPIO_PUDCLK0	(*(volatile uint32_t*) 	(GPIO_BASE + 0x98)) 
#define GPIO_PUDCLK1	(*(volatile uint32_t*) 	(GPIO_BASE + 0x9c))

#endif

