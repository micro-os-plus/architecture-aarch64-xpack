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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_AARCH64_ARCHITECTURE_H_
#define MICRO_OS_PLUS_ARCHITECTURE_AARCH64_ARCHITECTURE_H_

// ----------------------------------------------------------------------------

#if defined(__cplusplus)
#if !(__cplusplus >= 202002L || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L))
#error "C++20 or higher is required"
#endif
#endif // defined(__cplusplus)

#if __has_include("micro-os-plus/project-config.h")
#include "micro-os-plus/project-config.h"
#endif // __has_include("micro-os-plus/project-config.h")

#if __has_include("micro-os-plus/architecture-defines.h")
#include "micro-os-plus/architecture-defines.h"
#endif // __has_include("micro-os-plus/architecture-defines.h")

// ----------------------------------------------------------------------------

// No guard is needed; there can be only one architecture in a build.
// #if defined(MICRO_OS_PLUS_INCLUDE_ARCHITECTURES_AARCH64_ENABLED)

// ----------------------------------------------------------------------------

#include "micro-os-plus/architecture-aarch64/defines.h"
#include "micro-os-plus/architecture-aarch64/types.h"
#include "micro-os-plus/architecture-aarch64/instructions.h"
#include "micro-os-plus/architecture-aarch64/registers.h"

#include "micro-os-plus/architecture-aarch64/inlines/semihosting-inlines.h"

// ----------------------------------------------------------------------------

// #endif // defined(MICRO_OS_PLUS_INCLUDE_ARCHITECTURES_AARCH64_ENABLED)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_AARCH64_ARCHITECTURE_H_

// ----------------------------------------------------------------------------
