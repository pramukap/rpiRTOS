# Design heavily influenced by TI's TM4C Tivaware Makefile

# Definitions
CC=arm-none-eabi-gcc
OBJCPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump

LSCRIPT=${BPATH}/linker.ld
OPTIMIZATION_LVL=-O2

ROOT=..
CPATH=${ROOT}/src
IPATH=${ROOT}/src/inc
BPATH=${ROOT}/build

# nostartfiles means no standard libraries are included
# freestanding means the compiler doesn't assume that standard lib functions have their typical defintions
CFLAGS=	-mfpu=vfp			\
		-mfloat-abi=hard	\
		-march=armv6zk		\
		-mtune=arm1176jzf-s	\
		-nostartfiles		\
	   	-ffreestanding		\
	   	${OPTIMIZATION_LVL}	\
	   	-Wall				\
	   	-Wextra				\
	   	-fpic				\
	   	${patsubst %,-I%,${subst :, ,${IPATH}}}	# borrowed directly from Tivaware Makefile, path to header files
#		-mcpu=arm1176jzf-s	\	
#	   	-std=gnu99			

AFLAGS=	-mfpu=vfp			\
		-mfloat-abi=hard	\
		-march=armv6zk		\
		-mtune=arm1176jzf-s	\
		-nostartfiles		\
	   	-ffreestanding		\
	   	${patsubst %,-I%,${subst :, ,${IPATH}}} # borrowed directly from Tivaware Makefile
#		-mcpu=arm1176jzf-s	\
#	   	-fpic				\

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

# Makefile build defintions
# generate OS image
#${BPATH}/%.img: %.elf
#	${OBJCPY} ${<} -O binary ${@}	

# link object code and generate OS image
# filter modified from Tivaware Makefile
${BPATH}/%.elf:
	${CC} ${LFLAGS} -o ${@} $(filter %.o, ${^}) 
	${OBJCPY} ${@} -O binary ${@:.elf=.img}	# file extension substitution modified from Tivaware

# generate object code for assembly file
${BPATH}/%.o: ${CPATH}/%.s
	${CC} ${AFLAGS} -o ${@} -c ${<}

# generate object code for c file
${BPATH}/%.o: ${CPATH}/%.c
	${CC} ${CFLAGS} -o ${@} -c ${<}

# Rules
all: ${BPATH}/${MAIN}.elf

#${BPATH}/${MAIN}.img: ${BPATH}/${MAIN}.elf

${BPATH}/${MAIN}.elf: ${BPATH}/${MAIN}.o
${BPATH}/${MAIN}.elf: ${BPATH}/common.o
#${BPATH}/${MAIN}.elf: ${BPATH}/boot.o
${BPATH}/${MAIN}.elf: ${BPATH}/uart0.o
${BPATH}/${MAIN}.elf: ${BPATH}/led.o
#${BPATH}/${MAIN}.elf: ${BPATH}/shell.o

${BPATH}/${MAIN}.o: ${CPATH}/${MAIN}.c
${BPATH}/common.o: ${CPATH}/common.c
#${BPATH}/boot.o: ${CPATH}/boot.s
${BPATH}/uart0.o: ${CPATH}/uart0.c
${BPATH}/led.o: ${CPATH}/led.c
#${BPATH}/shell.o: ${CPATH}/shell.c

load:
	rm ../build/disk/kernel.img
	cp ../build/kernel.img ../build/disk/

dump: ${BPATH}/${MAIN}.elf
	${OBJDUMP} --full-contents ${BPATH}/${MAIN}.elf > kernel.dump
	${OBJDUMP} --disassemble ${BPATH}/${MAIN}.elf > kernel.S
	${OBJDUMP} --all-headers ${BPATH}/${MAIN}.elf > kernel.info

tty:
	dmesg | grep tty 

serial:
	sudo minicom -s

sll:
	./elf2sll

clean: ${BPATH}/${MAIN}.S ${BPATH}/${MAIN}.info
	rm ${BPATH}/*.o ${BPATH}/*.elf ${BPATH}/*.img ${BPATH}/*.dump ${BPATH}/*.S ${BPATH}/*.info ${BPATH}/temp ${BPATH}/*.sll

