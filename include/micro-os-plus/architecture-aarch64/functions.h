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
 * @brief Declarations of the AArch64 architecture functions.
 *
 * @details
 * These functions are defined in the `src` folder; they are used
 * internally by other µOS++ packages.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_AARCH64_FUNCTIONS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_AARCH64_FUNCTIONS_H_

// ----------------------------------------------------------------------------

#include <stdint.h>

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  /**
   * @brief Display the CPU identification.
   *
   * @details
   * Internal µOS++ function, called by the startup code (`run-main.cpp`
   * in the `startup` package) before `main()`, when
   * `MICRO_OS_PLUS_DEBUG_ENABLED` or `MICRO_OS_PLUS_DIAG_TRACE_ENABLED`
   * is defined; it is not part of the application API, therefore it has
   * no C++ equivalent.
   *
   * On AArch64 it decodes the `MIDR_EL1` identification register and
   * writes a line like `Arm Cortex-A53 r0p4` to the trace output
   * channel. It must be called at EL1 or higher. When the `diag-trace`
   * package is not available, it is empty.
   */
  void
  micro_os_plus_architecture_show_cpuid (void);

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_AARCH64_FUNCTIONS_H_

// ----------------------------------------------------------------------------
