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

#ifndef MICRO_OS_PLUS_ARCHITECTURE_AARCH64_INSTRUCTIONS_H_
#define MICRO_OS_PLUS_ARCHITECTURE_AARCH64_INSTRUCTIONS_H_

// ----------------------------------------------------------------------------

#include "micro-os-plus/architecture-aarch64/defines.h"

#include <stdint.h>

// ----------------------------------------------------------------------------
// Declarations of AArch64 functions to wrap architecture instructions.

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

  // --------------------------------------------------------------------------
  // Architecture assembly instructions in C.

  /**
   * `nop` instruction.
   */
  static void
  aarch64_architecture_nop (void);

  /**
   * @brief Software breakpoint.
   *
   * @details
   * Issues the `brk #0` instruction, the encoding used by GDB for
   * AArch64 software breakpoints.
   */
  static void
  aarch64_architecture_brk (void);

  /**
   * @brief Software breakpoint (deprecated name).
   *
   * @details
   * Kept for compatibility with earlier releases; `bkpt` is the
   * AArch32/Cortex-M mnemonic. Use `aarch64_architecture_brk()`.
   */
  __attribute__ ((deprecated ("use aarch64_architecture_brk()"))) static void
  aarch64_architecture_bkpt (void);

  /**
   * `wfi` instruction.
   */
  static void
  aarch64_architecture_wfi (void);

  /**
   * `dsb sy` instruction (Data Synchronization Barrier, full system).
   */
  static void
  aarch64_architecture_dsb (void);

  /**
   * `isb` instruction (Instruction Synchronization Barrier).
   */
  static void
  aarch64_architecture_isb (void);

  // --------------------------------------------------------------------------
  // Portable architecture assembly instructions in C.

  /**
   * `nop` instruction.
   */
  static void
  micro_os_plus_architecture_nop (void);

  /**
   * @brief Software breakpoint.
   *
   * @details
   * The portable name, shared with the other µOS++ architectures;
   * on AArch64 it issues the `brk #0` instruction.
   */
  static void
  micro_os_plus_architecture_brk (void);

  /**
   * `wfi` instruction.
   */
  static void
  micro_os_plus_architecture_wfi (void);

  /**
   * @brief Data synchronisation barrier.
   *
   * @details
   * Ensures that all explicit memory accesses, and all system register
   * writes, issued before this call complete before any instruction
   * after it executes. It also acts as a compiler memory barrier.
   *
   * On AArch64, it is implemented with the `dsb sy` instruction.
   */
  static void
  micro_os_plus_architecture_data_barrier (void);

  /**
   * @brief Instruction synchronisation barrier.
   *
   * @details
   * Ensures that the instructions after this call are fetched and
   * executed only after the effects of the preceding context-changing
   * operations (such as system register writes, or code written to
   * memory) are visible. Usually called right after
   * `micro_os_plus_architecture_data_barrier()`.
   *
   * On AArch64, it is implemented with the `isb` instruction.
   */
  static void
  micro_os_plus_architecture_instruction_barrier (void);

  // --------------------------------------------------------------------------

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

// ============================================================================

#if defined(__cplusplus)

namespace aarch64::architecture
{
  // --------------------------------------------------------------------------
  // Architecture assembly instructions in C++.

  /**
   * The assembler `nop` instruction.
   */
  void
  nop (void);

  /**
   * @brief Software breakpoint.
   *
   * @details
   * The C++ equivalent of `aarch64_architecture_brk()`; issues the
   * `brk #0` instruction.
   */
  void
  brk (void);

  /**
   * @brief Software breakpoint (deprecated name).
   *
   * @details
   * Kept for compatibility with earlier releases; `bkpt` is the
   * AArch32/Cortex-M mnemonic. Use `brk()`.
   */
  [[deprecated ("use brk()")]] void
  bkpt (void);

  /**
   * The assembler `wfi` instruction.
   */
  void
  wfi (void);

  /**
   * The assembler `dsb sy` (Data Synchronization Barrier) instruction.
   */
  void
  dsb (void);

  /**
   * The assembler `isb` (Instruction Synchronization Barrier) instruction.
   */
  void
  isb (void);

  // --------------------------------------------------------------------------
} // namespace aarch64::architecture

namespace micro_os_plus::architecture
{
  // --------------------------------------------------------------------------
  // Portable architecture assembly instructions in C++.

  /**
   * The assembler `nop` instruction.
   */
  void
  nop (void);

  /**
   * @brief Software breakpoint.
   *
   * @details
   * The C++ equivalent of `micro_os_plus_architecture_brk()`; on
   * AArch64 it issues the `brk #0` instruction.
   */
  void
  brk (void);

  /**
   * The assembler `wfi` instruction.
   */
  void
  wfi (void);

  /**
   * @brief Data synchronisation barrier.
   *
   * @details
   * The C++ equivalent of `micro_os_plus_architecture_data_barrier()`;
   * on AArch64, it is implemented with the `dsb sy` instruction.
   */
  void
  data_barrier (void);

  /**
   * @brief Instruction synchronisation barrier.
   *
   * @details
   * The C++ equivalent of
   * `micro_os_plus_architecture_instruction_barrier()`; on AArch64,
   * it is implemented with the `isb` instruction.
   */
  void
  instruction_barrier (void);

  // --------------------------------------------------------------------------
} // namespace micro_os_plus::architecture

#endif // defined(__cplusplus)

// ============================================================================
// Templates, inlines & constexpr implementations.

#include "inlines/instructions-inlines.h"

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_AARCH64_INSTRUCTIONS_H_

// ----------------------------------------------------------------------------
