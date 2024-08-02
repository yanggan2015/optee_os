include core/arch/arm/cpu/cortex-armv8-0.mk

$(call force,CFG_GIC,y)
$(call force,CFG_PL011,y)
$(call force,CFG_ARM_GICV3,y)
$(call force,CFG_CORE_CLUSTER_SHIFT,0)
$(call force,CFG_TEE_CORE_NB_CORE,4)
$(call force,CFG_SECURE_TIME_SOURCE_CNTPCT,y)
$(call force,CFG_WITH_ARM_TRUSTED_FW,y)

ifeq ($(CFG_ARM64_core),y)
$(call force,CFG_WITH_LPAE,y)
else  #CFG_ARM64_core
$(call force,CFG_ARM32_core,y)
endif #!CFG_ARM64_core

# 2 * CFG_TEE_CORE_NB_CORE
CFG_NUM_THREADS ?= 8

CFG_TZDRAM_START ?= 0xFC000000
CFG_TZDRAM_SIZE  ?= 0x02200000
CFG_SHMEM_START  ?= 0xFE200000
CFG_SHMEM_SIZE   ?= 0x00C00000

CFG_TEE_RAM_VA_SIZE ?= 0x400000
CFG_CORE_HEAP_SIZE  ?= 196608
