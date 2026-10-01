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
 * @brief Declarations of the AArch64 functions wrapping CPU instructions.
 *
 * @details
 * Each instruction is available in four forms: architecture specific C
 * functions (`aarch64_architecture_*()`), portable C functions
 * (`micro_os_plus_architecture_*()`), and the corresponding C++ functions
 * in the `aarch64::architecture` and `micro_os_plus::architecture`
 * namespaces. The portable forms are common to all µOS++ architectures.
 *
 * All functions are always inlined; their definitions are in
 * `inlines/instructions-inlines.h`, included at the end of this file.
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
   * @brief Execute a `nop` instruction.
   *
   * @details
   * The instruction performs no operation. The architecture does not
   * guarantee that it takes any time to execute, since it may be removed
   * from the pipeline, therefore it must not be used for timing delays.
   *
   * It is not a compiler barrier.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  aarch64_architecture_nop (void);

  /**
   * @brief Execute a `brk #0` instruction.
   *
   * @details
   * The instruction generates a synchronous Breakpoint Instruction
   * exception. `brk #0` is the encoding used by GDB for AArch64 software
   * breakpoints. If no debugger handles the exception, it is taken by the
   * application exception handler, which must be prepared for it.
   *
   * It also acts as a compiler memory barrier, so that a debugger
   * stopped at the breakpoint sees all the preceding stores in memory.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  aarch64_architecture_brk (void);

  /**
   * @brief Execute a `brk #0` instruction (deprecated name).
   *
   * @details
   * Kept for compatibility with earlier releases; `bkpt` is the
   * AArch32/Cortex-M mnemonic. Use `aarch64_architecture_brk()`.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE
  __attribute__ ((deprecated ("use aarch64_architecture_brk()"))) void
  aarch64_architecture_bkpt (void);

  /**
   * @brief Execute a `wfi` instruction.
   *
   * @details
   * The instruction suspends execution, possibly entering a low power
   * state, until a wake-up event, such as an interrupt or a debug event,
   * occurs. Depending on the system configuration, it may also be
   * trapped to a higher exception level (for example, at EL0 when
   * `SCTLR_EL1.nTWI` is 0).
   *
   * It also acts as a compiler memory barrier, so that variables changed
   * by interrupt handlers are read again after it returns. It is not a
   * hardware barrier; if outstanding memory writes must complete before
   * entering the low power state, call `aarch64_architecture_dsb()`
   * first.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  aarch64_architecture_wfi (void);

  /**
   * @brief Execute a `dsb sy` instruction.
   *
   * @details
   * Data Synchronisation Barrier, full system: no instruction after it
   * executes until all the explicit memory accesses, cache maintenance
   * operations, and TLB maintenance operations issued before it complete.
   *
   * It also acts as a compiler memory barrier.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  aarch64_architecture_dsb (void);

  /**
   * @brief Execute an `isb` instruction.
   *
   * @details
   * Instruction Synchronisation Barrier: flushes the pipeline, so that
   * the instructions after it are fetched again, and observe the effects
   * of the preceding context-changing operations, such as system register
   * writes. On AArch64 the only option is `sy`, which is the default.
   *
   * It also acts as a compiler memory barrier.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  aarch64_architecture_isb (void);

  // --------------------------------------------------------------------------
  // Portable architecture assembly instructions in C.

  /**
   * @brief Perform no operation.
   *
   * @details
   * Portable wrapper, available on all µOS++ architectures. On AArch64,
   * it is implemented with the `nop` instruction, which is not guaranteed
   * to take any time, therefore it must not be used for timing delays.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  micro_os_plus_architecture_nop (void);

  /**
   * @brief Enter the debugger.
   *
   * @details
   * Portable wrapper, available on all µOS++ architectures. On AArch64,
   * it is implemented with the `brk #0` instruction, which generates a
   * Breakpoint Instruction exception; if no debugger handles it, it is
   * taken by the application exception handler.
   *
   * It also acts as a compiler memory barrier.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  micro_os_plus_architecture_brk (void);

  /**
   * @brief Wait for an interrupt.
   *
   * @details
   * Portable wrapper, available on all µOS++ architectures. On AArch64,
   * it is implemented with the `wfi` instruction, which suspends
   * execution until a wake-up event, such as an interrupt, occurs.
   *
   * It also acts as a compiler memory barrier, but not as a hardware
   * barrier; if outstanding memory writes must complete before entering
   * the low power state, call `micro_os_plus_architecture_data_barrier()`
   * first.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
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
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
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
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
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
   * @brief Execute a `nop` instruction.
   *
   * @details
   * C++ equivalent of `aarch64_architecture_nop()`; the instruction is
   * not guaranteed to take any time, therefore it must not be used for
   * timing delays.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  nop (void) noexcept;

  /**
   * @brief Execute a `brk #0` instruction.
   *
   * @details
   * C++ equivalent of `aarch64_architecture_brk()`; it generates a
   * Breakpoint Instruction exception, handled by the debugger or, if
   * none, by the application exception handler. It also acts as a
   * compiler memory barrier.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  brk (void) noexcept;

  /**
   * @brief Execute a `brk #0` instruction (deprecated name).
   *
   * @details
   * Kept for compatibility with earlier releases; `bkpt` is the
   * AArch32/Cortex-M mnemonic. Use `brk()`.
   */
  [[deprecated ("use brk()")]] MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  bkpt (void) noexcept;

  /**
   * @brief Execute a `wfi` instruction.
   *
   * @details
   * C++ equivalent of `aarch64_architecture_wfi()`; it suspends
   * execution until a wake-up event, such as an interrupt, occurs, and
   * acts as a compiler memory barrier, but not as a hardware barrier.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  wfi (void) noexcept;

  /**
   * @brief Execute a `dsb sy` instruction.
   *
   * @details
   * C++ equivalent of `aarch64_architecture_dsb()` (Data
   * Synchronisation Barrier, full system); it also acts as a compiler
   * memory barrier.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  dsb (void) noexcept;

  /**
   * @brief Execute an `isb` instruction.
   *
   * @details
   * C++ equivalent of `aarch64_architecture_isb()` (Instruction
   * Synchronisation Barrier); it also acts as a compiler memory barrier.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  isb (void) noexcept;

  // --------------------------------------------------------------------------
} // namespace aarch64::architecture

namespace micro_os_plus::architecture
{
  // --------------------------------------------------------------------------
  // Portable architecture assembly instructions in C++.

  /**
   * @brief Perform no operation.
   *
   * @details
   * C++ equivalent of `micro_os_plus_architecture_nop()`, available on
   * all µOS++ architectures; on AArch64, it executes a `nop` instruction.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  nop (void) noexcept;

  /**
   * @brief Enter the debugger.
   *
   * @details
   * C++ equivalent of `micro_os_plus_architecture_brk()`, available on
   * all µOS++ architectures; on AArch64, it executes a `brk #0`
   * instruction.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  brk (void) noexcept;

  /**
   * @brief Wait for an interrupt.
   *
   * @details
   * C++ equivalent of `micro_os_plus_architecture_wfi()`, available on
   * all µOS++ architectures; on AArch64, it executes a `wfi` instruction.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  wfi (void) noexcept;

  /**
   * @brief Data synchronisation barrier.
   *
   * @details
   * The C++ equivalent of `micro_os_plus_architecture_data_barrier()`;
   * on AArch64, it is implemented with the `dsb sy` instruction.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  data_barrier (void) noexcept;

  /**
   * @brief Instruction synchronisation barrier.
   *
   * @details
   * The C++ equivalent of
   * `micro_os_plus_architecture_instruction_barrier()`; on AArch64,
   * it is implemented with the `isb` instruction.
   */
  MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE void
  instruction_barrier (void) noexcept;

  // --------------------------------------------------------------------------
} // namespace micro_os_plus::architecture

#endif // defined(__cplusplus)

// ============================================================================
// Templates, inlines & constexpr implementations.

#include "inlines/instructions-inlines.h"

// ----------------------------------------------------------------------------

#endif // MICRO_OS_PLUS_ARCHITECTURE_AARCH64_INSTRUCTIONS_H_

// ----------------------------------------------------------------------------
