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
 * @brief AArch64 architecture type definitions.
 *
 * @details
 * Defines the register types, both with architecture specific names and
 * with the portable names common to all µOS++ architectures, in C and in
 * C++.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_AARCH64_TYPES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_AARCH64_TYPES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  /**
   * @brief Unsigned type of a general purpose register.
   *
   * @details
   * All AArch64 general purpose registers (`x0`-`x30`) and the stack
   * pointer are 64-bit wide.
   */
  typedef uint64_t aarch64_architecture_register_t;
  /**
   * @brief Signed type of a general purpose register.
   *
   * @details
   * Used for values returned in registers that may be negative, such as
   * semihosting results.
   */
  typedef int64_t aarch64_architecture_signed_register_t;

  /**
   * @brief Portable unsigned register type.
   *
   * @details
   * Common to all µOS++ architectures; on AArch64 it is an alias of
   * `aarch64_architecture_register_t`.
   */
  typedef aarch64_architecture_register_t
      micro_os_plus_architecture_register_t;

  /**
   * @brief Portable signed register type.
   *
   * @details
   * Common to all µOS++ architectures; on AArch64 it is an alias of
   * `aarch64_architecture_signed_register_t`.
   */
  typedef aarch64_architecture_signed_register_t
      micro_os_plus_architecture_signed_register_t;

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

// ----------------------------------------------------------------------------

namespace aarch64::architecture
{
  // --------------------------------------------------------------------------

  /**
   * @brief Unsigned register type, in the
   * `aarch64::architecture` namespace.
   *
   * @details
   * C++ alias of `aarch64_architecture_register_t`.
   */
  using register_t = aarch64_architecture_register_t;

  /**
   * @brief Signed register type, in the
   * `aarch64::architecture` namespace.
   *
   * @details
   * C++ alias of `aarch64_architecture_signed_register_t`.
   */
  using signed_register_t = aarch64_architecture_signed_register_t;

  // --------------------------------------------------------------------------
} // namespace aarch64::architecture

namespace micro_os_plus::architecture
{
  // --------------------------------------------------------------------------

  /**
   * @brief Unsigned register type, in the
   * `micro_os_plus::architecture` namespace.
   *
   * @details
   * C++ alias of `aarch64_architecture_register_t`.
   */
  using register_t = aarch64_architecture_register_t;

  /**
   * @brief Signed register type, in the
   * `micro_os_plus::architecture` namespace.
   *
   * @details
   * C++ alias of `aarch64_architecture_signed_register_t`.
   */
  using signed_register_t = aarch64_architecture_signed_register_t;

  // --------------------------------------------------------------------------
} // namespace micro_os_plus::architecture

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_AARCH64_TYPES_H_

// ----------------------------------------------------------------------------
