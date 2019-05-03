#ifndef __GPIO__
#define __GPIO__

#include <stdint.h>
#include <stddef.h>

struct GPIO_FSEL_bits {
		unsigned fsel0: 3,
				 fsel1: 3,
				 fsel2: 3,
				 fsel3: 3,
				 fsel4: 3,
				 fsel5: 3,
				 fsel6: 3,
				 fsel7: 3,
				 fsel8: 3,
				 fsel9: 3,
				 res: 2;
};

union GPIO_FSEL_reg {
		uint32_t reg;
		struct GPIO_FSEL_bits fields;
};

struct GPIO_FSEL5_bits {
		unsigned fsel0: 3,
				 fsel1: 3,
				 fsel2: 3,
				 fsel3: 3,
				 res: 20;
};

union GPIO_FSEL5_reg {
		uint32_t reg;
		struct GPIO_FSEL5_bits fields;
};

#define TYPE0_REG(UC_NAME, LC_NAME) \
struct GPIO_ ## UC_NAME ## _bits {	\
	unsigned 	LC_NAME ## 0: 1,	\
				LC_NAME ## 1: 1,	\
				LC_NAME ## 2: 1,	\
				LC_NAME ## 3: 1,	\
				LC_NAME ## 4: 1,	\
				LC_NAME ## 5: 1,	\
				LC_NAME ## 6: 1,	\
				LC_NAME ## 7: 1,	\
				LC_NAME ## 8: 1,	\
				LC_NAME ## 9: 1,	\
				LC_NAME ## 10: 1,	\
				LC_NAME ## 11: 1,	\
				LC_NAME ## 12: 1,	\
				LC_NAME ## 13: 1,	\
				LC_NAME ## 14: 1,	\
				LC_NAME ## 15: 1,	\
				LC_NAME ## 16: 1,	\
				LC_NAME ## 17: 1,	\
				LC_NAME ## 18: 1,	\
				LC_NAME ## 19: 1,	\
				LC_NAME ## 20: 1,	\
				LC_NAME ## 21: 1,	\
				LC_NAME ## 22: 1,	\
				LC_NAME ## 23: 1,	\
				LC_NAME ## 24: 1,	\
				LC_NAME ## 25: 1,	\
				LC_NAME ## 26: 1,	\
				LC_NAME ## 27: 1,	\
				LC_NAME ## 28: 1,	\
				LC_NAME ## 29: 1,	\
				LC_NAME ## 30: 1,	\
				LC_NAME ## 31: 1;	\
};								\
								\
union GPIO_ ## UC_NAME ## _reg {			\
		uint32_t reg;					\
		struct GPIO_ ## UC_NAME ## _bits fields;	\
};

#define TYPE1_REG(UC_NAME, LC_NAME) \
struct GPIO_ ## UC_NAME ## _bits {	\
	unsigned	LC_NAME ## 32: 1,	\
				LC_NAME ## 33: 1,	\
				LC_NAME ## 34: 1,	\
				LC_NAME ## 35: 1,	\
				LC_NAME ## 36: 1,	\
				LC_NAME ## 37: 1,	\
				LC_NAME ## 38: 1,	\
				LC_NAME ## 39: 1,	\
				LC_NAME ## 40: 1,	\
				LC_NAME ## 41: 1,	\
				LC_NAME ## 42: 1,	\
				LC_NAME ## 43: 1,	\
				LC_NAME ## 44: 1,	\
				LC_NAME ## 45: 1,	\
				LC_NAME ## 46: 1,	\
				LC_NAME ## 47: 1,	\
				LC_NAME ## 48: 1,	\
				LC_NAME ## 49: 1,	\
				LC_NAME ## 50: 1,	\
				LC_NAME ## 51: 1,	\
				LC_NAME ## 52: 1,	\
				LC_NAME ## 53: 1,	\
				res: 10;		\
};								\
								\
union GPIO_ ## UC_NAME ## _reg	{			\
		uint32_t reg;					\
		struct GPIO_ ## UC_NAME ## _bits fields;	\
};

TYPE0_REG(SET0, set)
TYPE1_REG(SET1, set)
		
TYPE0_REG(CLR0, clr)
TYPE1_REG(CLR1, clr)

TYPE0_REG(LEV0, lev)
TYPE1_REG(LEV1, lev)
		
TYPE0_REG(EDS0, eds)
TYPE1_REG(EDS1, eds)
		
TYPE0_REG(REN0, ren)
TYPE1_REG(REN1, ren)
		
TYPE0_REG(FEN0, fen)
TYPE1_REG(FEN1, fen)
		
