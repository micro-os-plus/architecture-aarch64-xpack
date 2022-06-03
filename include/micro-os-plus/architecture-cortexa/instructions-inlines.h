/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus/)
 * Copyright (c) 2017 Liviu Ionescu.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_CORTEXA_INSTRUCTIONS_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_CORTEXA_INSTRUCTIONS_INLINES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------
// Inline implementations for the Cortex-A architecture instructions.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

  static inline __attribute__ ((always_inline)) void
  cortexa_architecture_nop (void)
  {
    __asm__ volatile(

        " nop "

        : /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
  }

  static inline __attribute__ ((always_inline)) void
  cortexa_architecture_bkpt (void)
  {
#if defined(__ARM_ARCH_8A)
    __asm__ volatile(

        // See 'aarch64-tdep.c' in GDB source, 'aarch64_default_breakpoint'
        // " .inst 0xd4200000 "
        " brk #0 "

        : /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
#elif defined(__ARM_ARCH_7A__)
  __asm__ volatile(

      " bkpt 0 "

      : /* Outputs */
      : /* Inputs */
      : /* Clobbers */
  );
#else
#error "Unsupported architecture."
#endif
  }

  static inline __attribute__ ((always_inline)) void
  cortexa_architecture_wfi (void)
  {
    __asm__ volatile(

        " wfi "

        : /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );
  }

  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_nop (void)
  {
    cortexa_architecture_nop ();
  }

  /**
   * `break` instruction.
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_brk (void)
  {
    cortexa_architecture_bkpt ();
  }

  /**
   * `wfi` instruction.
   */
  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_wfi (void)
  {
    cortexa_architecture_wfi ();
  }

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

namespace cortexa::architecture
{
  // --------------------------------------------------------------------------

  inline __attribute__ ((always_inline)) void
  nop (void)
  {
    cortexa_architecture_nop ();
  }

  inline __attribute__ ((always_inline)) void
  bkpt (void)
  {
    cortexa_architecture_bkpt ();
  }

  inline __attribute__ ((always_inline)) void
  wfi (void)
  {
    cortexa_architecture_wfi ();
  }

  // --------------------------------------------------------------------------
} // namespace cortexa::architecture

namespace micro_os_plus::architecture
{
  // --------------------------------------------------------------------------

  inline __attribute__ ((always_inline)) void
  nop (void)
  {
    cortexa::architecture::nop ();
  }

  inline __attribute__ ((always_inline)) void
  brk (void)
  {
    cortexa::architecture::bkpt ();
  }

  inline __attribute__ ((always_inline)) void
  wfi (void)
  {
    cortexa::architecture::wfi ();
  }

  // --------------------------------------------------------------------------
} // namespace micro_os_plus::architecture

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_CORTEXA_INSTRUCTIONS_INLINES_H_

// ----------------------------------------------------------------------------
