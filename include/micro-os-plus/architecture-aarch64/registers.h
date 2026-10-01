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
  static aarch64_architecture_register_t
  aarch64_architecture_get_sp (void);

  // TODO: add setter.

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
  static micro_os_plus_architecture_register_t
  micro_os_plus_architecture_get_sp (void);

  // TODO: add setter.

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

namespace aarch64::architecture::registers
{
  // --------------------------------------------------------------------------
  // Architecture getters in C++.

  /**
   * @brief Get the current stack pointer.
   *
   * @details
   * The C++ equivalent of `aarch64_architecture_get_sp()`.
   *
   * @return The 64-bit value of the current stack pointer.
   */
  register_t
  sp (void);

  // TODO: add setter.

  // --------------------------------------------------------------------------
} // namespace aarch64::architecture::registers

namespace micro_os_plus::architecture::registers
{
  // --------------------------------------------------------------------------
  // Portable architecture getters in C++.

  /**
   * @brief Get the current stack pointer.
   *
   * @details
   * The C++ equivalent of `micro_os_plus_architecture_get_sp()`.
   *
   * @return The value of the current stack pointer.
   */
  register_t
  sp (void);

  // TODO: add setter.

  // --------------------------------------------------------------------------
} // namespace micro_os_plus::architecture::registers

#endif // defined(__cplusplus)

// ============================================================================
// Templates, inlines & constexpr implementations.

#include "inlines/registers-inlines.h"

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_AARCH64_REGISTERS_H_

// ----------------------------------------------------------------------------
