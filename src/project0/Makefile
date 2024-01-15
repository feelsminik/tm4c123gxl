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
all: ${COMPILER}
all: ${COMPILER}/$(PROJ_NAME).axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

flash: gcc/$(PROJ_NAME).bin
		$(LM4FLASH) $<

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the Project Zero Example.
#
${COMPILER}/$(PROJ_NAME).axf: ${COMPILER}/$(PROJ_NAME).o
${COMPILER}/$(PROJ_NAME).axf: startup_${COMPILER}.o
${COMPILER}/$(PROJ_NAME).axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/$(PROJ_NAME).axf: $(PROJ_NAME).ld
SCATTERgcc_$(PROJ_NAME)=$(PROJ_NAME).ld
ENTRY_$(PROJ_NAME)=ResetISR
CFLAGSgcc=-DTARGET_IS_TM4C123_RB1

ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
