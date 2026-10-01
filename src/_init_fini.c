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
 * @brief Weak empty definitions of `_init()` and `_fini()`.
 *
 * @details
 * Newlib references `_fini()` from `__libc_fini_array()` (and, in some
 * configurations, `_init()` from `__libc_init_array()`); on bare-metal
 * targets there is no crt code to provide them, so these weak empty
 * definitions satisfy the linker. The application may override them
 * with strong definitions.
 */

#include "micro-os-plus/architecture.h"

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_ARCHITECTURES_AARCH64_ENABLED)

// ----------------------------------------------------------------------------

void
_init (void);

void
_fini (void);

// ----------------------------------------------------------------------------

// Newlib calls `_fini()` in `__libc_fini_array`; `_init()` was
// added for completeness.

// libg.a(libc_a-fini.o): in function `__libc_fini_array':
// (.text.__libc_fini_array+0x1c): undefined reference to `_fini'

/**
 * @brief Run legacy initialisation code.
 *
 * @details
 * Weak empty definition; nothing needs to run before the constructors
 * on this architecture.
 */
__attribute__ ((weak)) void
_init (void)
{
}

/**
 * @brief Run legacy termination code.
 *
 * @details
 * Weak empty definition, required to resolve the reference from
 * `__libc_fini_array()`.
 */
__attribute__ ((weak)) void
_fini (void)
{
}

// ----------------------------------------------------------------------------

#endif // defined(MICRO_OS_PLUS_ARCHITECTURES_AARCH64_ENABLED)

// ----------------------------------------------------------------------------
