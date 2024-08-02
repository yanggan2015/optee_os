/*
 * Phytium is pleased to support the open source community by making Phytium-optee available.
 * Copyright (c) 2023 Phytium Technology Co., Ltd.  All rights reserved.
 * Licensed under the BSD-2.0 License (the ""License""); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * https://opensource.org/license/bsd-license-php/
 * Unless required by applicable law or agreed to in writing, software distributed under the License is
 * distributed on an ""AS IS"" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PLATFORM_CONFIG_H
#define PLATFORM_CONFIG_H

#include "board_def.h" 
#include <mm/generic_ram_layout.h>

#ifdef CFG_WITH_PAGER
#error "Pager not supported!"
#endif

#ifdef CFG_TEE_LOAD_ADDR
#define TEE_LOAD_ADDR           CFG_TEE_LOAD_ADDR
#else
#define TEE_LOAD_ADDR           TEE_RAM_START
#endif

#ifndef UART_BAUDRATE
#define UART_BAUDRATE           115200
#endif
#ifndef CONSOLE_BAUDRATE
#define CONSOLE_BAUDRATE        UART_BAUDRATE
#endif

/* For virtual platforms where there isn't a clock */
#ifndef CONSOLE_UART_CLK_IN_HZ
#define CONSOLE_UART_CLK_IN_HZ  1
#endif

#endif /*PLATFORM_CONFIG_H*/
