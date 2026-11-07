# Code Review — Architecture: AArch64

Scope: `include/`, `src/` (the `tests/` folder is a placeholder), reviewed
against `.github/skills/code-review/SKILL.md`, on the `xpack-development`
working tree including uncommitted changes (2026-09-30).

Verification: all sources and the public header compiled with
`aarch64-none-elf-gcc` 15.2 (`-std=c++20` / `-std=c11`, `-Wall -Wextra
-Wpedantic -Wconversion -Wshadow`, with
`MICRO_OS_PLUS_ARCHITECTURE_AARCH64_ENABLED` and
`MICRO_OS_PLUS_SEMIHOSTING_ENABLED`), and `architecture.h` also as
assembler with `__ASSEMBLY__`. No warnings. Nothing was executed; there
are no tests.

## Summary

The package is small, and after the recent fixes it compiles cleanly, but:

- the stack pointer **setter is missing** in all four API forms, which
  breaks symmetry with the Cortex-M package and leaves portable code
  unable to call `micro_os_plus_architecture_set_sp()` on AArch64 (#1);
- `src/semihosting.cpp` can silently produce a **C++-mangled**
  `micro_os_plus_semihosting_call_host` (verified with `nm`), which
  would fail at link time for C callers (#2);
- `wfi` lacks a `memory` clobber (#3);
- Doxygen coverage is incomplete and partly inconsistent (#6–#9);
- the semihosting code carries AArch32/Angel leftovers (#4, #5).

## Findings

### Correctness and maintainability

**1. Stack pointer setter missing (all forms).** — **Closed (2026-10-01):**
the setters were added in all four forms, as recommended below, with a
`"memory"` clobber and the documented restrictions. The optional `sp_el0`
accessors were not added.
[registers.h:48](include/micro-os-plus/architecture-aarch64/registers.h#L48),
[:65](include/micro-os-plus/architecture-aarch64/registers.h#L65),
[:93](include/micro-os-plus/architecture-aarch64/registers.h#L93),
[:114](include/micro-os-plus/architecture-aarch64/registers.h#L114)
only have `// TODO: add setter.`. The Cortex-M package provides
`micro_os_plus_architecture_set_sp(top_of_stack)` in C and a
`sp(register_t)` overload in C++; portable code using them does not
compile for AArch64.

Recommended design, mirroring Cortex-M:

- C: `aarch64_architecture_set_sp(aarch64_architecture_register_t
  top_of_stack)` implemented as `mov sp, %0` with an `"r"` input and a
  `"memory"` clobber; `micro_os_plus_architecture_set_sp()` forwarding
  to it.
- C++: `void sp(register_t top_of_stack) noexcept;` overloads in both
  `aarch64::architecture::registers` and
  `micro_os_plus::architecture::registers`.
- Documentation must state the constraints, which are stricter than on
  Cortex-M. AArch64 has a single current `sp`, with no separate
  main and process pointers (`msp`/`psp`) to switch between. The compiler
  addresses locals and spills relative to `sp` (often without a frame
  pointer), so changing it from C/C++ is only safe:
  - where the function has no stack frame to preserve, for example
    early startup; or
  - when the call is immediately followed by a call to a `noreturn`
    function.

  The value must also be 16-byte aligned, since stack accesses through
  a misaligned `sp` fault when `SCTLR_ELx.SA` is set.
- Optionally, as the AArch64 analogue of `psp`, add
  `aarch64_architecture_get_sp_el0()` / `set_sp_el0()` (`mrs`/`msr
  sp_el0`), valid only at EL1 or higher with `SPSel == 1`; this is the
  safe way for an RTOS to prepare a thread stack.

**2. Possible C++ linkage of `micro_os_plus_semihosting_call_host`.** —
**Closed (2026-10-01):** the definition is now compiled only when
`micro-os-plus/semihosting.h` is found, so it always has the `extern "C"`
prototype (verified with `nm`: no symbol without the header, the C symbol
with the semihosting package header). No residual issue: without the
header no caller can compile a call to it, so omitting the definition is
harmless.
[semihosting.cpp:16-18](src/semihosting.cpp#L16-L18) includes
`micro-os-plus/semihosting.h` only if `__has_include` finds it, while the
body is compiled whenever `MICRO_OS_PLUS_SEMIHOSTING_ENABLED` is defined.
If the header is absent, the definition has no `extern "C"` prototype and
is emitted as `_Z35micro_os_plus_semihosting_call_hostiPm` (verified).
C callers then fail to link, and the cause is not obvious. Either include
the header unconditionally inside the `#if`, or emit `#error` when
semihosting is enabled but the header is missing, or wrap the definition
in `extern "C"`.

**3. `wfi` has no `memory` clobber.** — **Closed (2026-10-01):** the
`"memory"` clobber was added.
[instructions-inlines.h:63-74](include/micro-os-plus/architecture-aarch64/inlines/instructions-inlines.h#L63-L74).
Without it, the compiler may move memory accesses (for example, a flag set
by an interrupt handler) across the wait. CMSIS uses `"memory"` for
`__WFI()`. Add it.

**4. Semihosting comments and names are AArch32/Angel leftovers.** — **Closed (2026-10-01):** the
comments now describe the AArch64 `hlt #0xF000` convention and reference
the Arm semihosting specification in the `abi-aa` repository. The macro
names are tracked in #11.
[semihosting.cpp:27-29](src/semihosting.cpp#L27-L29) and
[:46-53](src/semihosting.cpp#L46-L53) refer to "SWI numbers", "RDI
(Angel) monitors", "supervisor mode", "APCS", and ARM DUI 0040D. None of
these apply to AArch64 `hlt #0xF000` semihosting. The current Arm
semihosting specification should be referenced instead.

**5. Semihosting clobber list is pessimistic.** — **Closed (2026-10-01),
no change needed:** checked against the specification (`abi-aa`
`semihosting.rst`, release 2025Q4). It defines `x0` as the return
register and states that some operations also return information in
`x1` (for example `SYS_ELAPSED`), but it does **not** state that the
other registers are preserved. The original claim below was therefore
wrong. The defensive clobbers are justified, and the cost (saving and
restoring `x30`) is negligible compared with a debugger trap. The
comments in the code were corrected accordingly.
[semihosting.cpp:45](src/semihosting.cpp#L45) clobbers `x2`, `x3`,
`x17`, `x30`, and `cc`. The AArch64 semihosting specification states that
only `x0` is modified by the call. The extra clobbers are harmless, but
without a justification they mislead readers; either drop them or
document why they are kept (for example, as defence against
non-conforming debuggers).

### Documentation (Doxygen)

**6. Missing `@brief`/`@details` on many declarations.** — **Closed (2026-10-01):** all declarations, definitions, typedefs, the macro, and the files now have Doxygen blocks, following the AArch32 package; Doxygen 1.17 reports no warnings (with `EXTRACT_STATIC`, `EXTRACT_ANON_NSPACES`, `WARN_NO_PARAMDOC`, and `__attribute__(x)` predefined empty).
- `aarch64_architecture_nop/wfi/dsb/isb`
  ([instructions.h:32-74](include/micro-os-plus/architecture-aarch64/instructions.h#L32-L74)).
- `micro_os_plus_architecture_nop/wfi`
  ([:79-99](include/micro-os-plus/architecture-aarch64/instructions.h#L79-L99)).
- The C++ `nop/wfi/dsb/isb`
  ([:144-186](include/micro-os-plus/architecture-aarch64/instructions.h#L144-L186),
  [:196-216](include/micro-os-plus/architecture-aarch64/instructions.h#L196-L216)).
- `micro_os_plus_architecture_show_cpuid()`
  ([functions.h:24](include/micro-os-plus/architecture-aarch64/functions.h#L24)).
- All typedefs and `using` aliases in
  [types.h](include/micro-os-plus/architecture-aarch64/types.h) and
  [semihosting-inlines.h](include/micro-os-plus/architecture-aarch64/inlines/semihosting-inlines.h)
  (plain `//` comments only).
- `MICRO_OS_PLUS_ARCHITECTURE_STACK_FILL_MAGIC` in
  [defines.h:18](include/micro-os-plus/architecture-aarch64/defines.h#L18).
- None of the parameters or return values documented with `@param` or
  `@return`, other than the stack pointer getters.

**7. Stale duplicate comments on inline definitions.** — **Closed (2026-10-01):** the one-line comments were replaced by `@details` blocks describing the implementation (clobbers, forwarding).
[instructions-inlines.h:108-142](include/micro-os-plus/architecture-aarch64/inlines/instructions-inlines.h#L108-L142)
carries one-line comments ("`break` instruction.", etc.) that duplicate,
and in one case contradict (`break` vs `brk`), the header documentation.
Either remove them or turn them into proper `@details` for the
definitions.

**8. American spelling.** — **Closed (2026-10-01):** "Synchronization" was replaced by "Synchronisation".
"Synchronization" at
[instructions.h:65](include/micro-os-plus/architecture-aarch64/instructions.h#L65),
[:71](include/micro-os-plus/architecture-aarch64/instructions.h#L71),
[:177](include/micro-os-plus/architecture-aarch64/instructions.h#L177),
and [:183](include/micro-os-plus/architecture-aarch64/instructions.h#L183).
The project requires British English ("Synchronisation").

**9. Misleading section titles.** — **Closed (2026-10-01):** the registers titles are accurate now that the setters exist (#1).
[instructions.h:22](include/micro-os-plus/architecture-aarch64/instructions.h#L22)
and the registers comments say "getters and mutators", but there are no
mutators (see #1). Update the titles together with #1.

### Modern C++

**10. No `noexcept` or `[[nodiscard]]` on the C++ wrappers.** — **Closed (2026-10-01):** all 15 C++
wrappers are `noexcept` (declarations and definitions), and both `sp()`
getters are `[[nodiscard]]`; verified with `static_assert(noexcept(...))`
and the `-Wunused-result` diagnostic in GCC and clang. In addition, the
compiler-specific `inline __attribute__ ((always_inline))` specifiers were
replaced by the `MICRO_OS_PLUS_ALWAYS_INLINE` macro, as in the
AArch32 package (`[[gnu::always_inline]] inline` in C++).
None of the C++ functions in `instructions.h` and `registers.h` can
throw; declare them `noexcept`. The `sp()` getters should also be
`[[nodiscard]]`.

**11. Macros in `semihosting.cpp`.** — **Closed (2026-10-01):** replaced by a
`constexpr` `semihosting_hlt_number` in an anonymous namespace, following
the AArch32 package; the operands are now bound to `x0`/`x1` with explicit
register variables.
`AngelSVC` / `AngelSVCInsn`
([semihosting.cpp:28-29](src/semihosting.cpp#L28-L29)) are CamelCase
macros, contrary to the snake_case convention. The immediate can be a
`constexpr` passed through the `"n"` constraint, and the mnemonic can be
written literally.

### Naming and style

**12. Line exceeds 80 characters.** — **Closed (2026-10-01):** resolved
by the restructuring of the conditionals for #2.
[semihosting.cpp:59](src/semihosting.cpp#L59) is 108 characters (the
`#endif` comment). This is a conflict between the 80-column rule and the
"repeat the exact `#if` expression" rule. Decide which prevails and record
the decision in the skill.

**13. Unused `using namespace micro_os_plus;`.** — **Closed (2026-10-01):** removed.
[show-cpuid.cpp:22](src/show-cpuid.cpp#L22) serves no purpose in an empty
function.

### Licensing and metadata

**14.** All files carry the MIT header. The copyright ranges are
plausible. The pending changes (`MICRO_OS_PLUS_ARCHITECTURE_AARCH64_ENABLED`
now required, register renames) are incompatible, and are not yet in
`CHANGELOG.md`; the next version should be a major bump (see the README).

### Folder structure

No findings. `semihosting-inlines.h` contains no inline functions, only
typedefs; the name is inherited from the other architectures and is
acceptable for consistency.

### Conditional compilation

No findings. All `#endif` lines carry the matching comment, and there are
no bare `#ifdef`/`#ifndef` outside the include guards.

### Tests

**15. No tests.**
Nothing in this package is tested. At minimum, a compile-only test
(C and C++, with and without the enable macro, and as assembler) would
have caught the old include-guard collision and would catch #2. A QEMU
AArch64 test could exercise `get_sp`/`set_sp` and semihosting.

## Left out (not certain enough)

- `MICRO_OS_PLUS_ARCHITECTURE_STACK_FILL_MAGIC` is a 32-bit value on a
  64-bit architecture. Whether this matters depends on how the startup
  code fills the stack; that code is not in this package. — **Resolved (2026-10-01):** the value is now 64-bit.
- `architecture.h` silently yields nothing when the enable macro is
  missing. An `#error` (or `#warning`) might be friendlier, but it would
  break multi-architecture builds that include every architecture package,
  if such builds exist.
- `show_cpuid()` could print `MIDR_EL1`, but `mrs` of it traps at EL0 on
  some configurations. The right behaviour depends on the exception level
  used by the µOS++ AArch64 startup. — **Done (2026-10-01):** the startup
  runs at EL1; `show_cpuid()` now decodes `MIDR_EL1`, verified on QEMU
  with 12 CPU models.
- The same Cortex-M defects (`msr %0, msp`/`psp` used to read, with a
  `uint32_t` result) exist in
  `architecture-cortexm-xpack/.../inlines/registers-inlines.h`. That is
  outside this review's scope, but it should be checked there.
