[![GitHub package.json version](https://img.shields.io/github/package-json/v/micro-os-plus/architecture-aarch64-xpack)](https://github.com/micro-os-plus/architecture-aarch64-xpack/blob/xpack/package.json)
[![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/micro-os-plus/architecture-aarch64-xpack)](https://github.com/micro-os-plus/architecture-aarch64-xpack/tags/)
[![npm (scoped)](https://img.shields.io/npm/v/@micro-os-plus/architecture-aarch64.svg?color=blue)](https://www.npmjs.com/package/@micro-os-plus/architecture-aarch64/)
[![license](https://img.shields.io/github/license/micro-os-plus/architecture-aarch64-xpack)](https://github.com/micro-os-plus/architecture-aarch64-xpack/blob/xpack/LICENSE)
[![CI on Push](https://github.com/micro-os-plus/architecture-aarch64-xpack/actions/workflows/test-ci.yml/badge.svg)](https://github.com/micro-os-plus/architecture-aarch64-xpack/actions/workflows/test-ci.yml)

# A source code library with the µOS++ architecture definitions for Arm AArch64 (64-bit Cortex-A)

This project provides the **architecture-aarch64** source library as an `xpm`
dependency and includes architecture definitions for embedded projects
running on Arm Cortex-A devices in AArch64 (64-bit) state.

The project is hosted on GitHub as
[micro-os-plus/architecture-aarch64-xpack](https://github.com/micro-os-plus/architecture-aarch64-xpack).

This page is addressed to developers who plan to include this source
library into their own projects.

For maintainer information, please see the
[README-MAINTAINER](README-MAINTAINER.md) file.

## Install

As a source library xpm package, the easiest way to add it to a project is via
**xpm**, but it can also be used as any Git project, for example as a submodule.

### Prerequisites

A recent [xpm](https://xpack.github.io/xpm/),
which is a portable [Node.js](https://nodejs.org/) command line application.

It is recommended to update to the latest version with:

```sh
npm install --global xpm@latest
```

For details please follow the instructions in the
[xPack install](https://xpack.github.io/install/) page.

### xpm

This package is available as
[`@micro-os-plus/architecture-aarch64`](https://www.npmjs.com/package/@micro-os-plus/architecture-aarch64)
from the `npmjs.com` registry:

```sh
cd my-project
xpm init # Unless a package.json is already present

xpm install @micro-os-plus/architecture-aarch64@latest

ls -l xpacks/@micro-os-plus/architecture-aarch64
```

### Git submodule

If, for any reason, **xpm** is not available, the next recommended
solution is to link it as a Git submodule below an `xpacks` folder.

```sh
cd my-project
git init # Unless already a Git project
mkdir -p xpacks

git submodule add https://github.com/micro-os-plus/architecture-aarch64-xpack.git \
  xpacks/@micro-os-plus/architecture-aarch64
```

## Branches

Apart from the unused `master` branch, there are two active branches:

- `xpack`, with the latest stable version (default)
- `xpack-development`, with the current development version

All development is done in the `xpack-development` branch, and contributions via
Pull Requests should be directed to this branch.

When new releases are published, the `xpack-development` branch is merged
into `xpack`.

## Developer info

### Overview

This source xpm package provides the AArch64 architecture layer of µOS++:
register types, wrappers for the CPU instructions (`nop`, `brk`, `wfi`,
`dsb`, `isb`), stack pointer accessors, the semihosting call, the CPU
identification display, and a generic RAM linker script.

### Status

The **architecture-aarch64** source library is fully functional,
but minimalistic, for running semihosted tests.

### Build & integration info

The project is written in C++, C, and inline assembly, and it is
expected to be used in C and C++ projects.

The source code is tested with aarch64-none-elf-gcc 11 to 15,
and should be warning free.

To ease the integration of this package into user projects,
ready-made CMake and meson configuration files are provided (see below).

For other build systems, consider the following details:

#### Include folders

The following folders should be passed to the compiler during the build:

- `include`

The header files to be included in user projects are:

```c++
#include "micro-os-plus/architecture.h"
```

#### Source files

The source files to be added to user projects are:

- `src/show-cpuid.cpp` - `micro_os_plus_architecture_show_cpuid()`,
  which decodes `MIDR_EL1` and writes a line like `Arm Cortex-A53 r0p4`
  to the trace output
- `src/semihosting.cpp` - the semihosting call for this platform
  (`hlt #0xF000`)
- `src/_init_fini.c` - empty definitions required by newlib

#### Preprocessor definitions

The configuration definitions are expected either in the specific header file
`micro-os-plus/architecture-defines.h` or in the common project configuration
file `micro-os-plus/project-config.h`:

- `MICRO_OS_PLUS_ARCHITECTURE_AARCH64_ENABLED` - enable the inclusion of the
  architecture files in the build; without it, the headers and the source
  files are empty
- `MICRO_OS_PLUS_SEMIHOSTING_ENABLED` - enable the semihosting call in
  `src/semihosting.cpp`; requires the `semihosting` package

The package itself defines, in `defines.h`:

- `MICRO_OS_PLUS_ARCHITECTURE_STACK_FILL_MAGIC` - the 64-bit value used
  by the device and RTOS port packages to fill the stacks
- `MICRO_OS_PLUS_ALWAYS_INLINE` - the specifiers of the
  always inlined wrappers (`static inline` in C, `inline` in C++)

#### Compiler options

- `-std=c++20` or higher for C++ sources
- `-std=c11` for C sources

#### C++ Namespaces

Portable:

- `micro_os_plus::architecture`
- `micro_os_plus::architecture::registers`

Architecture specific:

- `aarch64::architecture`
- `aarch64::architecture::registers`

#### C API

Each C++ function also has C equivalents, with the portable
`micro_os_plus_architecture_` prefix and the architecture specific
`aarch64_architecture_` prefix:

| Portable C++            | Portable C                                         | AArch64 instruction |
| ----------------------- | -------------------------------------------------- | ------------------- |
| `nop()`                 | `micro_os_plus_architecture_nop()`                 | `nop`               |
| `brk()`                 | `micro_os_plus_architecture_brk()`                 | `brk #0`            |
| `wfi()`                 | `micro_os_plus_architecture_wfi()`                 | `wfi`               |
| `data_barrier()`        | `micro_os_plus_architecture_data_barrier()`        | `dsb sy`            |
| `instruction_barrier()` | `micro_os_plus_architecture_instruction_barrier()` | `isb`               |
| `registers::sp()`       | `micro_os_plus_architecture_get_sp()`              | `mov <Xd>, sp`      |
| `registers::sp(top)`    | `micro_os_plus_architecture_set_sp(top)`           | `mov sp, <Xn>`      |

Setting the stack pointer from C/C++ is safe only when the calling
function has no stack frame still in use (for example, in the startup
code), or when it is immediately followed by a call to a function that
does not return; the value must be 16-byte aligned.

#### C++ Classes

- none

#### Dependencies

- `@micro-os-plus/semihosting` - optional, required only when semihosting
  is used
- `@micro-os-plus/diag-trace` - optional, required only for the
  `micro_os_plus_architecture_show_cpuid()` output

#### CMake

To integrate the architecture-aarch64 source library into a CMake application,
add this folder to the build:

```cmake
add_subdirectory("xpacks/@micro-os-plus/architecture-aarch64")
```

The result is an interface library that can be added as an application
dependency with:

```cmake
target_link_libraries(your-target PRIVATE

  micro-os-plus::architectures-aarch64
)
```

The generic alias `micro-os-plus::architecture` refers to the same
library, and can be used when the application is architecture agnostic.

#### meson

To integrate the architecture-aarch64 library into a meson application,
add this folder to the build:

```meson
subdir('xpacks/@micro-os-plus/architecture-aarch64')
```

The result is a dependency object that can be added
to an application with:

```meson
exe = executable(
  'your-target',
  c_args: micro_os_plus_architecture_aarch64_dependency_compile_c_args,
  cpp_args: micro_os_plus_architecture_aarch64_dependency_compile_cpp_args,
  link_with: [
    # Nothing, not static.
  ],
  dependencies: [
    micro_os_plus_architecture_aarch64_dependency,
  ]
)
```

The generic `micro_os_plus_architecture_dependency` object (with the
corresponding `_compile_c_args` and `_compile_cpp_args` variables) refers
to the same sources, and can be used when the application is
architecture agnostic.

#### xCDL

The package metadata for the xCDL build configuration tools is
available in `xcdl-package.jsonc`.

#### Linker scripts

The `linker-scripts` folder includes `sections-ram.ld`, a generic
linker script for configurations running entirely from RAM; it may be
redefined at device level.

### Examples

With `MICRO_OS_PLUS_ARCHITECTURE_AARCH64_ENABLED` defined:

```c++
#include "micro-os-plus/architecture.h"

using namespace micro_os_plus;

architecture::register_t reg;

reg = architecture::registers::sp();

architecture::data_barrier();
architecture::instruction_barrier();
```

### Known problems

- none

### Tests

There are no tests in this package yet; the functionality is exercised
by the tests of the packages that depend on it, like
[micro-test-plus](https://github.com/micro-os-plus/micro-test-plus-xpack).

## Change log - incompatible changes

According to [semver](https://semver.org) rules:

> Major version X (X.y.z | X > 0) MUST be incremented if any
> backwards incompatible changes are introduced to the public API.

The incompatible changes, in reverse chronological order,
are:

- v5.x:
  - `MICRO_OS_PLUS_ARCHITECTURE_AARCH64_ENABLED` must be defined to
    enable this library; without it, the headers and the source files
    are empty
  - the stack pointer getters were renamed and fixed:
    `aarch64_architecture_get_msp()` is now `aarch64_architecture_get_sp()`,
    and `aarch64::architecture::registers::msp()` is now `sp()`
    (the previous definitions were not usable)
  - the stack pointer setters `aarch64_architecture_set_sp()`,
    `micro_os_plus_architecture_set_sp()`, and the C++ `sp(register_t)`
    overloads were added
  - `aarch64_architecture_bkpt()` and `aarch64::architecture::bkpt()`
    were renamed `brk()`; the old names are deprecated aliases
  - `MICRO_OS_PLUS_INTEGER_STARTUP_STACK_FILL_MAGIC` was renamed
    `MICRO_OS_PLUS_ARCHITECTURE_STACK_FILL_MAGIC`, and its value was
    extended to 64 bits
  - the C++ wrappers are `noexcept`, and the `sp()` getters are
    `[[nodiscard]]`
- v4.x:
  - the CMake alias was renamed `micro-os-plus::architectures-aarch64`
    (the generic `micro-os-plus::architecture` was preserved)
  - the specific meson dependency is
    `micro_os_plus_architecture_aarch64_dependency`
  - `src/semihosting.cpp` and `src/_init_fini.c` were added in v4.0.0,
    and `src/show-cpuid.cpp` in v4.1.0; they must be compiled
  - the inline headers were moved to the `inlines` folder
- v3.x: first AArch64 release

(previous versions were part of `architecture-cortexa`)

## License

Unless otherwise stated, the content is released under the terms of the
[MIT License](https://opensource.org/licenses/mit),
with all rights reserved to
[Liviu Ionescu](https://github.com/ilg-ul).
