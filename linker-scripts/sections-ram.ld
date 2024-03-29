/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus/)
 * Copyright (c) 2022 Liviu Ionescu.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
 */

/*
 * Linker script for RAM only configurations.
 *
 * Static constructors/destructors use the new .init_array/.fini_array
 * definitions; the old .init/.fini are no longer used, but the sections
 * must still be present when using librdimon.
 *
 * TODO: check elf-redboot.ld
 *
 * The heap starts immediately after the last statically allocated
 * .bss/.noinit section (the _end symbol), and extends up to the stack.
 *
 * To make use of the multi-region initialisations, define
 * MICRO_OS_PLUS_INCLUDE_STARTUP_INIT_MULTIPLE_RAM_SECTIONS
 * for the startup.cpp file.
 */

/* TODO: set OUTPUT_FORMAT & OUTPUT_ARCH */
/*
 * The entry point is important for debuggers and simulators, the
 * hardware has its own notion of the startup address.
 */
ENTRY(Reset_Handler)

/*
 * The '__stack' definition is required by newlib crt0; do not remove it.
 * The stack is located at the very end of the RAM region.
 * With librdimon, crt0.S gets the heap and the stack from the debugger.
 */
__stack = DEFINED(__stack) ? __stack : ORIGIN(RAM) + LENGTH(RAM);
__stack_size = DEFINED(__stack_size) ? __stack_size : 16K;


