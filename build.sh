#! /bin/bash

make -j ARCH=arm  CROSS_COMPILE64=aarch64-openeuler-linux-gnu- CFG_ARM64_core=y CFG_USER_TA_TARGETS=ta_arm64 PLATFORM_FLAVOR=rk3399 PLATFORM=rockchip all

