#ifndef __UART0__
#define __UART0__

#include <stdint.h>
#include <stddef.h>

// bit field for register
// first item in bit field list corresponds to least significant bits
// so data corresponds to the lowest 8 bits

// Data Register
struct U0_DR_bits {
	unsigned data: 8, 
			 fe: 1, 
			 pe: 1, 
			 be: 1, 
			 oe: 1, 
			 res: 20; //, oe: 1, be: 1, pe: 1, fe: 1, data: 8;	
};

// union that allows access of individual bits in register or entire register 
union U0_DR_reg {
	uint32_t reg;
	struct U0_DR_bits fields;
};


// Receive Status Register/Error Clear Register
struct U0_RSRECR_bits {
	unsigned fe: 1,
			 pe: 1,
			 be: 1,
			 oe: 1,
			 res: 28;
};

union U0_RSRECR_reg {
	uint32_t reg;
	struct U0_RSRECR_bits field;	
};	

// Flag Register
struct U0_FR_bits {
	unsigned cts: 1,
			 dsr: 1,
			 dcd: 1,
			 busy: 1,
			 rxfe: 1,
			 txff: 1,
			 rxff: 1,
			 txfe: 1,
			 ri: 1,
			 res: 23;
};

union U0_FR_reg {
	uint32_t reg;
	struct U0_FR_bits field;	
};	

// Integer Baud Rate Divisor Register
struct U0_IBRD_bits {
	unsigned ibrd: 16,
			 res: 16;
};

union U0_IBRD_reg {
	uint32_t reg;
	struct U0_IBRD_bits field;	
};	

// Fractional Baud Rate Divisor Register
struct U0_FBRD_bits {
	unsigned fbrd: 6,
			 res: 26;
};

union U0_FBRD_reg {
	uint32_t reg;
	struct U0_FBRD_bits field;	
};	

// Line Control Register
struct U0_LCRH_bits {
	unsigned brk: 1,
			 pen: 1,
			 eps: 1,
			 stp2: 1,
			 fen: 1,
			 wlen: 2,
			 sps: 1,
			 res: 24;
};

union U0_LCRH_reg {
	uint32_t reg;
	struct U0_LCRH_bits field;	
};	

// Control Register
struct U0_CR_bits {
	unsigned uarten: 1,
			 siren: 1,
			 sirlp: 1,
			 res0: 4,
			 lbe: 1,
			 txe: 1,
			 rxe: 1,
			 dtr: 1,
			 rts: 1,
			 out1: 1,
			 out2: 1,
			 rtsen: 1,
			 ctsen: 1,
			 res1: 16;
};

union U0_CR_reg {
	uint32_t reg;
	struct U0_CR_bits field;	
};	

// Interrupt FIFO Level Select Register
struct U0_IFLS_bits {
	unsigned txiflsel: 3,
			 rxiflsel: 3,
			 txifpsel: 3,
			 rxifpsel: 3,
			 res: 20;
};

union U0_IFLS_reg {
	uint32_t reg;
	struct U0_IFLS_bits field;	
};	

// Interrupt Mask Set/Clear Register
struct U0_IMSC_bits {
	unsigned rimim: 1,
			 ctsmim: 1,
			 dcdmim: 1,
			 dsrmim: 1,
			 rxim: 1,
			 txim: 1,
			 rtim: 1,
			 feim: 1,
			 peim: 1,
			 beim: 1,
			 oeim: 1,
			 res: 21;
};

union U0_IMSC_reg {
	uint32_t reg;
	struct U0_IMSC_bits field;	
};	

// Raw Interrupt Status Register
struct U0_RIS_bits {
	unsigned rirmis: 1,
			 ctsrmis: 1,
			 dcdrmis: 1,
			 dsrrmis: 1,
			 rxris: 1,
			 txris: 1,
			 rtris: 1,
			 feris: 1,
			 peris: 1,
			 beris: 1,
			 oeris: 1,
			 res: 21;
};

union U0_RIS_reg {
	uint32_t reg;
	struct U0_RIS_bits field;	
};	

