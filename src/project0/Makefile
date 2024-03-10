PART=TM4C123GH6PM

#
# The base directory for TivaWare.
#
ROOT=../..

#
# Include the common make definitions.
#
# include ${ROOT}/makedefs


COMPILER=gcc
CFLAGSgcc=-DTARGET_IS_TM4C123_RB1
PREFIX:=arm-none-eabi
CC=${PREFIX}-gcc
AR=${PREFIX}-ar
OBJCOPY=${PREFIX}-objcopy
LD=${PREFIX}-ld
LM4FLASH = lm4flash

CPU=-mcpu=cortex-m4
FPU=-mfpu=fpv4-sp-d16 -mfloat-abi=hard

LDFLAGS=--gc-sections
AFLAGS=-mthumb \
    ${CPU}  \
       ${FPU}  \
       -MD
CFLAGS=-mthumb             \
       ${CPU}              \
       ${FPU}              \
       -ffunction-sections \
       -fdata-sections     \
       -MD                 \
       -std=c99            \
       -Wall               \
       -pedantic           \
       -DPART_${PART}      \
       -c

LIBGCC:=${shell ${CC} ${CFLAGS} -print-libgcc-file-name}
LIBC:=${shell ${CC} ${CFLAGS} -print-file-name=libc.a}
LIBM:=${shell ${CC} ${CFLAGS} -print-file-name=libm.a}

ifdef DEBUG
CFLAGS+=-g -D DEBUG -O0
else
CFLAGS+=-Os
endif

CFLAGS+=${CFLAGSgcc}
CFLAGS+= -I${IPATH}
AFLAGS+= -I${IPATH}

build/%.o: %.c
	@${CC} ${CFLAGS} -D${COMPILER} -o ${@} ${<}

build/%.o: %.S
	@${CC} ${AFLAGS} -D${COMPILER} -o ${@} -c ${<}

build/%.a:
	@${AR} -cr ${@} ${^}

build/%.axf:
	@if [ 'x${SCATTERgcc_${notdir ${@:.axf=}}}' = x ];					\
	then																 \
		ldname="${ROOT}/gcc/standalone.ld";							  \
	else																 \
		ldname="${SCATTERgcc_${notdir ${@:.axf=}}}";					 \
	fi;																  \
	${LD} -T $${ldname}												   \
		--entry ${ENTRY_${notdir ${@:.axf=}}}						   \
		${LDFLAGSgcc_${notdir ${@:.axf=}}}							  \
		${LDFLAGS} -o ${@} $(filter %.o %.a, ${^})					  \
		'${LIBM}' '${LIBC}' '${LIBGCC}'
	@${OBJCOPY} -O binary ${@} ${@:.axf=.bin}

#
# Where to find source files that do not live in this directory.
#

#
# Where to find header files that do not live in the source directory.
#
IPATH=../..

PROJ_NAME=project0

#
# The default rule, which causes the Project Zero Example to be built.
#
all: build/$(PROJ_NAME).axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf gcc ${wildcard *~}

lm4flash: build/$(PROJ_NAME).bin
		$(LM4FLASH) $<

flash: clean all lm4flash

#
# Rules for building the Project Zero Example.
#
build/$(PROJ_NAME).axf: build/$(PROJ_NAME).o
build/$(PROJ_NAME).axf: startup_${COMPILER}.o
build/$(PROJ_NAME).axf: $(PROJ_NAME).ld
SCATTERgcc_$(PROJ_NAME)=$(PROJ_NAME).ld
ENTRY_$(PROJ_NAME)=ResetISR
