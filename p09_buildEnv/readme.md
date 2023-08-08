This folder holds a reference to understand build procedure and linker script for bare metal embedded systems (ARM Cortex-M4 processor).
It consists of the following files:

1 - Makefile - used to create build targets with its option flags, etc.
2 - stm32_ls.ld - Linker script, used to instruct the compiler where to place various sections of code
3 - stm32_startup.c - startup file, implements RAM initialization, as well as Vector Table definition
4 - Source files (.c) hold implementation for setting a pin (connected to a LED on the board) based
    on the state of an input pin (connected to a push button on the board)

Steps for building, flash and debugging:

1 - Run "make clean" for removing all files and start a fresh build
2 - Run "make all" or simply "make". This will generate the .elf file among others
3 - Run "make load" to start the OpenOCD connection
4 - Using a different terminal, run "arm-none-eabi-gdb" command
5 - Once in GDB, run "target remote localhost:3333" to establish the connection between OpenOCD and GDB. 
    The host PC is now ready to talk to the target (micro)
6 - For flashing, run "monitor reset init" to reset the micro and halt it. 
    Then, run "monitor flash write_image erase (filename.elf)"
7 - Run "monitor reset init" and "monitor resume" and observe code execution

This has been done based on course "Embedded Systems Programming on ARM Cortex-M3/M4 Processor" from FastBit Embedded Brain Academy