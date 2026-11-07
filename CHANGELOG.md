# Change & release log

Releases in reverse chronological order.

Please check
[GitHub](https://github.com/micro-os-plus/architecture-aarch64-xpack/issues/)
and close existing issues and pull requests.

## 2026-11-07

* v5.0.0
* 09a6021 re-generate top commons

## 2026-10-09

* d5accd4 xcdl micro-os-plus.architecture.aarch64
* e4bd0cf re-generate top commons
* 30c50da move to maintenance
* ac7e564 MICRO_OS_PLUS_ARCHITECTURE_AARCH64_ENABLED
* 1c754c6 MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE

## 2026-10-01

* d1de4f0 re-format
* cfa19d4 rename package description
* 783894c rename _ARCHITECTURE_STACK_FILL_MAGIC
* 36ac9e9 implement show_cpuid
* 576c61b cleanup
* bfe6874 add MICRO_OS_PLUS_ARCHITECTURE_ALWAYS_INLINE
* 71719f4 add noexcept and nodiscard
* c2e802d add doxygen comments
* c121c5e brk() with memory clobber
* 7fc2051 semihosting.cpp: document clobber
* e468797 semihosting.cpp rework with hlt
* 804b4e3 wfi with memory barrier
* db1ddc9 semihosting.cpp: fix conditional compilation
* 1e81d9f add stack setter
* 3990d56 copilot instructions
* 41e14c7 cosmetics
* 54bff27 enable MICRO_OS_PLUS_ARCHITECTURE_AARCH64_ENABLED guard
* 8a677da get_sp()
* b94f9d0 architecture::brk for deprecated bkpt
* ecb0097 add data/instruction barrier
* 69869f1 check __ASSEMBLER__

## 2026-09-09

* c947319 4.1.0
* 5110712 prepare v4.1.0
* c7c2f8b re-format

## 2026-09-08

* b00a4c6 architecture.h __ASSEMBLY__
* bf5a452 add micro_os_plus_semihosting_register_t

## 2026-09-07

* 36424f1 cosmetics xpm packages
* 1861f7f add show-cpuid

## 2026-08-05

* bcc4058 readme cosmetics

## 2026-08-04

* defb1d3 4.0.0
* 5b5b67a README update
* 340aa2b prepare v4.0.0
* 95f0e61 re-generate top commons

## 2026-07-31

* 2f1b98e CHANGELOG update
* 72cac7f re-generate top xcdl
* 88d71c5 xcdl-package.json update
* 2c0c19d re-generate top commons
* a32249d cosmetise guards & includes

## 2026-07-21

* ccf4eaa re-work with inlines folder
* d3b1bf7 xcdl export
* 867941b re-format clang
* 4d4c069 extract semihosting.cpp
* b40ed4c update copyright notices
* 03b2db2 re-generate top commons

## 2026-06-06

* 3dd3779 copyright update 2026

## 2025-11-20

* 4f49110 rename npm-pack

## 2025-10-07

* f2e2ff0 update copyright notices

## 2023-11-28

* 08e6765 README updates
* 5b52c64 package.json: cosmetise scripts

## 2023-10-19

* d7d8b7b package.json: cosmetise description
* 0946936 README updates

## 2023-07-14

* dfb5663 README updates
* f22d86c package.json: cosmetise urls
* 078edb0 package.json: minXpm 0.16.2

## 2023-06-04

* 906b0af update for @scope/name

## 2023-06-03

* f20f47f lower case ci.yml
* 2307382 package.json min 0.16.0

## 2023-05-08

* a0ee320 .npmignore update
* 99fb8b3 3.2.0
* 88e34f9 remove .gitkeep
* 4338dff prepare v3.2.0
* 0e3f852 prepare v3.2.0
* 4d41e7b README updates
* 361c2ed README update
* 1b365eb #3: add _init_fini()

## 2022-08-16

* 01a9ed5 package.json min 0.14.0 & defaults

## 2022-08-03

* fb1ddcd .vscode/settings.json: cmake.ignoreCMakeListsMissing
* 8966ef3 .vscode/settings.json: makefile.configureOnOpen

## 2022-07-28

* 72122b6 CHANGELOG update
* e12c9d9 #2: fix w register name

## 2022-07-28

* v3.1.0
* e12c9d9 #2: fix w register name
* 1b8dbe0 #2: use names for semihosting_call_host() args
* 5423ec0 #1: Add signed_register_t for semihosting result

## 2022-07-25

* 9a7e15d define.h comment out MICRO_OS_PLUS_HAS_INTERRUPTS_STACK
* a13ed7e add preliminary xpack.json

## 2022-07-12

* v3.0.0
* 7ce2426 rework as aarch64
* copy/paste architecture-cortexa-xpack

## 2022-06-09

* v2.0.0 released
* 7dcab86 sections-ram.ld update stack & heap; cleanups
* 3419641 remove sections-flash.ld
* 26f568c architecture.h: include registers-inlines.h
* 8f9cbab registers-inlines.h: fix getters & setters
* d2c90ae move exceptions & vectors to qemu device for now

## 2022-06-03

* v1.0.0 released

## 2022-05-22

* v1.0.0 prepared
* copied from architecture-cortexm-xpack
