**Stellaris Launchpad TM4C123G ARM Cortex-M4 Template Project**

A very basic template project for the Texas Instruments Stellaris Launchpad EK-TM4C123GXL using GNU toolchain

This simple example uses direct register access method so only the register definitions from the tm4c123ge6pm.h file is needed to be included.

If the StellarisWare drivers and hardware headers are needed, just include the required header files, the makefile will link them for you.

For flashing lm4tools project is used:

https://github.com/utzig/lm4tools

To compile:
	
	$ make all

To flash:
	
	$ make flash
