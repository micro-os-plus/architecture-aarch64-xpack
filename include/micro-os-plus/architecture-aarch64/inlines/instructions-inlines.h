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

  static inline __attribute__ ((always_inline)) void
  aarch64_architecture_bkpt (void)
  {
    aarch64_architecture_brk ();
  }

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

  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_nop (void)
  {
    aarch64_architecture_nop ();
  }

  /**
   * `break` instruction.
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_brk (void)
  {
    aarch64_architecture_brk ();
  }

  /**
   * `wfi` instruction.
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_wfi (void)
  {
    aarch64_architecture_wfi ();
  }

  /**
   * Data synchronisation barrier (`dsb sy`).
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_data_barrier (void)
  {
    aarch64_architecture_dsb ();
  }

  /**
   * Instruction synchronisation barrier (`isb`).
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

  inline __attribute__ ((always_inline)) void
  nop (void)
  {
    aarch64_architecture_nop ();
  }

  inline __attribute__ ((always_inline)) void
  brk (void)
  {
    aarch64_architecture_brk ();
  }

  inline __attribute__ ((always_inline)) void
  bkpt (void)
  {
    brk ();
  }

  inline __attribute__ ((always_inline)) void
  wfi (void)
  {
    aarch64_architecture_wfi ();
  }

  inline __attribute__ ((always_inline)) void
  dsb (void)
  {
    aarch64_architecture_dsb ();
  }

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

  inline __attribute__ ((always_inline)) void
  nop (void)
  {
    aarch64::architecture::nop ();
  }

  inline __attribute__ ((always_inline)) void
  brk (void)
  {
    aarch64::architecture::brk ();
  }

  inline __attribute__ ((always_inline)) void
  wfi (void)
  {
    aarch64::architecture::wfi ();
  }

  inline __attribute__ ((always_inline)) void
  data_barrier (void)
  {
    aarch64::architecture::dsb ();
  }

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