TYPE0_REG(HEN0, hen)
TYPE1_REG(HEN1, hen)
		
TYPE0_REG(LEN0, len)
TYPE1_REG(LEN1, len)
		
TYPE0_REG(AREN0, aren)
TYPE1_REG(AREN1, aren)

TYPE0_REG(AFEN0, afen)
TYPE1_REG(AFEN1, afen)
		
struct GPIO_PUD_bits {
	unsigned pud: 2,
			 res: 30;
};

union GPIO_PUD_reg {
		uint32_t reg;
		struct GPIO_PUD_bits field;
};

TYPE0_REG (PUDCLK0, pudclk)
TYPE1_REG (PUDCLK1, pudclk)

#define TYPE0_REG_NAME (NAME) volatile union GPIO_ ## NAME ## _reg*
#define TYPE1_REG_NAME (NAME) volatile union GPIO_ ## NAME ## _reg*

#define GPIO_BASE 		0x7e200000
#define GPIO_FSEL0		(*(volatile union GPIO_FSEL_reg*) GPIO_BASE + 0x00)
#define GPIO_FSEL1		(*(volatile union GPIO_FSEL_reg*) GPIO_BASE + 0x04) 
#define GPIO_FSEL2		(*(volatile union GPIO_FSEL_reg*) GPIO_BASE + 0x08)
#define GPIO_FSEL3 		(*(volatile union GPIO_FSEL_reg*) GPIO_BASE + 0x0c)
#define GPIO_FSEL4 		(*(volatile union GPIO_FSEL_reg*) GPIO_BASE + 0x10)
#define GPIO_FSEL5 		(*(volatile union GPIO_FSEL5_reg*) GPIO_BASE + 0x14)
#define GPIO_SET0		(*(TYPE0_REG_NAME (SET0)) GPIO_BASE + 0x1c)
#define GPIO_SET1 		(*(TYPE1_REG_NAME (SET1)) GPIO_BASE + 0x20)
#define GPIO_CLR0 		(*(TYPE0_REG_NAME (CLR0)) GPIO_BASE + 0x28)
#define GPIO_CLR1 		(*(TYPE1_REG_NAME (CLR1)) GPIO_BASE + 0x2c)
#define GPIO_LEV0		(*(TYPE0_REG_NAME (LEV0)) GPIO_BASE + 0x34)
#define GPIO_LEV1		(*(TYPE1_REG_NAME (LEV1)) GPIO_BASE + 0x38)
#define GPIO_EDS0 		(*(TYPE0_REG_NAME (EDS0)) GPIO_BASE + 0x40)
#define GPIO_EDS1		(*(TYPE1_REG_NAME (EDS1)) GPIO_BASE + 0x44)
#define GPIO_REN0 		(*(TYPE0_REG_NAME (REN0)) GPIO_BASE + 0x4c)
#define GPIO_REN1 		(*(TYPE1_REG_NAME (REN1)) GPIO_BASE + 0x50)
#define GPIO_FEN0 		(*(TYPE0_REG_NAME (FEN0)) GPIO_BASE + 0x58)
#define GPIO_FEN1 		(*(TYPE1_REG_NAME (FEN1)) GPIO_BASE + 0x5c)
#define GPIO_HEN0 		(*(TYPE0_REG_NAME (HEN0)) GPIO_BASE + 0x64)
#define GPIO_HEN1		(*(TYPE1_REG_NAME (HEN1)) GPIO_BASE + 0x68)
#define GPIO_LEN0 		(*(TYPE0_REG_NAME (LEN0)) GPIO_BASE + 0x70)
#define GPIO_LEN1 		(*(TYPE1_REG_NAME (LEN1)) GPIO_BASE + 0x74)
#define GPIO_AREN0 		(*(TYPE0_REG_NAME (AREN0)) GPIO_BASE + 0x7c)
#define GPIO_AREN1		(*(TYPE1_REG_NAME (AREN1)) GPIO_BASE + 0x80)
#define GPIO_AFEN0 		(*(TYPE0_REG_NAME (AFEN0)) GPIO_BASE + 0x88)
#define GPIO_AFEN1		(*(TYPE1_REG_NAME (AFEN1)) GPIO_BASE + 0x8c)
#define GPIO_PUD		(*(volatile union GPIO_PUD_reg*) GPIO_BASE + 0x94)
#define GPIO_PUDCLK0	(*(TYPE0_REG_NAME (PUDCLK0)) GPIO_BASE + 0x98) 
#define GPIO_PUDCLK1	(*(TYPE1_REG_NAME (PUDCLK1)) GPIO_BASE + 0x9c)

#endif