SECTIONS
{
  /*
   * For AArch64 devices, the beginning of the startup code is stored in
   * the .interrupt_vectors section.
   */
  .interrupt_vectors : ALIGN(4)
  {
    __vectors_start = ABSOLUTE(.) ;

    KEEP(*(.interrupt_vectors .interrupt_vectors.*))    /* Interrupt vectors */
  } >RAM

  /*
   * Dynamic Run Time Metadata.
   * Normally the debugger reaches this section by resolving a symbol,
   * but in case it should scan memory for the magic, better place this
   * section as early as possible.
   */
  .drtm : ALIGN(4)
  {
    KEEP(*(.drtm .drtm.*))
  } >RAM

  /*
   * This section is here for convenience, to store the
   * startup code at the beginning of the memory, hoping that
   * this will increase the readability of the listing.
   */
  .after_vectors : ALIGN(4)
  {
    *(.after_vectors .after_vectors.*)	/* Startup code and ISRs */
  } >RAM

  /*
   * Memory regions initialization arrays.
   *
   * There are two kinds of arrays for each RAM region, one for
   * data and one for bss. Each is iterated at startup and the
   * region initialization is performed.
   *
   * The data array includes:
   * - from (LOADADDR())
   * - region_begin (ADDR())
   * - region_end (ADDR()+SIZEOF())
   *
   * The bss array includes:
   * - region_begin (ADDR())
   * - region_end (ADDR()+SIZEOF())
   *
   * WARNING: It is mandatory that the regions are word aligned,
   * since the initialization code works only on words.
   */
  .mem_inits : ALIGN(4)
  {
    PROVIDE_HIDDEN(__data_regions_array_begin__ = .); /* µOS++ specific. */

    LONG(LOADADDR(.data));
    LONG(ADDR(.data));
    LONG(ADDR(.data)+SIZEOF(.data));

    /* If more DATA regions are needed, add more such records. */

    PROVIDE_HIDDEN(__data_regions_array_end__ = .); /* µOS++ specific. */

    PROVIDE_HIDDEN(__bss_regions_array_begin__ = .); /* µOS++ specific. */

    LONG(ADDR(.bss));
    LONG(ADDR(.bss)+SIZEOF(.bss));

    /* If more BSS regions are needed, add more such records. */

    PROVIDE_HIDDEN(__bss_regions_array_end__ = .); /* µOS++ specific. */
  } >RAM

  /*
   * The preinit code, i.e. an array of pointers to initialization
   * functions to be performed before constructors.
   */
  .preinit_array : ALIGN(4)
  {
    /*
     * PROVIDE not used intentionally,
     * this symbol must not be used for other purposes.
     */
    __preinit_array_start = .;   /* Used by crt0.S */

    /*
     * Used to run the system inits before anything else.
     */
    KEEP(*(.preinit_array_sysinit .preinit_array_sysinit.*))

    /*
     * Used for other platform inits.
     */
    KEEP(*(.preinit_array_platform .preinit_array_platform.*))

    /*
     * The application inits. If you need to enforce some order in
     * execution, create new sections, as before.
     */
    KEEP(*(.preinit_array .preinit_array.*))

    __preinit_array_end = .;     /* Used by crt0.S */
  } >RAM

  /*
   * The init code, i.e. an array of pointers to static constructors.
   */
  .init_array : ALIGN(4)
  {
    /* PROVIDE not used intentionally, this symbol must not be used */
    __init_array_start = .;        /* Used by crt0.S */

    KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP(*(.init_array EXCLUDE_FILE(*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))

    __init_array_end = .;          /* Used by crt0.S */
  } >RAM

  /*
   * The fini code, i.e. an array of pointers to static destructors.
   */
  .fini_array : ALIGN(4)
  {
    /* PROVIDE not used intentionally, this symbol must not be used. */
    __fini_array_start = .;        /* Standard newlib definition. */

    KEEP(*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
    KEEP(*(.fini_array EXCLUDE_FILE(*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))

    __fini_array_end = .;          /* Standard newlib definition. */
  } >RAM

  /*
   * The program code.
   */
  .text : ALIGN(4)
  {
    *(.text.unlikely .text.unlikely.*)
    *(.text.startup .text.startup.*)
    *(.text .text.*)
    *(.gnu.linkonce.t.*)
  } >RAM


  /*
   * Mandatory for _init() to work, with crt0.
   * Called in __libc_fini_array().
   */
  .init : ALIGN(4)
  {
    KEEP (*(.init))
  } >RAM

  /*
   * Mandatory for _fini() to work, with crt0.
   * Called in __libc_fini_array().
   */
  .fini : ALIGN(4)
  {
    KEEP (*(.fini))
  } >RAM

  . = ALIGN(4);
  PROVIDE(__etext = .);
  PROVIDE(_etext = .);
  PROVIDE(etext = .);

  /*
   * C++ virtual tables.
   */
  .vtable : ALIGN(4)
  {
    KEEP(*(vtable))
  } >RAM

  /*
   * Exception frames.
   */
  .exceptions : ALIGN(4)
  {
    KEEP(*(.eh_frame*))
    *(.gcc_except_table)
  } >RAM

  /*
   * Stub sections generated by the linker, to glue together
   * ARM and Thumb code. .glue_7 is used for ARM code calling
   * Thumb code, and .glue_7t is used for Thumb code calling
   * ARM code. Apparently always generated by the linker, for some
   * architectures, so better leave them here.
   */
  .glue : ALIGN(4)
  {
    *(.glue_7)
    *(.glue_7t)
  } >RAM


  /* ARM magic sections, after exceptions. */
  .ARM.extab : ALIGN(4)
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } >RAM

  . = ALIGN(4);
  __exidx_start = .;
  .ARM.exidx : ALIGN(4)
  {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } >RAM
  __exidx_end = .;

  /*
   * Read-only data (constants)
   */
  .rodata : ALIGN(4)
  {
    *(.rodata .rodata.*)
    *(.constdata .constdata.*)
    *(.gnu.linkonce.r.*)
  } >RAM

  . = ALIGN(4);
  PROVIDE( _data = . );

  /*
   * The initialised data section.
   *
   * The program executes knowing that the data is in RAM
   * but the loader puts the initial values in FLASH.
   * The startup will copy the initial values from FLASH to RAM.
   */
  .data : ALIGN(4)
  {
    FILL(0xFF)

    __data_start__ = . ;           /* Standard newlib definition. */
    __data_begin__ = . ;           /* µOS++ specific */
    *(.data_begin .data_begin.*)   /* µOS++ __data_begin_guard */

    *(.data .data.*)
    *(.gnu.linkonce.d.*)

    *(.sdata .sdata.*)
    *(.gnu.linkonce.s.*)

    *(.data_end .data_end.*)       /* µOS++ __data_end_guard; must be last */
    . = ALIGN(4);
    __data_end__ = . ;             /* Standard newlib definition. */
  } >RAM

  /*
   * This address is used by the µOS++ startup code to
   * initialise the .data section.
   */
  __data_load_addr__ = LOADADDR(.data);

  . = ALIGN(4);
  PROVIDE( __edata = . );
  PROVIDE( _edata = . );
  PROVIDE( edata = . );

  /*
   * The uninitialised data sections. NOLOAD is used to avoid
   * the "section `.bss' type changed to PROGBITS" warning
   */

  /* The primary uninitialised data section. */
  .bss (NOLOAD) : ALIGN(4)
  {
    __bss_start = .;               /* Standard newlib definition. */
    __bss_start__ = .;             /* Standard newlib definition. */
    __bss_begin__ = .;          /* µOS++ specific */
    *(.bss_begin .bss_begin.*)    /* µOS++ __bss_begin_guard */

    *(.sbss .sbss.*)
    *(.gnu.linkonce.sb.*)

    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)

    *(.bss_end .bss_end.*)         /* µOS++ __bss_end_guard; must be last */
    . = ALIGN(4);
    __bss_end__ = .;               /* Standard newlib definition. */
    __bss_end = .;                 /* Standard newlib definition. */
  } >RAM

  /*
   * Similar to .bss, but not initialised to zero. µOS++ extension.
   */
  .noinit (NOLOAD) : ALIGN(4)
  {
    __noinit_begin__ = .;          /* µOS++ extension. */

    *(.noinit .noinit.*)

    . = ALIGN(4) ;
    __noinit_end__ = .;            /* µOS++ extension. */
  } >RAM

  /* _sbrk() expects at least word alignment. */
  . = ALIGN(8);
  PROVIDE( __end__ = . ); /* Used by crt0.S arm & aarch64 */
  PROVIDE( __end = . ); /* Used by crt0.S sparc, m68k */
  PROVIDE( _end = . ); /* Used by libgloss sbrk() */
  PROVIDE( end = . ); /* Used by newlib _sbrk() arm & aarch64 */

  PROVIDE( __heap_begin__ = . );     /* µOS++ extension. */

  /*
   * It should generate an error if the heap overrides the stack.
   */
  .stack __stack - __stack_size :
  {
    PROVIDE( _heap_end = . );      /* Used by sbrk in some architectures */
    PROVIDE( _heap_end_ = . );     /* Used by sbrk in some architectures */
    PROVIDE( __heap_end = . );     /* Used by sbrk in some architectures */

    PROVIDE( __heap_end__ = . );   /* µOS++ extension. */

    /*
     * libgloss also uses `__heap_limit` in _sbrk(), initially set to
     * 0xcafedead and later updated to the value returned by SYS_HEAPINFO.
     */
    . += __stack_size;
  } >RAM

  /* ---------------------------------------------------------------------- */
  /* After that there are only debugging sections. */

  /*
   * Stabs debugging sections.
   */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }

  /*
   * DWARF debug sections.
   * Symbols in the DWARF debugging sections are relative to the beginning
   * of the section so we begin them at 0.
   */

  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
}
