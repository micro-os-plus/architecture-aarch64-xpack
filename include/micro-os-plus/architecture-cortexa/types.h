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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_CORTEXA_TYPES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_CORTEXA_TYPES_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

#if defined(__ARM_ARCH_8A)
  typedef uint64_t cortexa_architecture_register_t;
  typedef uint64_t micro_os_plus_architecture_register_t;
#else
typedef uint32_t cortexa_architecture_register_t;
typedef uint32_t micro_os_plus_architecture_register_t;
#endif

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

// ----------------------------------------------------------------------------

namespace cortexa::architecture
{
  // --------------------------------------------------------------------------

  using register_t = cortexa_architecture_register_t;

  // --------------------------------------------------------------------------
} // namespace cortexa::architecture

namespace micro_os_plus::architecture
{
  // --------------------------------------------------------------------------

  using register_t = cortexa_architecture_register_t;

  // --------------------------------------------------------------------------
} // namespace micro_os_plus::architecture

// ----------------------------------------------------------------------------

#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_CORTEXA_TYPES_H_

// ----------------------------------------------------------------------------
