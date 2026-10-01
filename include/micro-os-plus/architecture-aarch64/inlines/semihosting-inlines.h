/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2020-2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can be
 * obtained from https://opensource.org/licenses/mit.
 */

/**
 * @file
 * @brief AArch64 type definitions used by the semihosting call.
 *
 * @details
 * The `semihosting` package uses these architecture specific types in
 * its declarations; the call itself,
 * `micro_os_plus_semihosting_call_host()`, is implemented in
 * `src/semihosting.cpp`.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_AARCH64_INLINES_SEMIHOSTING_INLINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_AARCH64_INLINES_SEMIHOSTING_INLINES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------
// AArch64 type definitions used by the semihosting call; the call itself
// is implemented in `src/semihosting.cpp`.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------

  /**
   * @brief Type of each field in the semihosting structures.
   *
   * @details
   * Semihosting structures, such as the heap information block, have
   * fields of the register size (64 bits on AArch64).
   */
  typedef micro_os_plus_architecture_register_t
      micro_os_plus_semihosting_register_t;

  /**
   * @brief Type of each entry in a semihosting parameter block.
   *
   * @details
   * The parameter block, passed by address in `x1`, is an array of
   * 64-bit fields, as defined by the Arm semihosting specification.
   */
  typedef micro_os_plus_architecture_register_t
      micro_os_plus_semihosting_param_block_t;

  /**
   * @brief Type of the semihosting call result.
   *
   * @details
   * The result is returned in `x0`; it is signed, since many operations
   * return -1 on error.
   */
  typedef micro_os_plus_architecture_signed_register_t
      micro_os_plus_semihosting_response_t;

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_AARCH64_INLINES_SEMIHOSTING_INLINES_H_

// ----------------------------------------------------------------------------
