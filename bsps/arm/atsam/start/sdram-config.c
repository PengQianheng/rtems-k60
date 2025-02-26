/* SPDX-License-Identifier: BSD-2-Clause */

/*
 * Copyright (c) 2016 embedded brains GmbH.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <bspopts.h>
#include <chip.h>
#include <include/board_memories.h>

#if defined ATSAM_SDRAM_IS42S16100E_7BLI

#if ATSAM_MCK != 123000000
#error Please check SDRAM settings for this clock frequency.
#endif

const struct BOARD_Sdram_Config BOARD_Sdram_Config = {
  /* FIXME: a lot of these values should be calculated using CPU frequency */
  .sdramc_tr = 1562,
  .sdramc_cr =
      SDRAMC_CR_NC_COL8      /* 8 column bits */
    | SDRAMC_CR_NR_ROW11     /* 12 row bits (4K) */
    | SDRAMC_CR_CAS_LATENCY3 /* CAS Latency 3 */
    | SDRAMC_CR_NB_BANK2     /* 2 banks */
    | SDRAMC_CR_DBW          /* 16 bit */
    | SDRAMC_CR_TWR(5)
    | SDRAMC_CR_TRC_TRFC(13) /* 63ns   min */
    | SDRAMC_CR_TRP(5)       /* Command period (PRE to ACT) 21 ns min */
    | SDRAMC_CR_TRCD(5)      /* Active Command to R/W Cmd delay time 21ns min */
    | SDRAMC_CR_TRAS(9)      /* Command period (ACT to PRE)  42ns min */
    | SDRAMC_CR_TXSR(15U),   /* Exit self-refresh to active time  70ns Min */
  .sdramc_mdr = SDRAMC_MDR_MD_SDRAM,
  .sdramc_cfr1 = SDRAMC_CFR1_UNAL_SUPPORTED | SDRAMC_CFR1_TMRD(2),
  .sdramc_lpr = 0
};

#elif defined ATSAM_SDRAM_IS42S16320F_7BL

#if ATSAM_MCK != 123000000
#error Please check SDRAM settings for this clock frequency.
#endif

#define CLOCK_CYCLES_FROM_NS_MAX(ns) \
    (((ns) * (ATSAM_MCK / 1000ul / 1000ul)) / 1000ul)
#define CLOCK_CYCLES_FROM_NS_MIN(ns) (CLOCK_CYCLES_FROM_NS_MAX(ns) + 1)

const struct BOARD_Sdram_Config BOARD_Sdram_Config = {
  /* 8k refresh cycles every 64ms => 7.8125us */
  .sdramc_tr = CLOCK_CYCLES_FROM_NS_MAX(7812ul),
  .sdramc_cr =
      SDRAMC_CR_NC_COL10
    | SDRAMC_CR_NR_ROW13
    | SDRAMC_CR_CAS_LATENCY3
    | SDRAMC_CR_NB_BANK4
    | SDRAMC_CR_DBW
    /* t_WR = 30ns min (t_RC - t_RP - t_RCD;
     * see data sheet November 2015 page 55);
     * add some security margin */
    | SDRAMC_CR_TWR(CLOCK_CYCLES_FROM_NS_MIN(40))
    | SDRAMC_CR_TRC_TRFC(CLOCK_CYCLES_FROM_NS_MIN(60))
    | SDRAMC_CR_TRP(CLOCK_CYCLES_FROM_NS_MIN(15))
    | SDRAMC_CR_TRCD(CLOCK_CYCLES_FROM_NS_MIN(15))
    | SDRAMC_CR_TRAS(CLOCK_CYCLES_FROM_NS_MIN(37))
    | SDRAMC_CR_TXSR(CLOCK_CYCLES_FROM_NS_MIN(67)),
  .sdramc_mdr = SDRAMC_MDR_MD_SDRAM,
  .sdramc_cfr1 = SDRAMC_CFR1_UNAL_SUPPORTED |
      SDRAMC_CFR1_TMRD(CLOCK_CYCLES_FROM_NS_MIN(14)),
  .sdramc_lpr = 0
};

#elif defined ATSAM_SDRAM_MT48LC16M16A2P_6A

/*
 * Refresh: 7.81 us
 * TWR: 12 ns
 * TRC_TRFC: 60 ns
 * TRP: 15 ns
 * TRCD: 18 ns
 * TRAS: 42 ns
 * TXSR: 67 ns
 * TMRD: 2 clock cycles
 */

#if ATSAM_MCK == 60000000
const struct BOARD_Sdram_Config BOARD_Sdram_Config = {
  .sdramc_tr = 0x1D4,
  .sdramc_cr =
      SDRAMC_CR_NC_COL9
    | SDRAMC_CR_NR_ROW13
    | SDRAMC_CR_NB_BANK4
    | SDRAMC_CR_CAS_LATENCY3
    | SDRAMC_CR_DBW
    | SDRAMC_CR_TWR(3)
    | SDRAMC_CR_TRC_TRFC(8)
    | SDRAMC_CR_TRP(3)
    | SDRAMC_CR_TRCD(3)
    | SDRAMC_CR_TRAS(5)
    | SDRAMC_CR_TXSR(9),
  .sdramc_mdr = SDRAMC_MDR_MD_SDRAM,
  .sdramc_cfr1 = SDRAMC_CFR1_UNAL_SUPPORTED |
      SDRAMC_CFR1_TMRD(2),
  .sdramc_lpr = 0
};

#elif ATSAM_MCK == 123000000
const struct BOARD_Sdram_Config BOARD_Sdram_Config = {
  .sdramc_tr = 960,
  .sdramc_cr =
      SDRAMC_CR_NC_COL9
    | SDRAMC_CR_NR_ROW13
    | SDRAMC_CR_NB_BANK4
    | SDRAMC_CR_CAS_LATENCY3
    | SDRAMC_CR_DBW
    | SDRAMC_CR_TWR(2)
    | SDRAMC_CR_TRC_TRFC(8)
    | SDRAMC_CR_TRP(2)
    | SDRAMC_CR_TRCD(3)
    | SDRAMC_CR_TRAS(6)
    | SDRAMC_CR_TXSR(9),
  .sdramc_mdr = SDRAMC_MDR_MD_SDRAM,
  .sdramc_cfr1 = SDRAMC_CFR1_UNAL_SUPPORTED |
      SDRAMC_CFR1_TMRD(2),
  .sdramc_lpr = 0
};

#else /* ATSAM_MCK unknown */
#error Please check SDRAM settings for this frequency.
#endif

#elif defined ATSAM_SDRAM_CUSTOM
/*
 * Custom SDRAM defined. Provide only a dummy BOARD_Sdram_Config. This config
 * won't work and is only there so that test applications can link. The
 * application has to overwrite this BOARD_Sdram_Config!
 */
const struct BOARD_Sdram_Config BOARD_Sdram_Config = {};
#else
  #error SDRAM not supported.
#endif
