/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2021-2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can be
 * obtained from https://opensource.org/licenses/mit.
 */

/**
 * @file
 * @brief AArch64 architecture preprocessor definitions.
 *
 * @details
 * The definitions in this file are also used from assembly sources,
 * therefore it must contain only preprocessor directives.
 */

#ifndef MICRO_OS_PLUS_ARCHITECTURE_AARCH64_DEFINES_H_
#define MICRO_OS_PLUS_ARCHITECTURE_AARCH64_DEFINES_H_

// ----------------------------------------------------------------------------

// Not defined for AArch64, therefore the RTOS does not provide a separate
// interrupts stack object.
// #define MICRO_OS_PLUS_HAS_INTERRUPTS_STACK

/**
 * @brief Value used to fill the stack at startup.
 *
 * @details
 * The device and RTOS port packages fill stacks with this 32-bit value,
 * so that the unused part can later be identified, and the maximum stack
 * usage computed. On little-endian cores it is stored in memory as the
 * bytes `DE AD BE EF`, which are easy to recognise in a memory dump.
 */
#define MICRO_OS_PLUS_INTEGER_STARTUP_STACK_FILL_MAGIC (0xEFBEADDE)

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_AARCH64_DEFINES_H_

// ----------------------------------------------------------------------------
