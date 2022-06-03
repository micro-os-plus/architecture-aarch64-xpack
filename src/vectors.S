/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus/)
 * Copyright (c) 2022 Liviu Ionescu.
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can
 * be obtained from https://opensource.org/licenses/MIT/.
 */

#define __ASSEMBLY__ 1
#include "micro-os-plus/architecture-cortexa/exception-handlers.h"

// ----------------------------------------------------------------------------

#if defined(__ARM_ARCH_8A)

// ----------------------------------------------------------------------------

// The ARMv8-A interrupt/exception vectors.
//
// There are 4 modes, each with 4 interrupts (sync, irq, fiq, serror).
// Each has a branch that goes to an assembly routine which creates
// the exception frame and calls a common C handler.

  // "x" makes it visible in the listing.
  .section .interrupt_vectors,"awx",%progbits

  .balign 0x800 // Vector tables must be placed at a 2KB-aligned address
  .globl _interrupt_vectors
  .type _interrupt_vectors, %function
_interrupt_vectors:

  // Current EL with SP0
  .balign 0x80 // Each entry is 32w/128B in size
  b    _current_el_sp0_sync // Synchronous
  .balign 0x80
  b    _current_el_sp0_irq  // IRQ/vIRQ
  .balign 0x80
  b    _current_el_sp0_fiq // FIQ/vFIQ
  .balign 0x80
  b    _current_el_sp0_serror // SError/vSError

  // Current EL with SPx.
  .balign 0x80 // Each entry is 32w/128B in size
  b    _current_el_spx_sync // Synchronous
  .balign 0x80
  b    _current_el_spx_irq // IRQ/vIRQ
  .balign 0x80
  b    _current_el_spx_fiq // FIQ/vFIQ
  .balign 0x80
  b    _current_el_spx_serror // SError/vSError

  // Lower EL using AArch64.
  .balign 0x80 // Each entry is 32w/128B in size
  b    _lower_el_aarch64_sync
  .balign 0x80
  b    _lower_el_aarch64_irq
  .balign 0x80
  b    _lower_el_aarch64_fiq
  .balign 0x80
  b    _lower_el_aarch64_serror

  // Lower EL using AArch32
  .balign 0x80 // Each entry is 32w/128B in size
  b    _lower_el_aarch32_sync
  .balign 0x80
  b    _lower_el_aarch32_irq
  .balign 0x80
  b    _lower_el_aarch32_fiq
  .balign 0x80
  b    _lower_el_aarch32_serror

// ----------------------------------------------------------------------------
// Copyright (c) 2014 Takeharu KATO.
// https://github.com/takeharukato/sample-tsk-sw/blob/master/hal/aarch64/vector.S

