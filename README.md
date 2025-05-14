# Linux terminal based project for TM4C123GXL

When I started learning more about embedded development someone recommended me the development board [EK-TM4C123GXL](https://www.ti.com/tool/EK-TM4C123GXL).
To my surprise most of the tutorials used different IDEs on Windows to get started. I didn't want abstract away most of the processes behind programming and flashing
a MCU and wanted to use the command line on Linux. This is just a simple setup to work with the MCU using command line tools.

## Requirements

- [lm4tools]("https://github.com/utzig/lm4tools"): for flashing code onto the microcontroller
- [Arm GNU Toolchain]("https://developer.arm.com/downloads/-/gnu-rm"): for cross compiling written C code to targeted platform
