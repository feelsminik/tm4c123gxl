PART=TM4C123GH6PM

#
# The base directory for TivaWare.
#
ROOT=../..

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

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
build/$(PROJ_NAME).axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
build/$(PROJ_NAME).axf: $(PROJ_NAME).ld
SCATTERgcc_$(PROJ_NAME)=$(PROJ_NAME).ld
ENTRY_$(PROJ_NAME)=ResetISR