.macro save_registers exc_type
  // Save generic registers from (x29,x30) pair to (x1,x2) pair.
  stp    x29, x30, [sp, #-16]!
  stp    x27, x28, [sp, #-16]!
  stp    x25, x26, [sp, #-16]!
  stp    x23, x24, [sp, #-16]!
  stp    x21, x22, [sp, #-16]!
  stp    x19, x20, [sp, #-16]!
  stp    x17, x18, [sp, #-16]!
  stp    x15, x16, [sp, #-16]!
  stp    x13, x14, [sp, #-16]!
  stp    x11, x12, [sp, #-16]!
  stp    x9, x10, [sp, #-16]!
  stp    x7, x8, [sp, #-16]!
  stp    x5, x6, [sp, #-16]!
  stp    x3, x4, [sp, #-16]!
  stp    x1, x2, [sp, #-16]!
  // Save (spsr, x0).
  mrs    x21, spsr_el1
  stp    x21, x0, [sp, #-16]!
  // Allocate a room for sp_el0 and store elr.
  mrs    x21, elr_el1
  stp    xzr, x21, [sp, #-16]!
  // Save exception type and esr.
  mov    x21, #(\exc_type)
  mrs    x22, esr_el1
  stp    x21, x22, [sp, #-16]!
.endm

.macro save_trapped_sp
  mrs    x21, sp_el0
  str    x21, [sp, #EXC_EXC_SP_OFFSET]
.endm

.macro call_common_trap_handler
  mov    x0, sp
  bl     common_trap_handler
.endm

.macro save_nested_sp
  mov    x21, sp
  add    x21, x21, #EXC_FRAME_SIZE
  str    x21, [sp, #EXC_EXC_SP_OFFSET]
.endm

.macro restore_trapped_sp
  ldr    x21, [sp, #EXC_EXC_SP_OFFSET]
  msr    sp_el0, x21
.endm

.macro restore_registers
  // Drop exception type, esr,
  add    sp, sp, #16
  // Drop exception stack pointer and restore elr_el1.
  ldp    x21, x22, [sp], #16
  msr    elr_el1, x22

  // Restore spsr and x0.
  ldp    x21, x0, [sp], #16
  msr    spsr_el1, x21

  // Restore generic registers from (x29,x30) pair to (x1,x2) pair.
  ldp    x1, x2, [sp], #16
  ldp    x3, x4, [sp], #16
  ldp    x5, x6, [sp], #16
  ldp    x7, x8, [sp], #16
  ldp    x9, x10, [sp], #16
  ldp    x11, x12, [sp], #16
  ldp    x13, x14, [sp], #16
  ldp    x15, x16, [sp], #16
  ldp    x17, x18, [sp], #16
  ldp    x19, x20, [sp], #16
  ldp    x21, x22, [sp], #16
  ldp    x23, x24, [sp], #16
  ldp    x25, x26, [sp], #16
  ldp    x27, x28, [sp], #16
  ldp    x29, x30, [sp], #16
.endm

// ----------------------------------------------------------------------------

  .section .after_vectors,"awx",%progbits

  .balign 4
  .type _current_el_sp0_sync, %function
_current_el_sp0_sync:
  save_registers AARCH64_EXC_SYNC_SP0
  save_trapped_sp
  call_common_trap_handler
  restore_trapped_sp
  restore_registers
  eret

  .balign 4
  .type _current_el_sp0_irq, %function
_current_el_sp0_irq:
  save_registers AARCH64_EXC_IRQ_SP0
  save_trapped_sp
  call_common_trap_handler
  restore_trapped_sp
  restore_registers
  eret

  .balign 4
  .type _current_el_sp0_fiq, %function
_current_el_sp0_fiq:
  save_registers AARCH64_EXC_FIQ_SP0
  save_trapped_sp
  call_common_trap_handler
  restore_trapped_sp
  restore_registers
  eret

  .balign 4
  .type _current_el_sp0_serror, %function
_current_el_sp0_serror:
  save_registers AARCH64_EXC_SERR_SP0
  save_trapped_sp
  call_common_trap_handler
  restore_trapped_sp
  restore_registers
  eret

// ----------------------------------------------------------------------------

  .balign 4
  .type _current_el_spx_sync, %function
_current_el_spx_sync:
  save_registers AARCH64_EXC_SYNC_SPX
  save_nested_sp
  call_common_trap_handler
  restore_registers
  eret

  .balign 4
  .type _current_el_spx_irq, %function
_current_el_spx_irq:
  save_registers AARCH64_EXC_IRQ_SPX
  save_nested_sp
  call_common_trap_handler
  restore_registers
  eret

  .balign 4
  .type _current_el_spx_fiq, %function
_current_el_spx_fiq:
  save_registers AARCH64_EXC_FIQ_SPX
  save_nested_sp
  call_common_trap_handler
  restore_registers
  eret

  .balign 4
  .type _current_el_spx_serror, %function
_current_el_spx_serror:
  save_registers AARCH64_EXC_SERR_SPX
  save_nested_sp
  call_common_trap_handler
  restore_registers
  eret

// ----------------------------------------------------------------------------

  .balign 4
  .type _lower_el_aarch64_sync, %function
_lower_el_aarch64_sync:
  save_registers AARCH64_EXC_SYNC_AARCH64
  save_trapped_sp
  call_common_trap_handler
  restore_trapped_sp
  restore_registers
  eret

  .balign 4
  .type _lower_el_aarch64_irq, %function
_lower_el_aarch64_irq:
  save_registers AARCH64_EXC_IRQ_AARCH64
  save_trapped_sp
  call_common_trap_handler
  restore_trapped_sp
  restore_registers
  eret

  .balign 4
  .type _lower_el_aarch64_fiq, %function
_lower_el_aarch64_fiq:
  save_registers AARCH64_EXC_FIQ_AARCH64
  save_trapped_sp
  call_common_trap_handler
  restore_trapped_sp
  restore_registers
  eret

  .balign 4
  .type _lower_el_aarch64_serror, %function
_lower_el_aarch64_serror:
  save_registers AARCH64_EXC_SERR_AARCH64
  save_trapped_sp
  call_common_trap_handler
  restore_trapped_sp
  restore_registers
  eret

// ----------------------------------------------------------------------------

  .balign 4
  .type _lower_el_aarch32_sync, %function
_lower_el_aarch32_sync:
  save_registers AARCH64_EXC_SYNC_AARCH32
  save_trapped_sp
  call_common_trap_handler
  restore_trapped_sp
  restore_registers
  eret

  .balign 4
  .type _lower_el_aarch32_irq, %function
_lower_el_aarch32_irq:
  save_registers AARCH64_EXC_IRQ_AARCH32
  save_trapped_sp
  call_common_trap_handler
  restore_trapped_sp
  restore_registers
  eret

  .balign 4
  .type _lower_el_aarch32_fiq, %function
_lower_el_aarch32_fiq:
  save_registers AARCH64_EXC_FIQ_AARCH32
  save_trapped_sp
  call_common_trap_handler
  restore_trapped_sp
  restore_registers
  eret

  .balign 4
  .type _lower_el_aarch32_serror, %function
_lower_el_aarch32_serror:
  save_registers AARCH64_EXC_SERR_AARCH32
  save_trapped_sp
  call_common_trap_handler
  restore_trapped_sp
  restore_registers
  eret

// ============================================================================

#elif defined(__ARM_ARCH_7A__)

  .globl _interrupt_vectors
  // "x" makes it visible in the listing.
  .section .interrupt_vectors,"awx",%progbits

    .align  7
_interrupt_vectors:

  .balign 4
  b     reset_handler
  b     undefined_handler
  b     swi_handler
  b     prefetch_handler
  b     data_handler
  nop   // Reserved vector
  b     irq_handler
  b     fiq_handler

// ----------------------------------------------------------------------------

  .section .after_vectors,"awx",%progbits

  .balign 4
undefined_handler:
	wfi
	b     undefined_handler

  .balign 4
swi_handler:
  wfi
  b     swi_handler

  .balign 4
prefetch_handler:
  wfi
  b     prefetch_handler

  .balign 4
data_handler:
  wfi
  b     data_handler

  .balign 4
irq_handler:
  SUB   lr, lr, #4
  SRSFD sp!, #0x1f
  CPS   #0x1f
  PUSH  {r0-r3, r12}
  AND   r1, sp, #4
  SUB   sp, sp, r1
  PUSH  {r1, lr}
  BL    identify_and_clear_source
  CPSIE i
  BL    c_irq_handler
  CPSID i
  POP   {r1, lr}
  ADD   sp, sp, r1
  POP   {r0-r3, r12}
  RFEFD sp!

identify_and_clear_source:
  bx    lr

  .balign 4
fiq_handler:
  wfi
  b     fiq_handler

// ----------------------------------------------------------------------------

#else
#error "Unsupported architecture."
#endif

