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

#include <compiler.h>
#include <kernel/pseudo_ta.h>
#include <kernel/panic.h>
#include <kernel/thread.h>
#include <mm/core_memprot.h>
#include <pta_invoke_tests.h>
#include <string.h>
#include <stdio.h>
#include <tee/cache.h>
#include <tee_api_defines.h>
#include <tee_api_types.h>
#include <trace.h>
#include <types_ext.h>

#define PTA_NAME        "pta_ptt.pta"

#define PTA_PTT_UUID { 0x82DA116D, 0xC09C, 0x737E, \
         { 0xF1, 0x90, 0x99, 0xE1, 0x03, 0x87, 0x31, 0xD5} } 

/* The TAFs ID implemented in this TA */
#define PTA_PTT_PBF_VER         100
#define PTA_PTT_OPTEE_VER       200
#define PTA_PTT_COMPILE_TIME    201
#define PTA_PTT_PHYTIUM_VER     202

#define PTA_PTT_BUF_MAX         256

extern const char core_v_str[];
extern void thread_arm_smc_call(struct thread_smc_args*, struct thread_smc_args*);

/*
 * Trusted Application Entry Points
 */
static TEE_Result create_ta(void)
{
    DMSG("create entry point for pseudo TA \"%s\"", PTA_NAME);
    return TEE_SUCCESS;
}

static void destroy_ta(void)
{
    DMSG("destroy entry point for pseudo ta \"%s\"", PTA_NAME);
}

static TEE_Result open_session(uint32_t nParamTypes __unused,
        TEE_Param pParams[TEE_NUM_PARAMS] __unused,
        void **ppSessionContext __unused)
{
    DMSG("open entry point for pseudo ta \"%s\"", PTA_NAME);
    return TEE_SUCCESS;
}

static void close_session(void *pSessionContext __unused)
{
    DMSG("close entry point for pseudo ta \"%s\"", PTA_NAME);
}

static TEE_Result invoke_command(void *pSessionContext __unused,
        uint32_t nCommandID, uint32_t __maybe_unused nParamTypes,
        TEE_Param __maybe_unused sParams[TEE_NUM_PARAMS])
{
    struct thread_smc_args smc_in = {0};
    struct thread_smc_args smc_out = {0};
    char *pBuf = NULL;

    FMSG("command entry point for pseudo ta \"%s\"", PTA_NAME);

    /*
     * p[0].memref.buffer = output buffer
     */
    if (TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_OUTPUT,
                TEE_PARAM_TYPE_NONE,
                TEE_PARAM_TYPE_NONE,
                TEE_PARAM_TYPE_NONE) != nParamTypes) {
        return TEE_ERROR_BAD_PARAMETERS;
    }
    pBuf = sParams[0].memref.buffer;

    switch (nCommandID)
    {
        case PTA_PTT_PBF_VER:
            smc_in.a0 = 0x82000001;
            thread_arm_smc_call(&smc_in, &smc_out);
            snprintf(pBuf, PTA_PTT_BUF_MAX, "PBF version : v%lx.%lx", ((smc_out.a0 >> 16) & 0xFFFF), (smc_out.a0 & 0xFFFF));
            return TEE_SUCCESS;

        case PTA_PTT_OPTEE_VER:
            snprintf(pBuf, PTA_PTT_BUF_MAX, "OP-TEE base version : %d.%d", CFG_OPTEE_REVISION_MAJOR, CFG_OPTEE_REVISION_MINOR);
            return TEE_SUCCESS;

        case PTA_PTT_COMPILE_TIME:
            snprintf(pBuf, PTA_PTT_BUF_MAX, "%s", core_v_str);
            return TEE_SUCCESS;

        case PTA_PTT_PHYTIUM_VER:
            snprintf(pBuf, PTA_PTT_BUF_MAX, "Phytium-optee verison : v3.2");
            return TEE_SUCCESS;

        default:
            return TEE_ERROR_BAD_PARAMETERS;
    }
}

pseudo_ta_register(.uuid = PTA_PTT_UUID, .name =  PTA_NAME,
           .flags = PTA_DEFAULT_FLAGS | TA_FLAG_SECURE_DATA_PATH |
                TA_FLAG_CONCURRENT,
           .create_entry_point = create_ta,
           .destroy_entry_point = destroy_ta,
           .open_session_entry_point = open_session,
           .close_session_entry_point = close_session,
           .invoke_command_entry_point = invoke_command);
