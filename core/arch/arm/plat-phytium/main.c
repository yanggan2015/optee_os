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

#include <stdint.h>
#include <string.h>
#include <arm.h>
#include <console.h>
#include <kernel/boot.h>
#include <kernel/interrupt.h>
#include <kernel/thread.h>
#include <kernel/misc.h>
#include <kernel/tee_time.h>
#include <mm/core_memprot.h>
#include <trace.h>
#include <io.h>
#include <drivers/pl011.h>
#include <drivers/gic.h>
#include <platform_config.h>

#ifdef CFG_PL011
static struct pl011_data console_data;
#endif

register_phys_mem_pgdir(MEM_AREA_IO_SEC,
			ROUNDDOWN(CONSOLE_UART_BASE, CORE_MMU_PGDIR_SIZE),
			CORE_MMU_PGDIR_SIZE);

register_phys_mem_pgdir(MEM_AREA_IO_SEC,
			ROUNDDOWN(GIC_BASE + GICC_OFFSET, CORE_MMU_PGDIR_SIZE),
			CORE_MMU_PGDIR_SIZE);

register_phys_mem_pgdir(MEM_AREA_IO_SEC,
			ROUNDDOWN(GIC_BASE + GICD_OFFSET, CORE_MMU_PGDIR_SIZE),
			CORE_MMU_PGDIR_SIZE);

#ifdef DRAM1_BASE
register_ddr(DRAM1_BASE,DRAM1_SIZE);
#endif

#ifdef DRAM2_BASE
register_ddr(DRAM2_BASE,DRAM2_SIZE);
#endif

void boot_primary_init_intc(void)
{
#ifdef GICD_BASE
	gic_init(0, GICD_BASE);
#else
	gic_init(GIC_BASE + GICC_OFFSET, GIC_BASE + GICD_OFFSET);
#endif
}

#if CFG_TEE_CORE_NB_CORE > 1
void boot_secondary_init_intc(void)
{
	gic_init_per_cpu();
}
#endif

void plat_console_init(void)
{
#ifdef CFG_PL011
#ifdef CFG_PL011_ONLY_REGISTER
	pl011_register(&console_data, CONSOLE_UART_BASE);
#else
	pl011_init(&console_data, CONSOLE_UART_BASE,
		       CONSOLE_UART_CLK_IN_HZ, CONSOLE_BAUDRATE);
#endif
#endif
	register_serial_console(&console_data.chip);
}

void console_flush(void)
{
	struct serial_chip *cons = &console_data.chip;
	cons->ops->flush(cons);
}
