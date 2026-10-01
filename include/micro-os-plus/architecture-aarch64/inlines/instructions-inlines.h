/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2017-2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can be
 * obtained from https://opensource.org/licenses/mit.
 */

/**
 * @file
 * @brief Inline definitions of the AArch64 functions wrapping CPU
 * instructions.
 *
 * @details
 * The architecture specific C functions contain the inline assembly; all
 * the other forms (portable C, and both C++ namespaces) forward to them,
 * so that each instruction is written only once.
 *
 * This file is included at the end of `instructions.h` and must not be
 * included directly.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_AARCH64_INLINES_INSTRUCTIONS_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_AARCH64_INLINES_INSTRUCTIONS_INLINES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------
// Inline implementations for the AArch64 architecture instructions.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

  /**
   * @details
   * The assembly statement is `volatile`, so that it is not removed; it
   * has no clobbers, since the instruction has no effect on registers or
   * memory.
   */
  static inline __attribute__ ((always_inline)) void
  aarch64_architecture_nop (void)
  {
    __asm__ volatile (

        " nop "

        : /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
  }

  /**
   * @details
   * The `"memory"` clobber prevents the compiler from moving or
   * eliminating memory accesses across the breakpoint, so that the
   * debugger sees all the preceding stores, and the code after it reads
   * again any values changed from the debugger.
   */
  static inline __attribute__ ((always_inline)) void
  aarch64_architecture_brk (void)
  {
    __asm__ volatile (

        // See 'aarch64-tdep.c' in GDB source, 'aarch64_default_breakpoint'
        // " .inst 0xd4200000 "
        " brk #0 "

        : /* Outputs */
        : /* Inputs */
        : "memory" /* Clobbers */
    );
  }

  /**
   * @details
   * Forwards to `aarch64_architecture_brk()`.
   */
  static inline __attribute__ ((always_inline)) void
  aarch64_architecture_bkpt (void)
  {
    aarch64_architecture_brk ();
  }

  /**
   * @details
   * The `"memory"` clobber forces the compiler to read again, after the
   * instruction, any values that interrupt handlers may have changed.
   */
  static inline __attribute__ ((always_inline)) void
  aarch64_architecture_wfi (void)
  {
    __asm__ volatile (

        " wfi "

        : /* Outputs */
        : /* Inputs */
        : "memory" /* Clobbers */
    );
  }

  /**
   * @details
   * The `"memory"` clobber makes the hardware barrier also a compiler
   * barrier, so that memory accesses are not moved across it.
   */
  static inline __attribute__ ((always_inline)) void
  aarch64_architecture_dsb (void)
  {
    __asm__ volatile (

        " dsb sy "

        : /* Outputs */
        : /* Inputs */
        : "memory" /* Clobbers */
    );
  }

  /**
   * @details
   * The `"memory"` clobber makes the hardware barrier also a compiler
   * barrier, so that memory accesses are not moved across it.
   */
  static inline __attribute__ ((always_inline)) void
  aarch64_architecture_isb (void)
  {
    __asm__ volatile (

        " isb "

        : /* Outputs */
        : /* Inputs */
        : "memory" /* Clobbers */
    );
  }

  /**
   * @details
   * Forwards to `aarch64_architecture_nop()`.
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_nop (void)
  {
    aarch64_architecture_nop ();
  }

  /**
   * @details
   * Forwards to `aarch64_architecture_brk()`.
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_brk (void)
  {
    aarch64_architecture_brk ();
  }

  /**
   * @details
   * Forwards to `aarch64_architecture_wfi()`.
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_wfi (void)
  {
    aarch64_architecture_wfi ();
  }

  /**
   * @details
   * Forwards to `aarch64_architecture_dsb()`.
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_data_barrier (void)
  {
    aarch64_architecture_dsb ();
  }

  /**
   * @details
   * Forwards to `aarch64_architecture_isb()`.
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_instruction_barrier (void)
  {
    aarch64_architecture_isb ();
  }

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

namespace aarch64::architecture
{
  // --------------------------------------------------------------------------

  /**
   * @details
   * Forwards to `aarch64_architecture_nop()`.
   */
  inline __attribute__ ((always_inline)) void
  nop (void)
  {
    aarch64_architecture_nop ();
  }

  /**
   * @details
   * Forwards to `aarch64_architecture_brk()`.
   */
  inline __attribute__ ((always_inline)) void
  brk (void)
  {
    aarch64_architecture_brk ();
  }

  /**
   * @details
   * Forwards to `brk()`.
   */
  inline __attribute__ ((always_inline)) void
  bkpt (void)
  {
    brk ();
  }

  /**
   * @details
   * Forwards to `aarch64_architecture_wfi()`.
   */
  inline __attribute__ ((always_inline)) void
  wfi (void)
  {
    aarch64_architecture_wfi ();
  }

  /**
   * @details
   * Forwards to `aarch64_architecture_dsb()`.
   */
  inline __attribute__ ((always_inline)) void
  dsb (void)
  {
    aarch64_architecture_dsb ();
  }

  /**
   * @details
   * Forwards to `aarch64_architecture_isb()`.
   */
  inline __attribute__ ((always_inline)) void
  isb (void)
  {
    aarch64_architecture_isb ();
  }

  // --------------------------------------------------------------------------
} // namespace aarch64::architecture

namespace micro_os_plus::architecture
{
  // --------------------------------------------------------------------------

  /**
   * @details
   * Forwards to `aarch64::architecture::nop()`.
   */
  inline __attribute__ ((always_inline)) void
  nop (void)
  {
    aarch64::architecture::nop ();
  }

  /**
   * @details
   * Forwards to `aarch64::architecture::brk()`.
   */
  inline __attribute__ ((always_inline)) void
  brk (void)
  {
    aarch64::architecture::brk ();
  }

  /**
   * @details
   * Forwards to `aarch64::architecture::wfi()`.
   */
  inline __attribute__ ((always_inline)) void
  wfi (void)
  {
    aarch64::architecture::wfi ();
  }

  /**
   * @details
   * Forwards to `aarch64::architecture::dsb()`.
   */
  inline __attribute__ ((always_inline)) void
  data_barrier (void)
  {
    aarch64::architecture::dsb ();
  }

  /**
   * @details
   * Forwards to `aarch64::architecture::isb()`.
   */
  inline __attribute__ ((always_inline)) void
  instruction_barrier (void)
  {
    aarch64::architecture::isb ();
  }

  // --------------------------------------------------------------------------
} // namespace micro_os_plus::architecture

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_AARCH64_INLINES_INSTRUCTIONS_INLINES_H_

// ----------------------------------------------------------------------------
