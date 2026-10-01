/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2022-2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can be
 * obtained from https://opensource.org/licenses/mit.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_AARCH64_INLINES_REGISTERS_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_AARCH64_INLINES_REGISTERS_INLINES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------
// Inline implementations for the AArch64 architecture registers.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

  static inline __attribute__ ((always_inline)) aarch64_architecture_register_t
  aarch64_architecture_get_sp (void)
  {
    aarch64_architecture_register_t result;

    __asm__ volatile (

        " mov %0, sp "

        : "=r"(result) /* Outputs */
        : /* Inputs */
        : /* Clobbers */
    );

    return result;
  }

  static inline __attribute__ ((always_inline)) void
  aarch64_architecture_set_sp (aarch64_architecture_register_t top_of_stack)
  {
    __asm__ volatile (

        " mov sp, %0 "

        : /* Outputs */
        : "r"(top_of_stack) /* Inputs */
        : "memory" /* Clobbers */
    );
  }

  static inline
      __attribute__ ((always_inline)) micro_os_plus_architecture_register_t
      micro_os_plus_architecture_get_sp (void)
  {
    return aarch64_architecture_get_sp ();
  }

  static inline __attribute__ ((always_inline)) void
  micro_os_plus_architecture_set_sp (
      micro_os_plus_architecture_register_t top_of_stack)
  {
    aarch64_architecture_set_sp (top_of_stack);
  }

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

namespace aarch64::architecture::registers
{
  // --------------------------------------------------------------------------

  inline __attribute__ ((always_inline)) register_t
  sp (void)
  {
    return aarch64_architecture_get_sp ();
  }

  inline __attribute__ ((always_inline)) void
  sp (register_t top_of_stack)
  {
    aarch64_architecture_set_sp (top_of_stack);
  }

  // --------------------------------------------------------------------------
} // namespace aarch64::architecture::registers

namespace micro_os_plus::architecture::registers
{
  // --------------------------------------------------------------------------

  inline __attribute__ ((always_inline)) register_t
  sp (void)
  {
    return micro_os_plus_architecture_get_sp ();
  }

  inline __attribute__ ((always_inline)) void
  sp (register_t top_of_stack)
  {
    micro_os_plus_architecture_set_sp (top_of_stack);
  }

  // --------------------------------------------------------------------------
} // namespace micro_os_plus::architecture::registers

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_AARCH64_INLINES_REGISTERS_INLINES_H_

// ----------------------------------------------------------------------------
