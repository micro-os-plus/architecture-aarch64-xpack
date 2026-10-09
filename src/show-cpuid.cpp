/*
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2023-2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can be
 * obtained from https://opensource.org/licenses/mit.
 */

// ----------------------------------------------------------------------------

/**
 * @file
 * @brief AArch64 implementation of the CPU identification display.
 *
 * @details
 * Decodes the `MIDR_EL1` (Main ID Register) fields and writes a line
 * like `Arm Cortex-A53 r0p4` to the trace output channel.
 *
 * The implementer and part numbers are those listed in the Linux kernel
 * `arch/arm64/include/asm/cputype.h`.
 */

#include "micro-os-plus/architecture.h"

// ----------------------------------------------------------------------------

#if defined(MICRO_OS_PLUS_ARCHITECTURE_AARCH64_ENABLED)

// The trace output is optional; without the `diag-trace` package, the
// function is empty.
#if __has_include("micro-os-plus/diag/trace.h")
#include "micro-os-plus/diag/trace.h"

#include <cstdint>

// ----------------------------------------------------------------------------

namespace
{
  /**
   * @brief Get the name of a CPU implementer.
   *
   * @details
   * The implementer codes are assigned by Arm; only the most common ones
   * are listed.
   *
   * @param implementer The `MIDR_EL1.Implementer` field (bits [31:24]).
   * @return A pointer to a string literal with the implementer name, or
   * `nullptr` if the code is not known.
   */
  [[nodiscard]] const char*
  get_implementer_name (std::uint32_t implementer) noexcept
  {
    switch (implementer)
      {
      case 0x41U:
        return "Arm";
      case 0x42U:
        return "Broadcom";
      case 0x43U:
        return "Cavium";
      case 0x46U:
        return "Fujitsu";
      case 0x48U:
        return "HiSilicon";
      case 0x4EU:
        return "NVIDIA";
      case 0x50U:
        return "APM";
      case 0x51U:
        return "Qualcomm";
      case 0x61U:
        return "Apple";
      case 0x6DU:
        return "Microsoft";
      case 0xC0U:
        return "Ampere";
      default:
        return nullptr;
      }
  }

  /**
   * @brief Get the name of an Arm Ltd. core.
   *
   * @details
   * Only meaningful when the implementer is Arm (`0x41`); the part
   * numbers of the other implementers overlap with these.
   *
   * @param part_num The `MIDR_EL1.PartNum` field (bits [15:4]).
   * @return A pointer to a string literal with the core name, or
   * `nullptr` if the part number is not known.
   */
  [[nodiscard]] const char*
  get_arm_part_name (std::uint32_t part_num) noexcept
  {
    switch (part_num)
      {
      case 0xD00U:
        return "Foundation Model";
      case 0xD03U:
        return "Cortex-A53";
      case 0xD04U:
        return "Cortex-A35";
      case 0xD05U:
        return "Cortex-A55";
      case 0xD07U:
        return "Cortex-A57";
      case 0xD08U:
        return "Cortex-A72";
      case 0xD09U:
        return "Cortex-A73";
      case 0xD0AU:
        return "Cortex-A75";
      case 0xD0BU:
        return "Cortex-A76";
      case 0xD0CU:
        return "Neoverse-N1";
      case 0xD0DU:
        return "Cortex-A77";
      case 0xD0EU:
        return "Cortex-A76AE";
      case 0xD0FU:
        return "AEMv8 Model";
      case 0xD40U:
        return "Neoverse-V1";
      case 0xD41U:
        return "Cortex-A78";
      case 0xD42U:
        return "Cortex-A78AE";
      case 0xD44U:
        return "Cortex-X1";
      case 0xD46U:
        return "Cortex-A510";
      case 0xD47U:
        return "Cortex-A710";
      case 0xD48U:
        return "Cortex-X2";
      case 0xD49U:
        return "Neoverse-N2";
      case 0xD4BU:
        return "Cortex-A78C";
      case 0xD4CU:
        return "Cortex-X1C";
      case 0xD4DU:
        return "Cortex-A715";
      case 0xD4EU:
        return "Cortex-X3";
      case 0xD4FU:
        return "Neoverse-V2";
      case 0xD80U:
        return "Cortex-A520";
      case 0xD81U:
        return "Cortex-A720";
      case 0xD82U:
        return "Cortex-X4";
      case 0xD83U:
        return "Neoverse-V3AE";
      case 0xD84U:
        return "Neoverse-V3";
      case 0xD85U:
        return "Cortex-X925";
      case 0xD87U:
        return "Cortex-A725";
      case 0xD88U:
        return "Cortex-A520AE";
      case 0xD89U:
        return "Cortex-A720AE";
      case 0xD8AU:
        return "C1-Nano";
      case 0xD8BU:
        return "C1-Pro";
      case 0xD8CU:
        return "C1-Ultra";
      case 0xD8EU:
        return "Neoverse-N3";
      case 0xD90U:
        return "C1-Premium";
      default:
        return nullptr;
      }
  }
} // namespace

#endif // __has_include("micro-os-plus/diag/trace.h")

// ----------------------------------------------------------------------------

/**
 * @details
 * Reads `MIDR_EL1`, which requires EL1 or higher (the µOS++ AArch64
 * startup code runs at EL1), decodes its fields, and writes them to the
 * trace output channel:
 *
 * - Implementer, bits [31:24], as a name when known (e.g. `Arm`);
 * - PartNum, bits [15:4], as a core name when the implementer is Arm and
 *   the part is known (e.g. `Cortex-A53`), otherwise in hexadecimal;
 * - Variant, bits [23:20], and Revision, bits [3:0], as `rVpR`;
 * - Architecture, bits [19:16], only when it is not `0xF`, the value
 *   used by all Armv8 and later cores.
 *
 * When the `diag-trace` package is not available, the function is empty.
 */
void
micro_os_plus_architecture_show_cpuid (void)
{
#if __has_include("micro-os-plus/diag/trace.h")
  using namespace micro_os_plus;

  std::uint64_t midr;
  __asm__ volatile (

      " mrs %0, midr_el1 "

      : "=r"(midr) /* Outputs */
      : /* Inputs */
      : /* Clobbers */
  );

  const auto implementer = static_cast<std::uint32_t> ((midr >> 24) & 0xFFU);
  const auto variant = static_cast<std::uint32_t> ((midr >> 20) & 0x0FU);
  const auto architecture = static_cast<std::uint32_t> ((midr >> 16) & 0x0FU);
  const auto part_num = static_cast<std::uint32_t> ((midr >> 4) & 0xFFFU);
  const auto revision = static_cast<std::uint32_t> (midr & 0x0FU);

  const char* implementer_name = get_implementer_name (implementer);
  const char* part_name
      = (implementer == 0x41U) ? get_arm_part_name (part_num) : nullptr;

  if (implementer_name != nullptr)
    {
      trace::printf ("%s ", implementer_name);
    }
  else
    {
      trace::printf ("Implementer 0x%02X ", implementer);
    }

  if (part_name != nullptr)
    {
      trace::printf ("%s", part_name);
    }
  else
    {
      trace::printf ("part 0x%03X", part_num);
    }

  trace::printf (" r%up%u", variant, revision);

  if (architecture != 0xFU)
    {
      trace::printf (" (architecture 0x%X)", architecture);
    }

  trace::printf ("\n");
#endif // __has_include("micro-os-plus/diag/trace.h")
}

// ----------------------------------------------------------------------------

#endif // defined(MICRO_OS_PLUS_ARCHITECTURE_AARCH64_ENABLED)

// ----------------------------------------------------------------------------
