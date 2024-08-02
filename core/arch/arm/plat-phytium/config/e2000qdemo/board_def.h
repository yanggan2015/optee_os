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

#ifndef BOARD_DEF_H
#define BOARD_DEF_H

/* Make stacks aligned to data cache line length */
#define STACK_ALIGNMENT		64

#define GIC_BASE		0x30800000
#define UART0_BASE		0x2800d000
#define UART1_BASE		0xFF010000

#define IT_UART0		53
#define IT_UART1		54

#define UART0_CLK_IN_HZ		100000000
#define UART1_CLK_IN_HZ		100000000
#define CONSOLE_UART_BASE	UART0_BASE
#define IT_CONSOLE_UART		IT_UART0
#define CONSOLE_UART_CLK_IN_HZ	UART0_CLK_IN_HZ

#define DRAM0_BASE		0
#define DRAM0_SIZE		0x80000000

#define DRAM1_BASE		0x80000000
#define DRAM1_SIZE		0x7c000000

#define DRAM2_BASE		0x2000000000UL
#define DRAM2_SIZE		0x180000000UL

#define GICD_OFFSET		0
#define GICC_OFFSET		0x20000

#endif /* BOARD_DEF_H */
