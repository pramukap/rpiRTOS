# Design heavily influenced by TI's TM4C Tivaware Makefile

# Definitions
CC=arm-none-eabi-gcc
OBJCPY=arm-none-eabi-objcopy

LSCRIPT=${BPATH}/linker.ld
OPTIMIZATION_LVL=-O2

ROOT=..
IPATH=${ROOT}/inc
BPATH=${ROOT}/build

CFLAGS=	-mfpu=vfp			\
		-mfloat-abi=hard	\
		-march=armv6zk		\
		-mtune=arm1176jzf-s	\
		-nostartfiles		\
	   	${OPTIMIZATION_LVL}	\
	   	-Wall				\
	   	-Wextra				\
	   	${patsubst %,-I%,${subst :, ,${IPATH}}}	# borrowed directly from Tivaware Makefile
#		-mcpu=arm1176jzf-s	\	
#	   	-fpic				\
#	   	-ffreestanding		\
#	   	-std=gnu99			

AFLAGS=	-mfpu=vfp			\
		-mfloat-abi=hard	\
		-march=armv6zk		\
		-mtune=arm1176jzf-s	\
		-nostartfiles		\
	   	${patsubst %,-I%,${subst :, ,${IPATH}}} # borrowed directly from Tivaware Makefile
#		-mcpu=arm1176jzf-s	\
#	   	-fpic				\
#	   	-ffreestanding		\

#LFLAGS=-T ${LSCRIPT}		\
#	   -ffreestanding		\
#	   ${OPTIMIZATION_LVL}	\
#	   -nostdlib

LFLAGS=	-mfpu=vfp			\
		-mfloat-abi=hard	\
		-march=armv6zk		\
		-mtune=arm1176jzf-s	\
		-nostartfiles		\
	   	
MAIN=kernel

# generate OS image
#${BPATH}/%.img: %.elf
#	${OBJCPY} ${<} -O binary ${@}	

# link object code and generate OS image
# filter modified from Tivaware Makefile
${BPATH}/%.elf:
	${CC} ${LFLAGS} -o ${@} $(filter %.o, ${^}) 
	${OBJCPY} ${@} -O binary ${@:.elf=.img}	# file extension substitution modified from Tivaware

# generate object code for assembly file
${BPATH}/%.o: %.s
	${CC} ${AFLAGS} -o ${@} -c ${<}

# generate object code for c file
${BPATH}/%.o: %.c
	${CC} ${CFLAGS} -o ${@} -c ${<}

# Rules
all: ${BPATH}/${MAIN}.elf

#${BPATH}/${MAIN}.img: ${BPATH}/${MAIN}.elf

${BPATH}/${MAIN}.elf: ${BPATH}/${MAIN}.o
#${BPATH}/${MAIN}.elf: ${BPATH}/boot.o
${BPATH}/${MAIN}.elf: ${BPATH}/uart0.o
${BPATH}/${MAIN}.elf: ${BPATH}/led.o

${BPATH}/${MAIN}.o: ${MAIN}.c
#${BPATH}/boot.o: boot.s
${BPATH}/uart0.o: uart0.c
${BPATH}/led.o: led.c

tty:
	dmesg | grep tty 

serial:
	sudo minicom -s

clean:
	rm ${BPATH}/*.o ${BPATH}/*.elf ${BPATH}/*.img

