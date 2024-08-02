# Default board
PLATFORM_FLAVOR ?= e2000qdemo

# Disable core ASLR for two reasons:
# 1. There is no source for ALSR seed, as ATF does not provide a
#    DTB to OP-TEE. Hardware RNG is also not currently supported.
# 2. OP-TEE does not boot with enabled CFG_CORE_ASLR.
$(call force,CFG_CORE_ASLR,n)
$(call force,CFG_CORE_DYN_SHM,y)
$(call force,CFG_CORE_ARM64_PA_BITS,44)
$(call force,CFG_ENCRYPT_TA,y)
$(call force,CFG_INSECURE,y)

$(call force,CFG_PTA_PTT,y)

include $(platform-dir)/config/$(PLATFORM_FLAVOR)/board.mk
