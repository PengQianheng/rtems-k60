/* SPDX-License-Identifier: BSD-2-Clause */

/*
 * Copyright (C) 2020 embedded brains GmbH (http://www.embedded-brains.de)
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stm32h7/hal.h>

static const stm32h7_uart_config stm32h7_usart2_config = {
  .gpio = {
    .regs = GPIOA,
    .config = {
      .Pin = GPIO_PIN_2 | GPIO_PIN_3,
      .Mode = GPIO_MODE_AF_PP,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_FREQ_LOW,
      .Alternate = GPIO_AF7_USART2
    }
  },
  .irq = USART2_IRQn,
  .device_index = 1
};

stm32h7_uart_context stm32h7_usart2_instance = {
  .uart = {
    .Instance = USART2,
    .Init.BaudRate = BSP_CONSOLE_BAUD,
    .Init.WordLength = UART_WORDLENGTH_8B,
    .Init.StopBits = UART_STOPBITS_1,
    .Init.Parity = UART_PARITY_NONE,
    .Init.Mode = UART_MODE_TX_RX,
    .Init.HwFlowCtl = UART_HWCONTROL_NONE,
    .Init.OverSampling = UART_OVERSAMPLING_16,
    .Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE,
    .Init.ClockPrescaler = UART_PRESCALER_DIV1,
    .AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT
  },
  .config = &stm32h7_usart2_config
};
