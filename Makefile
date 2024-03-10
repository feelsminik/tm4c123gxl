PROJ_NAME=hello_blink
COMPILER=gcc
LM4FLASH = lm4flash

PREFIX:=arm-none-eabi
CC=${PREFIX}-gcc
AR=${PREFIX}-ar
OBJCOPY=${PREFIX}-objcopy
LD=${PREFIX}-ld

PART=TM4C123GH6PM
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
ifdef DEBUG
CFLAGS+=-g -D DEBUG -O0
else
CFLAGS+=-Os
endif
CFLAGS+=-DTARGET_IS_TM4C123_RB1

LIBGCC:=${shell ${CC} ${CFLAGS} -print-libgcc-file-name}
LIBC:=${shell ${CC} ${CFLAGS} -print-file-name=libc.a}
LIBM:=${shell ${CC} ${CFLAGS} -print-file-name=libm.a}


all: build/$(PROJ_NAME).axf

build/$(PROJ_NAME).axf: build/$(PROJ_NAME).o
build/$(PROJ_NAME).axf: build/startup.o

build/$(PROJ_NAME).axf:
	$(LD) -T "linker_script.ld" \
		--entry ResetISR \
		${LDFLAGS} -o $@ $(filter %.o %.a, $^) \
		'${LIBM}' '${LIBC}' '${LIBGCC}'
	@${OBJCOPY} -O binary $@ ${@:.axf=.bin}

build/%.o: src/%.c
	$(CC) $(CFLAGS) -D$(COMPILER) -o $@ $<

build/%.o: %.c
	$(CC) $(CFLAGS) -D$(COMPILER) -o $@ $<

lm4flash: build/$(PROJ_NAME).bin
		$(LM4FLASH) $<

flash: clean all lm4flash

.PHONY: clean
clean:
	@rm -rf gcc ${wildcard *~}