// Masked Interrupt Status Register
struct U0_MIS_bits {
	unsigned rimmis: 1,
			 ctsmmis: 1,
			 dcdmmis: 1,
			 dsrmmis: 1,
			 rxmis: 1,
			 txmis: 1,
			 rtmis: 1,
			 femis: 1,
			 pemis: 1,
			 bemis: 1,
			 oemis: 1,
			 res: 21;
};

union U0_MIS_reg {
	uint32_t reg;
	struct U0_MIS_bits field;	
};	

// Interrupt Clear Register
struct U0_ICR_bits {
	unsigned rimic: 1,
			 ctsmic: 1,
			 dcdmic: 1,
			 dsrmic: 1,
			 rxic: 1,
			 txic: 1,
			 rtic: 1,
			 feic: 1,
			 peic: 1,
			 beic: 1,
			 oeic: 1,
			 res: 21;
};

union U0_ICR_reg {
	uint32_t reg;
	struct U0_ICR_bits field;	
};	

// Test Control Register
struct U0_ITCR_bits {
	unsigned itcr0: 1,
			 itcr1: 1,
			 res: 30;
};

union U0_ITCR_reg {
	uint32_t reg;
	struct U0_ITCR_bits field;	
};	

// Test Control Register
struct U0_ITIP_bits {
	unsigned itip0: 1,
			 res0: 2,
			 itip3: 1,
			 res1: 28;
};

union U0_ITIP_reg {
	uint32_t reg;
	struct U0_ITIP_bits field;	
};	

// Test Control Register
struct U0_ITOP_bits {
	unsigned itip0: 1,
			 res0: 2,
			 itip3: 1,
			 res1: 2,
			 itop6: 1,
			 itop7: 1,
			 itop8: 1,
			 itop9: 1,
			 itop10: 1,
			 itop11: 1,
			 res: 20;
};

union U0_ITOP_reg {
	uint32_t reg;
	struct U0_ITOP_bits field;	
};	

// Test Data Register
struct U0_TDR_bits {
	unsigned TDR10_0: 11,
			 res: 21;
};

union U0_TDR_reg {
	uint32_t reg;
	struct U0_TDR_bits field;	
};	

#define UART0_BASE 		0x7e20100
#define UART0_DR		(* (volatile union U0_DR_reg *)		UART0_BASE + 0x00)
#define UART0_RSRECR	(* (volatile union U0_RSRECR_reg *)	UART0_BASE + 0x04)
#define UART0_FR		(* (volatile union U0_FR_reg *)		UART0_BASE + 0x18)
#define UART0_IBRD		(* (volatile union U0_IBRD_reg *)	UART0_BASE + 0x24)
#define UART0_FBRD		(* (volatile union U0_FBRD_reg *)	UART0_BASE + 0x28)
#define UART0_LCRH		(* (volatile union U0_LCRH_reg *)	UART0_BASE + 0x2c)
#define UART0_CR		(* (volatile union U0_CR_reg *)		UART0_BASE + 0x30)
#define UART0_IFLS		(* (volatile union U0_IFLS_reg *)	UART0_BASE + 0x34)
#define UART0_IMSC		(* (volatile union U0_IMSC_reg *)	UART0_BASE + 0x38)
#define UART0_RIS		(* (volatile union U0_RIS_reg *)	UART0_BASE + 0x3c)
#define UART0_MIS		(* (volatile union U0_MIS_reg *)	UART0_BASE + 0x30)
#define UART0_ICR		(* (volatile union U0_ICR_reg *)	UART0_BASE + 0x44)
#define UART0_ITCR		(* (volatile union U0_ITCR_reg *)	UART0_BASE + 0x80)
#define UART0_ITIP		(* (volatile union U0_ITIP_reg *)	UART0_BASE + 0x84)
#define UART0_ITOP		(* (volatile union U0_ITOP_reg *)	UART0_BASE + 0x88)
#define UART0_TDR 		(* (volatile union U0_TDR_reg *)	UART0_BASE + 0x8c)

#endif
