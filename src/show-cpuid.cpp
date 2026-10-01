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
 * @brief AArch64 implementation of the CPU identification display.
 */

#include "micro-os-plus/architecture.h"

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_ARCHITECTURES_AARCH64_ENABLED)

// ----------------------------------------------------------------------------

/**
 * @details
 * Currently empty; reading `MIDR_EL1` requires EL1 or higher, and the
 * output depends on the trace infrastructure.
 */
void
micro_os_plus_architecture_show_cpuid (void)
{
}

// ----------------------------------------------------------------------------

#endif // defined(MICRO_OS_PLUS_ARCHITECTURES_AARCH64_ENABLED)

// ----------------------------------------------------------------------------
