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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_CORTEXA_REGISTERS_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_CORTEXA_REGISTERS_INLINES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------
// Inline implementations for the Cortex-A architecture instructions.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

  static inline __attribute__ ((always_inline)) cortexa_architecture_register_t
  cortexa_architecture_get_msp (void)
  {
    uint32_t result;

    __asm__ volatile(

        "msr %0, msp"

        : "=r"(result) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );

    return result;
  }

  static inline __attribute__ ((always_inline))
  micro_os_plus_architecture_register_t
  micro_os_plus_architecture_get_sp (void)
  {
    return cortexa_architecture_get_msp ();
  }

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

namespace cortexa::architecture::registers
{
  // --------------------------------------------------------------------------

  inline __attribute__ ((always_inline)) register_t
  msp (void)
  {
    return cortexa_architecture_get_msp ();
  }

  // --------------------------------------------------------------------------
} // namespace cortexa::architecture::registers

namespace micro_os_plus::architecture::registers
{
  // --------------------------------------------------------------------------

  inline __attribute__ ((always_inline)) register_t
  sp (void)
  {
    return micro_os_plus_architecture_get_sp ();
  }

  // --------------------------------------------------------------------------
} // namespace micro_os_plus::architecture::registers

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_CORTEXA_REGISTERS_INLINES_H_

// ----------------------------------------------------------------------------
