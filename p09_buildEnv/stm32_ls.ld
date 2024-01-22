/* ENTRY command is used to tell which is the entry point to start code 
   execution */
ENTRY(Reset_Handler)

/* MEMORY command is used to specify different memories on the device */
MEMORY
{
    FLASH(rx): ORIGIN =0x08000000, LENGTH =1024K
    SRAM(rwx): ORIGIN =0x20000000, LENGTH =128K
}
 

/* SECTIONS command describes different sections */
SECTIONS
{
    /* This section should include .text section of all input files */
    .text :
    {
        /* Merge all .isr_vector section of all input files */
        *(.isr_vector)
        /* Merge all .text section of all input files */
        *(.text)
        *(.text.*)
        *(.init)
        *(.fini)
        /* Merge all .rodata section of all input files */
        *(.rodata)
        *(.rodata.*)
        /* Code should be aligned to natural size boudaries for instruction
           fetching.
        */
        . = ALIGN(4);
        /* Create a symbol "_etext" which denotes the end of text section.
           The value assigned to it is the Location Counter '.' operator,
           which will return the location address information.
         */
        _etext = .;
    } >FLASH AT>FLASH /* First parameter specifies  */

    _la_data = LOADADDR(.data);

    /* This section should include .data section of all input files */
    .data :
    {
        _sdata = .;
        /* Merge all .data section of all input files */
        *(.data)
        *(.data.*)
        /* Code should be aligned to natural size boudaries for instruction
           fetching.
        */
        . = ALIGN(4);
        _edata = .;
    } >SRAM AT>FLASH /* First parameter determines where the data is ultimately
                        loaded to. Second parameter determines where data will
                        be loaded from. */

    .bss :
    {
        _sbss = .;
        /* Below symbol is needed by the std lib: nano-libc */
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss.*)
        /* Code should be aligned to natural size boudaries for instruction
           fetching.
        */
        . = ALIGN(4);
        _ebss = .;
        /* Below symbol is needed by the std lib: nano-libc */
        __bss_end__ = _ebss;
        . = ALIGN(4);
        /* Below symbol is needed by the std lib: nano-libc */
        end = .;
        /* Below symbol is needed by semi hosting lib: rdimon */
        __end__ = .;
    }> SRAM 
}