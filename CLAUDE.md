# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with
code in this repository.

@.github/copilot-instructions.md

## Project Overview

`@micro-os-plus/architecture-aarch64` is a small **source-only** xpm/npm
package providing the Arm AArch64 architecture layer for µOS++. It is not
built on its own; consumer projects add it as a dependency and compile its
sources as part of their own build. It is the AArch64 counterpart of
`architecture-cortexm-xpack` and `architecture-riscv-xpack`, and implements
the generic `micro-os-plus.architecture` interface.

Active development happens on the `xpack-development` branch; `xpack` is the
stable branch. `master` is not used for development.

## Build Integration

There is no standalone build and no functional test suite in this
repository (`tests/CMakeLists.txt` is a `# TODO` placeholder, and there is no
`tests/package.json`). Validation happens in dependent projects (for example,
the µOS++ templates and `micro-test-plus` tests running on QEMU AArch64).

To check changes locally, compile against the headers with the AArch64 cross
toolchain (`~/.local/xPacks/@xpack-dev-tools/aarch64-none-elf-gcc/`), in
both C and C++20, with `-Iinclude
-DMICRO_OS_PLUS_ARCHITECTURE_AARCH64_ENABLED`; without that define every
header is empty and nothing is actually checked. `src/semihosting.cpp` also
needs `-DMICRO_OS_PLUS_SEMIHOSTING_ENABLED` and a
`micro-os-plus/semihosting.h` from the semihosting package. The xPack clang
installed by `xpm install` on macOS lacks the AArch64 backend; Apple clang
works with `--target=aarch64-none-elf -ffreestanding`.

Consumers integrate the package via:

- CMake: `add_subdirectory("xpacks/@micro-os-plus/architecture-aarch64")`,
  then link `micro-os-plus::architectures-aarch64` or the generic alias
  `micro-os-plus::architecture` (an `INTERFACE` library; sources propagate
  to the consumer).
- Meson: `subdir(...)`, then use
  `micro_os_plus_architecture_aarch64_dependency` or
  `micro_os_plus_architecture_dependency`.

### Generated files — do not edit by hand

`xcdl-package.jsonc` is the single source of truth for components, include
folders, and source files. `CMakeLists.txt` and `meson.build` are generated
from it (templates in `scripts/templates/`):

```sh
xpm run xcdl-export        # regenerate CMakeLists.txt and meson.build
```

When adding or removing a source file, edit `xcdl-package.jsonc` and
regenerate, rather than editing the CMake or Meson files directly.

Many other files (`.gitignore`, `.github/workflows/*.yml`, the `scripts/*.mjs`
helpers) carry a `DO NOT EDIT! Automatically generated` banner; they come from
`@xpack/npm-packages-helper` (`npm run generate-top-commons`) and changes must
be made in that helper's templates.

### Formatting

```sh
xpm install                # fetches the pinned clang (21.x) toolchain
xpm run clang-format       # C/C++ sources and headers
xpm run cmake-format
xpm run jsonc-format
```

Always reformat changed source files before committing.

## Architecture

### Compile-time enablement

Everything is guarded by `MICRO_OS_PLUS_ARCHITECTURE_AARCH64_ENABLED`, which
is expected to come from the xcdl-generated
`micro-os-plus/architecture-defines.h` (or from
`micro-os-plus/project-config.h`); both are picked up via `__has_include` in
[include/micro-os-plus/architecture.h](include/micro-os-plus/architecture.h).
If the macro is not defined, the headers expose nothing and all three source
files compile to empty translation units. Semihosting code additionally
requires `MICRO_OS_PLUS_SEMIHOSTING_ENABLED`.

The C++ headers require C++20.

### Header layout

`architecture.h` is the single public entry point. It always includes
`defines.h` (safe for assembly), and, unless `__ASSEMBLER__` is defined, also
`types.h`, `functions.h`, `instructions.h`, `registers.h`, and
`inlines/semihosting-inlines.h`.

Each API is exposed in three parallel forms, which must be kept in sync:

1. C functions with an `aarch64_architecture_` prefix (architecture-specific).
2. C functions with a `micro_os_plus_architecture_` prefix (portable names
   shared with the other architecture packages).
3. C++ wrappers in `namespace aarch64::architecture` and
   `namespace micro_os_plus::architecture`.

Declarations live in `instructions.h` / `registers.h`; the bodies (inline
assembly) live in `inlines/` and are included at the bottom of the declaring
header. Both declarations and definitions use
`MICRO_OS_PLUS_ALWAYS_INLINE` (from `defines.h`, shared with the
AArch32 package): `static inline __attribute__ ((always_inline))` in C, and
`[[gnu::always_inline]] inline` in C++ (external linkage, required by the
One Definition Rule). In C++ it must follow any standard attributes such as
`[[nodiscard]]`; GNU `__attribute__` specifiers go after it. C++ wrappers are
`noexcept`.

The headers in `inlines/` are intentionally **not** self-contained: they
include only system headers (such as `<stdint.h>`), never other local
headers, and rely on the declaring header (or `architecture.h`) having
included `defines.h` and `types.h` first. Do not add local includes to them.
The other headers are expected to compile on their own.

`inlines/semihosting-inlines.h` does not contain functions; it defines the
architecture-width types (`micro_os_plus_semihosting_register_t`,
`_param_block_t`, `_response_t`) consumed by the separate
`@micro-os-plus/semihosting` package.

### Sources

- [src/semihosting.cpp](src/semihosting.cpp):
  `micro_os_plus_semihosting_call_host()` using `hlt #0xF000` (AArch64 Angel
  semihosting). It includes `micro-os-plus/semihosting.h`, which is **not** a
  declared dependency (doing so would create a circular dependency, as noted
  in `xcdl-package.jsonc`); the consumer must supply it.
- [src/_init_fini.c](src/_init_fini.c): weak empty `_init()` / `_fini()`,
  required by newlib's `__libc_fini_array`.
- [src/show-cpuid.cpp](src/show-cpuid.cpp):
  `micro_os_plus_architecture_show_cpuid()`, decodes `MIDR_EL1` (needs
  EL1, which the µOS++ startup uses) and prints it via `diag-trace`, which
  is included only if `__has_include` finds it (an optional dependency).

### Linker script

[linker-scripts/sections-ram.ld](linker-scripts/sections-ram.ld) is a generic
RAM-only layout (entry `Reset_Handler`, µOS++ `__data_regions_array_*` /
`__bss_regions_array_*` tables, `__stack` / `__stack_size` defaulting to the
top of `RAM` and 16 KiB). Device packages may override it. It is not
referenced by the CMake or Meson files; consumers pass it to the linker
themselves.

## Naming Notes

- The AArch64 breakpoint instruction is `brk`; `aarch64_architecture_brk()`
  and `aarch64::architecture::brk()` are the current names. The `bkpt`
  variants are deprecated aliases kept for compatibility with 4.1.0; do not
  use them in new code.
- The stack pointer getters and setters (`*_get_sp()` / `*_set_sp()`,
  C++ `registers::sp()` / `registers::sp(register_t)`) use `mov` to and
  from `sp`; AArch64 has no `msp`/`psp`, so Cortex-M names must not be
  reintroduced. The setters are only safe without a live stack frame or
  right before a `noreturn` call; keep that caveat in their documentation.

## Releases

The procedure is documented in [README-MAINTAINER.md](README-MAINTAINER.md):
update `CHANGELOG.md`, bump the version with `npm version`, `npm pack` to
check the contents (adjust `.npmignore` if needed), and `npm publish`. Keep
the version in `package.json`, `README-MAINTAINER.md`, and `CHANGELOG.md`
consistent.
