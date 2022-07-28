# Change & release log

Releases in reverse chronological order.

Please check
[GitHub](https://github.com/micro-os-plus/architecture-aarch64-xpack/issues/)
and close existing issues and pull requests.

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
