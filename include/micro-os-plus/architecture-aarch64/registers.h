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

/**
 * @file
 * @brief Declarations of the AArch64 functions accessing CPU registers.
 *
 * @details
 * As for the instructions, each register accessor is available as
 * architecture specific and portable C functions, and in the
 * `aarch64::architecture::registers` and
 * `micro_os_plus::architecture::registers` C++ namespaces.
 *
 * All functions are always inlined; their definitions are in
 * `inlines/registers-inlines.h`, included at the end of this file.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_AARCH64_REGISTERS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_AARCH64_REGISTERS_H_

// ----------------------------------------------------------------------------

#include "micro-os-plus/architecture-aarch64/defines.h"
#include "micro-os-plus/architecture-aarch64/types.h"

#include <stdint.h>

// ----------------------------------------------------------------------------
// Declarations of AArch64 functions to access architecture registers.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------
  // Architecture registers getters and mutators in C.

  /**
   * @brief Get the current stack pointer.
   *
   * @details
   * Returns the value of the stack pointer selected for the current
   * exception level (`SP_EL0` or `SP_ELx`, depending on `SPSel`),
   * as seen by the calling code. The value is read with
   * `mov <Xd>, sp`, since `sp` cannot be used directly as the source
   * of most other instructions.
   *
   * @return The 64-bit value of the current stack pointer.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE aarch64_architecture_register_t
  aarch64_architecture_get_sp (void);

  /**
   * @brief Set the current stack pointer.
   *
   * @details
   * Writes the stack pointer selected for the current exception level
   * (`SP_EL0` or `SP_ELx`, depending on `SPSel`) with
   * `mov sp, <Xn>`.
   *
   * This is intended for low-level code, such as the startup code or
   * a context switch. AArch64 has a single current stack pointer, and
   * the compiler addresses local variables and spilled registers
   * relative to it (often without a frame pointer). Changing it from
   * C/C++ is safe only when the calling function has no stack frame
   * that is still in use, or when it is immediately followed by a call
   * to a function that does not return.
   *
   * The value must be 16-byte aligned; with `SCTLR_ELx.SA` set, any
   * stack access through a misaligned stack pointer raises an
   * alignment fault.
   *
   * @param top_of_stack The new value of the stack pointer.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  aarch64_architecture_set_sp (aarch64_architecture_register_t top_of_stack);

  // --------------------------------------------------------------------------
  // Portable architecture registers getters and mutators in C.

  /**
   * @brief Get the current stack pointer.
   *
   * @details
   * The portable name, shared with the other µOS++ architectures;
   * on AArch64 it forwards to `aarch64_architecture_get_sp()`.
   *
   * @return The value of the current stack pointer.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE
  micro_os_plus_architecture_register_t
  micro_os_plus_architecture_get_sp (void);

  /**
   * @brief Set the current stack pointer.
   *
   * @details
   * The portable name, shared with the other µOS++ architectures;
   * on AArch64 it forwards to `aarch64_architecture_set_sp()`, and
   * the same restrictions apply.
   *
   * @param top_of_stack The new value of the stack pointer.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  micro_os_plus_architecture_set_sp (
      micro_os_plus_architecture_register_t top_of_stack);

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

namespace aarch64::architecture::registers
{
  // --------------------------------------------------------------------------
  // Architecture registers getters and mutators in C++.

  /**
   * @brief Get the current stack pointer.
   *
   * @details
   * The C++ equivalent of `aarch64_architecture_get_sp()`.
   *
   * @return The 64-bit value of the current stack pointer.
   */
  [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE register_t
  sp (void) noexcept;

  /**
   * @brief Set the current stack pointer.
   *
   * @details
   * The C++ equivalent of `aarch64_architecture_set_sp()`; the same
   * restrictions apply.
   *
   * @param top_of_stack The new value of the stack pointer.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  sp (register_t top_of_stack) noexcept;

  // --------------------------------------------------------------------------
} // namespace aarch64::architecture::registers

namespace micro_os_plus::architecture::registers
{
  // --------------------------------------------------------------------------
  // Portable architecture registers getters and mutators in C++.

  /**
   * @brief Get the current stack pointer.
   *
   * @details
   * The C++ equivalent of `micro_os_plus_architecture_get_sp()`.
   *
   * @return The value of the current stack pointer.
   */
  [[nodiscard]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE register_t
  sp (void) noexcept;

  /**
   * @brief Set the current stack pointer.
   *
   * @details
   * The C++ equivalent of `micro_os_plus_architecture_set_sp()`; the
   * same restrictions apply.
   *
   * @param top_of_stack The new value of the stack pointer.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  sp (register_t top_of_stack) noexcept;

  // --------------------------------------------------------------------------
} // namespace micro_os_plus::architecture::registers

#endif // defined(__cplusplus)

// ============================================================================
// Templates, inlines & constexpr implementations.

#include "inlines/registers-inlines.h"

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_AARCH64_REGISTERS_H_

// ----------------------------------------------------------------------------
