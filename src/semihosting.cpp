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

#include "micro-os-plus/semihosting.h"

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_SEMIHOSTING_ENABLED)

// ----------------------------------------------------------------------------

// SWI numbers and reason codes for RDI (Angel) monitors.
#define AngelSVC 0xF000
#define AngelSVCInsn "hlt"

micro_os_plus_semihosting_response_t
micro_os_plus_semihosting_call_host (
    int reason, micro_os_plus_semihosting_param_block_t* arg)
{
  micro_os_plus_semihosting_response_t value;
  __asm__ volatile (

      " mov w0, %w[rsn] \n"
      " mov x1, %[arg] \n"
      " " AngelSVCInsn " %[svc] \n"
      " mov %[val], x0 \n"

      : [val] "=r"(value) /* Outputs */
      : [rsn] "r"(reason), [arg] "r"(arg), [svc] "n"(AngelSVC) /* Inputs */
      : "x0", "x1", "x2", "x3", "x17", "x30", "memory", "cc"
      /* Clobbers x0 and x1, and lr if in supervisor mode */
  );

  // Accordingly to page 13-77 of ARM DUI 0040D other registers
  // can also be clobbered. Some memory positions may also be
  // changed by a system call, so they should not be kept in
  // registers. Note: we are assuming the manual is right and
  // Angel is respecting the APCS.
  return value;
}

// ----------------------------------------------------------------------------

#endif // defined(MICRO_OS_PLUS_SEMIHOSTING_ENABLED)

// ----------------------------------------------------------------------------
