#ifndef UART0_REGMAP_H
#define UART0_REGMAP_H

#include <stdint.h>

#define UART0_BASE 		0x20201000
#define UART0_DR		(* (volatile uint32_t *)	(UART0_BASE + 0x00))
#define UART0_RSRECR	(* (volatile uint32_t *)	(UART0_BASE + 0x04))
#define UART0_FR		(* (volatile uint32_t *)	(UART0_BASE + 0x18))
#define UART0_IBRD		(* (volatile uint32_t *)	(UART0_BASE + 0x24))
#define UART0_FBRD		(* (volatile uint32_t *)	(UART0_BASE + 0x28))
#define UART0_LCRH		(* (volatile uint32_t *)	(UART0_BASE + 0x2c))
#define UART0_CR		(* (volatile uint32_t *)	(UART0_BASE + 0x30))
#define UART0_IFLS		(* (volatile uint32_t *)	(UART0_BASE + 0x34))
#define UART0_IMSC		(* (volatile uint32_t *)	(UART0_BASE + 0x38))
#define UART0_RIS		(* (volatile uint32_t *)	(UART0_BASE + 0x3c))
#define UART0_MIS		(* (volatile uint32_t *)	(UART0_BASE + 0x30))
#define UART0_ICR		(* (volatile uint32_t *)	(UART0_BASE + 0x44))
#define UART0_ITCR		(* (volatile uint32_t *)	(UART0_BASE + 0x80))
#define UART0_ITIP		(* (volatile uint32_t *)	(UART0_BASE + 0x84))
#define UART0_ITOP		(* (volatile uint32_t *)	(UART0_BASE + 0x88))
#define UART0_TDR 		(* (volatile uint32_t *)	(UART0_BASE + 0x8c))

#endif
