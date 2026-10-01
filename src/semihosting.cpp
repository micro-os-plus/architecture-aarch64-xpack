/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2023-2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can be
 * obtained from https://opensource.org/licenses/mit.
 */

// ----------------------------------------------------------------------------

/**
 * @file
 * @brief AArch64 implementation of the semihosting call.
 *
 * @details
 * Implements `micro_os_plus_semihosting_call_host()`, declared in the
 * `semihosting` package, using the `hlt` instruction, as defined by the
 * Arm semihosting specification for AArch64:
 * https://github.com/ARM-software/abi-aa/blob/main/semihosting/semihosting.rst
 *
 * Nothing is compiled unless the architecture is enabled, the
 * `semihosting` package is available, and semihosting is enabled.
 */

#include "micro-os-plus/architecture.h"

#if defined(MICRO_OS_PLUS_ARCHITECTURES_AARCH64_ENABLED)

// The whole implementation depends on this header: it must be included
// before testing MICRO_OS_PLUS_SEMIHOSTING_ENABLED, which may be defined
// in `micro-os-plus/semihosting-defines.h`, and its declaration gives the
// definition below C linkage.
#if __has_include("micro-os-plus/semihosting.h")
#include "micro-os-plus/semihosting.h"

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_SEMIHOSTING_ENABLED)

// ----------------------------------------------------------------------------

namespace
{
  /**
   * @brief Semihosting trap number, used as the `hlt` immediate.
   *
   * @details
   * `0xF000`, as defined by the Arm semihosting specification for
   * AArch64. Unlike AArch32, there is a single value, since AArch64
   * has a single instruction set state.
   */
  constexpr micro_os_plus_architecture_register_t semihosting_hlt_number
      = 0xF000;
} // namespace

/**
 * @details
 * Traps to the debugger, which performs the operation identified by
 * `reason`, using the parameters in the block pointed to by `arg`, and
 * returns its result.
 *
 * The call is synchronous. If the debugger or emulator (such as QEMU)
 * does not intercept the `hlt` instruction, and halting debug is not
 * enabled, the instruction is treated as undefined and raises a
 * synchronous exception, which the application normally does not
 * expect; therefore semihosting must be enabled only when running
 * under a debugger or an emulator with semihosting support.
 *
 * @param reason The semihosting operation number, passed in `w0`.
 * @param arg Pointer to the parameter block (or, for some operations, a
 * single value), passed in `x1`.
 * @return The operation result, returned in `x0`; its meaning depends on
 * the operation, and many operations return -1 on error.
 */
micro_os_plus_semihosting_response_t
micro_os_plus_semihosting_call_host (
    int reason, micro_os_plus_semihosting_param_block_t* arg)
{
  // The semihosting ABI passes the reason in w0 and the parameter block
  // address in x1, and returns the result in x0. Binding the operands
  // directly to these registers (GNU explicit register variables, still
  // valid in C++17 and later) avoids the extra moves the compiler would
  // otherwise generate. x1 is also declared as an in/out operand, so
  // that the compiler conservatively does not assume it is preserved.
  register micro_os_plus_semihosting_response_t value __asm__ ("x0") = reason;
  register micro_os_plus_semihosting_param_block_t* param __asm__ ("x1") = arg;

  __asm__ volatile (

      " hlt %[hlt] \n"

      : [val] "+r"(value), [arg] "+r"(param) /* Outputs */
      : [hlt] "i"(semihosting_hlt_number) /* Inputs */
      : "x2", "x3", "x17", "x30", "memory", "cc" /* Clobbers */
  );

  // The specification states that all registers other than x0 are
  // preserved, so the clobbers beyond x0 and x1 are defensive only.
  // The `memory` clobber is required, since the host may read or write
  // any buffer referred to by the parameter block.
  return value;
}

// ----------------------------------------------------------------------------

#endif // defined(MICRO_OS_PLUS_SEMIHOSTING_ENABLED)

// ----------------------------------------------------------------------------

#endif // __has_include("micro-os-plus/semihosting.h")

// ----------------------------------------------------------------------------

#endif // defined(MICRO_OS_PLUS_ARCHITECTURES_AARCH64_ENABLED)

// ----------------------------------------------------------------------------
