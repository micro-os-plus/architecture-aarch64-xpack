/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2017-2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/mit.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_AARCH64_TYPES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_AARCH64_TYPES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  typedef uint64_t aarch64_architecture_register_t;
  typedef int64_t aarch64_architecture_signed_register_t;

  typedef aarch64_architecture_register_t
      micro_os_plus_architecture_register_t;
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

  using register_t = aarch64_architecture_register_t;
  using signed_register_t = aarch64_architecture_signed_register_t;

  // --------------------------------------------------------------------------
} // namespace aarch64::architecture

namespace micro_os_plus::architecture
{
  // --------------------------------------------------------------------------

  using register_t = aarch64_architecture_register_t;
  using signed_register_t = aarch64_architecture_signed_register_t;

  // --------------------------------------------------------------------------
} // namespace micro_os_plus::architecture

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_AARCH64_TYPES_H_

// ----------------------------------------------------------------------------
