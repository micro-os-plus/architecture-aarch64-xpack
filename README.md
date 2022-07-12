[![license](https://img.shields.io/github/license/micro-os-plus/architecture-aarch64-xpack)](https://github.com/micro-os-plus/architecture-aarch64-xpack/blob/xpack/LICENSE)
[![CI on Push](https://github.com/micro-os-plus/architecture-aarch64-xpack/workflows/CI%20on%20Push/badge.svg)](https://github.com/micro-os-plus/architecture-aarch64-xpack/actions?query=workflow%3A%22CI+on+Push%22)

# A source library xPacks with the µOS++ Arm AArch64 architecture definitions

The project is hosted on GitHub as
[micro-os-plus/architecture-aarch64-xpack](https://github.com/micro-os-plus/architecture-aarch64-xpack).

## Maintainer info

This page is addressed to developers who plan to include this source
library into their own projects.

For maintainer info, please see the
[README-MAINTAINER](README-MAINTAINER.md) file.

## Install

As a source library xPacks, the easiest way to add it to a project is via
**xpm**, but it can also be used as any Git project, for example as a submodule.

### Prerequisites

A recent [xpm](https://xpack.github.io/xpm/),
which is a portable [Node.js](https://nodejs.org/) command line application.

For details please follow the instructions in the
[xPack install](https://xpack.github.io/install/) page.

### xpm

Note: the package will be available from npmjs.com at a later date.

For now, it can be installed from GitHub:

```sh
cd my-project
xpm init # Unless a package.json is already present

xpm install github:micro-os-plus/architecture-aarch64-xpack
```

When ready, this package will be available as
[`@micro-os-plus/architecture-aarch64`](https://www.npmjs.com/package/@micro-os-plus/architecture-aarch64)
from the `npmjs.com` registry:

```sh
cd my-project
xpm init # Unless a package.json is already present

xpm install @micro-os-plus/architecture-aarch64@latest

ls -l xpacks/micro-os-plus-architecture-aarch64
```

### Git submodule

If, for any reason, **xpm** is not available, the next recommended
solution is to link it as a Git submodule below an `xpacks` folder.

```sh
cd my-project
git init # Unless already a Git project
mkdir -p xpacks

git submodule add https://github.com/micro-os-plus/architecture-aarch64-xpack.git \
  xpacks/micro-os-plus-architecture-aarch64
```

## Branches

Apart from the unused `master` branch, there are two active branches:

- `xpack`, with the latest stable version (default)
- `xpack-develop`, with the current development version

All development is done in the `xpack-develop` branch, and contributions via
Pull Requests should be directed to this branch.

When new releases are published, the `xpack-develop` branch is merged
into `xpack`.

## Developer info

This source xPack provides general AArch64 definitions an
the implementation for the µOS++ scheduler,
running on **Arm AArch64** devices. (not yet)

### Status

The µOS++ AArch64 definitions are minimalistic, for running the tests.

### Build & integration info

To include this package in a project, consider the following details.

#### Include folders

The following folders should be passed to the compiler during the build:

- `include`

The header files to be included in user projects are:

```c++
#include <micro-os-plus/architecture.h>
```

#### Source files

The source files to be added to user projects are:

- none

#### Preprocessor definitions

- none

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

#### C++ Classes

- none

### Examples

```c++
#include <micro-os-plus/architecture.h>

using namespace micro_os_plus;

architecture::register_t reg;

reg = architecture::registers::sp();
```

### Known problems

- does not use CMSIS Core (yet)

### Tests

TBD

## Change log - incompatible changes

According to [semver](https://semver.org) rules:

> Major version X (X.y.z | X > 0) MUST be incremented if any
backwards incompatible changes are introduced to the public API.

The incompatible changes, in reverse chronological order,
are:

- v2.x: exception handling moved to qemu device for now;
  sections-flash.ld removed
- v1.x: initial release

## License

The original content is released under the
[MIT License](https://opensource.org/licenses/MIT/),
with all rights reserved to
[Liviu Ionescu](https://github.com/ilg-ul/).
