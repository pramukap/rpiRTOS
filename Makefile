CC=arm-none-eabi-gcc

CFLAGS=-mcpu=arm1176jzf-s	\
	   -fpic				\
	   -ffreestanding		\
	   -std=gnu99			\
	   -O2					\
	   -Wall				\
	   -Wextra

AFLAGS=-mcpu=arm1176jzf-s	\
	   -fpic				\
	   -ffreestanding	

LFLAGS=-T					\
	   -ffreestanding		\
	   -O2					\
	   -nostdlib			

BUILD_NAME=kernel.img

#
# Main C filename
#
MAIN=main

#
# The default rule, which causes the Project Zero Example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/${MAIN}.axf

#
# Enable debug code at compile-time
#
debug: CFLAGSgcc+=-DDEBUG
debug: CFLAGSgcc+=-g
debug: all

#
# Enable gdb debugging
# 
gdb: debug
	openocd --file /usr/share/openocd/scripts/board/ek-tm4c123gxl.cfg &
	arm-none-eabi-gdb -tui -command=init.gdb gcc/${MAIN}.axf

#
# The rule to flash the program to the chip.
#
flash:
	lm4flash gcc/${MAIN}.bin

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the Project Zero Example.
#
${COMPILER}/${MAIN}.axf: ${COMPILER}/${MAIN}.o
${COMPILER}/${MAIN}.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/${MAIN}.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/${MAIN}.axf: link.ld
SCATTERgcc_${MAIN}=link.ld
ENTRY_${MAIN}=ResetISR
CFLAGSgcc=-DTARGET_IS_TM4C123_RB1

#
# Rules for building custom drivers.
# ${COMPILER}/${MAIN}.axf: ${COMPILER}/[replace this with name of driver].o
#
${COMPILER}/${MAIN}.axf: ${COMPILER}/OSasm.o

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif

