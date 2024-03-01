//*****************************************************************************
//
// blinky.c - Simple example to blink the on-board LED.
//
// Copyright (c) 2012-2020 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.2.0.295 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>

/* #include "driverlib/debug.h" */
/* #include "driverlib/gpio.h" */
/* #include "driverlib/sysctl.h" */
/* #include "inc/hw_memmap.h" */

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Blinky (blinky)</h1>
//!
//! A very simple example that blinks the on-board LED using direct register
//! access.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line) {
  while (1)
    ;
}
#endif

//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************
void wait();

int main(void) {
  unsigned int *RCGCGPIO = (unsigned int *)0x400FE608U;
  unsigned int *GPIOFDIR = (unsigned int *)0x40025400U;
  unsigned int *GPIOFDEN = (unsigned int *)0x4002551CU;
  unsigned int *GPIOFDATA = (unsigned int *)0x40025000U;

  *RCGCGPIO = 0x20;
  *GPIOFDIR = 0x0EU;
  *GPIOFDEN = 0x0EU;

  /* *((volatile unsigned int *)0x400FE608U) = 0x20U; */
  /* *((volatile unsigned int *)0x40025400U) = 0x0EU; */
  /* *((volatile unsigned int *)0x4002551CU) = 0x0EU; */

  while (1) {
    // 0b 0000 1110
    *GPIOFDATA = 0x02U;
    wait();
    *GPIOFDATA = 0x04U;
    wait();
  }
  return 0;
}

void wait(void) {
  int counter = 0;
  while (counter < 1000000000) {
    counter++;
  }
}
