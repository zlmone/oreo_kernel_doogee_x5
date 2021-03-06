/* Copyright Statement:
* 
* This software/firmware and related documentation ("MediaTek Software") are
* protected under relevant copyright laws. The information contained herein
* is confidential and proprietary to MediaTek Inc. and/or its licensors.
* Without the prior written permission of MediaTek inc. and/or its licensors,
* any reproduction, modification, use or disclosure of MediaTek Software,
* and information contained herein, in whole or in part, shall be strictly prohibited.
*/
/* MediaTek Inc. (C) 2010. All rights reserved.
* 
* BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
* THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
* RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
* AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
* NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
* SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
* SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
* THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
* THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
* CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
* SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
* STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
* CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
* AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
* OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
* MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
* The following software/firmware and/or related documentation ("MediaTek Software")
* have been modified by MediaTek Inc. All revisions are subject to any receiver's
* applicable license agreements with MediaTek Inc.
*/

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#if defined(BUILD_LK)
#include <platform/mt_gpio.h>
#include <platform/mt_pmic.h>
#endif

#if !defined(BUILD_LK)
#include <linux/string.h>
#endif
#include "lcm_drv.h"

#if defined(BUILD_LK)
#define LCM_DEBUG  printf
#define LCM_FUNC_TRACE() printf("huyl [uboot] %s\n",__func__)
#else
#define LCM_DEBUG  printk
#define LCM_FUNC_TRACE() printk("huyl [kernel] %s\n",__func__)
#endif
// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  			(720)
#define FRAME_HEIGHT 			(1280)

#define REGFLAG_DELAY          		(0XFEE)
#define REGFLAG_END_OF_TABLE      	(0xFFF)	// END OF REGISTERS MARKER

#ifndef FALSE
#define FALSE 0
#endif

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = { 0 };

#define SET_RESET_PIN(v)    		(lcm_util.set_reset_pin((v)))

#define UDELAY(n) 					(lcm_util.udelay(n))
#define MDELAY(n) 					(lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	        lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)											lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)


struct LCM_setting_table {
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[64];
};
struct LCM_setting_table2 {
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[64];
};
static void lcm_init_power(void)
{
}


static void lcm_suspend_power(void)
{
}

static void lcm_resume_power(void)
{
}
static struct LCM_setting_table lcm_initialization_setting[] = {
    { 0xFF, 0x04, {0xAA, 0x55, 0x25, 0x01}},
    { 0x6F, 0x01, {0x03}},
    { 0xF4, 0x01, {0x60}},
    { 0x6F, 0x01, {0x06}},
    { 0xF4, 0x01, {0x01}},
    { 0x6F, 0x01, {0x21}},
    { 0xF7, 0x01, {0x01}},
    { 0xFEE, 0x01, {0x00}},
    { 0x6F, 0x01, {0x21}},
    { 0xF7, 0x01, {0x00}},
    { 0xFC, 0x01, {0x08}},
    { 0xFEE, 0x01, {0x00}},
    { 0xFC, 0x01, {0x00}},
    { 0x6F, 0x01, {0x16}},
    { 0xF7, 0x01, {0x10}},
    { 0xFF, 0x04, {0xAA, 0x55, 0x25, 0x00}},
    { 0xFF, 0x04, {0xAA, 0x55, 0xA5, 0x80}},
    { 0x6F, 0x02, {0x11, 0x00}},
    { 0xF7, 0x02, {0x20, 0x00}},
    { 0x6F, 0x01, {0x06}},
    { 0xF7, 0x01, {0xA0}},
    { 0x6F, 0x01, {0x19}},
    { 0xF7, 0x01, {0x12}},
    { 0x6F, 0x01, {0x02}},
    { 0xF7, 0x01, {0x47}},
    { 0x6F, 0x01, {0x17}},
    { 0xF4, 0x01, {0x70}},
    { 0x6F, 0x01, {0x01}},
    { 0xF9, 0x01, {0x46}},
    { 0xF0, 0x05, {0x55, 0xAA, 0x52, 0x08, 0x00}},
    { 0xBD, 0x05, {0x01, 0xA0, 0x10, 0x10, 0x01}},
    { 0xB8, 0x04, {0x00, 0x00, 0x00, 0x00}},
    { 0xBB, 0x02, {0x24, 0x24}},
    { 0xBC, 0x02, {0x00, 0x00}},
    { 0xB6, 0x01, {0x04}},
    { 0xC8, 0x01, {0x80}},
    { 0xD9, 0x02, {0x01, 0x01}},
    { 0xD4, 0x01, {0xC7}},
    { 0xB1, 0x02, {0x60, 0x21}},
    { 0xFF, 0x04, {0xAA, 0x55, 0x25, 0x01}},
    { 0xFC, 0x01, {0x08}},
    { 0xFEE, 0x01, {0x00}},
    { 0xFC, 0x01, {0x00}},
    { 0xFEE, 0x14, {0x00}},
    { 0x6F, 0x01, {0x21}},
    { 0xF7, 0x01, {0x01}},
    { 0xFEE, 0x01, {0x00}},
    { 0x6F, 0x01, {0x21}},
    { 0xF7, 0x01, {0x00}},
    { 0xFF, 0x04, {0xAA, 0x55, 0x25, 0x00}},
    { 0xF0, 0x05, {0x55, 0xAA, 0x52, 0x08, 0x01}},
    { 0xF0, 0x05, {0x55, 0xAA, 0x52, 0x08, 0x01}},
    { 0xB0, 0x02, {0x09, 0x09}},
    { 0xB1, 0x02, {0x09, 0x09}},
    { 0xBC, 0x02, {0x88, 0x00}},
    { 0xBD, 0x02, {0x88, 0x00}},
    { 0xBE, 0x01, {0x65}},
    { 0xCA, 0x01, {0x00}},
    { 0xC0, 0x01, {0x0C}},
    { 0xB5, 0x02, {0x03, 0x03}},
    { 0xB3, 0x02, {0x19, 0x19}},
    { 0xB4, 0x02, {0x19, 0x19}},
    { 0xB9, 0x02, {0x36, 0x36}},
    { 0xBA, 0x02, {0x24, 0x24}},
    { 0xF0, 0x05, {0x55, 0xAA, 0x52, 0x08, 0x02}},
    { 0xEE, 0x01, {0x01}},
    { 0xB0, 0x10, {0x00, 0x0E, 0x00, 0x69, 0x00, 0x96, 0x00, 0xB5, 0x00, 0xD0, 0x00, 0xF4, 0x01, 0x11, 0x01, 0x3F}},
    { 0xB1, 0x10, {0x01, 0x62, 0x01, 0x9C, 0x01, 0xC9, 0x02, 0x0E, 0x02, 0x44, 0x02, 0x48, 0x02, 0x74, 0x02, 0xA9}},
    { 0xB2, 0x10, {0x02, 0xCB, 0x02, 0xF6, 0x03, 0x16, 0x03, 0x3F, 0x03, 0x5C, 0x03, 0x73, 0x03, 0x9B, 0x03, 0x9F}},
    { 0xB3, 0x04, {0x03, 0xD7, 0x03, 0xE8}},
    { 0xB4, 0x10, {0x00, 0x05, 0x00, 0x50, 0x00, 0x8D, 0x00, 0xAD, 0x00, 0xC4, 0x00, 0xEB, 0x01, 0x09, 0x01, 0x39}},
    { 0xB5, 0x10, {0x01, 0x5E, 0x01, 0x97, 0x01, 0xC4, 0x02, 0x08, 0x02, 0x3D, 0x02, 0x3E, 0x02, 0x70, 0x02, 0xA4}},
    { 0xB6, 0x10, {0x02, 0xC5, 0x02, 0xF2, 0x03, 0x11, 0x03, 0x3B, 0x03, 0x58, 0x03, 0x6C, 0x03, 0x96, 0x03, 0xCA}},
    { 0xB7, 0x04, {0x03, 0xF5, 0x03, 0xF8}},
    { 0xB8, 0x10, {0x00, 0x14, 0x00, 0x3B, 0x00, 0x6F, 0x00, 0x8E, 0x00, 0xA9, 0x00, 0xD1, 0x00, 0xF1, 0x01, 0x24}},
    { 0xB9, 0x10, {0x01, 0x4C, 0x01, 0x8A, 0x01, 0xB9, 0x02, 0x03, 0x02, 0x3A, 0x02, 0x3B, 0x02, 0x6E, 0x02, 0xA4}},
    { 0xBA, 0x10, {0x02, 0xC5, 0x02, 0xF4, 0x03, 0x16, 0x03, 0x4D, 0x03, 0x81, 0x03, 0xF9, 0x03, 0xFA, 0x03, 0xFB}},
    { 0xBB, 0x04, {0x03, 0xFD, 0x03, 0xFE}},
    { 0xBC, 0x10, {0x00, 0x0E, 0x00, 0x69, 0x00, 0x96, 0x00, 0xB5, 0x00, 0xD0, 0x00, 0xF4, 0x01, 0x11, 0x01, 0x3F}},
    { 0xBD, 0x10, {0x01, 0x62, 0x01, 0x9C, 0x01, 0xC9, 0x02, 0x0E, 0x02, 0x44, 0x02, 0x48, 0x02, 0x74, 0x02, 0xA9}},
    { 0xBE, 0x10, {0x02, 0xCB, 0x02, 0xF6, 0x03, 0x16, 0x03, 0x3F, 0x03, 0x5C, 0x03, 0x73, 0x03, 0x9B, 0x03, 0x9F}},
    { 0xBF, 0x04, {0x03, 0xD7, 0x03, 0xE8}},
    { 0xC0, 0x10, {0x00, 0x05, 0x00, 0x50, 0x00, 0x8D, 0x00, 0xAD, 0x00, 0xC4, 0x00, 0xEB, 0x01, 0x09, 0x01, 0x39}},
    { 0xC1, 0x10, {0x01, 0x5E, 0x01, 0x97, 0x01, 0xC4, 0x02, 0x08, 0x02, 0x3D, 0x02, 0x3E, 0x02, 0x70, 0x02, 0xA4}},
    { 0xC2, 0x10, {0x02, 0xC5, 0x02, 0xF2, 0x03, 0x11, 0x03, 0x3B, 0x03, 0x58, 0x03, 0x6C, 0x03, 0x96, 0x03, 0xCA}},
    { 0xC3, 0x04, {0x03, 0xF5, 0x03, 0xF8}},
    { 0xC4, 0x10, {0x00, 0x14, 0x00, 0x3B, 0x00, 0x6F, 0x00, 0x8E, 0x00, 0xA9, 0x00, 0xD1, 0x00, 0xF1, 0x01, 0x24}},
    { 0xC5, 0x10, {0x01, 0x4C, 0x01, 0x8A, 0x01, 0xB9, 0x02, 0x03, 0x02, 0x3A, 0x02, 0x3B, 0x02, 0x6E, 0x02, 0xA4}},
    { 0xC6, 0x10, {0x02, 0xC5, 0x02, 0xF4, 0x03, 0x16, 0x03, 0x4D, 0x03, 0x81, 0x03, 0xF9, 0x03, 0xFA, 0x03, 0xFB}},
    { 0xC7, 0x04, {0x03, 0xFD, 0x03, 0xFE}},
    { 0xF0, 0x05, {0x55, 0xAA, 0x52, 0x08, 0x06}},
    { 0xB0, 0x02, {0x31, 0x2E}},
    { 0xB1, 0x02, {0x10, 0x12}},
    { 0xB2, 0x02, {0x16, 0x18}},
    { 0xB3, 0x02, {0x31, 0x31}},
    { 0xB4, 0x02, {0x31, 0x34}},
    { 0xB5, 0x02, {0x34, 0x34}},
    { 0xB6, 0x02, {0x34, 0x34}},
    { 0xB7, 0x02, {0x34, 0x34}},
    { 0xB8, 0x02, {0x33, 0x2D}},
    { 0xB9, 0x02, {0x00, 0x02}},
    { 0xBA, 0x02, {0x03, 0x01}},
    { 0xBB, 0x02, {0x2D, 0x33}},
    { 0xBC, 0x02, {0x34, 0x34}},
    { 0xBD, 0x02, {0x34, 0x34}},
    { 0xBE, 0x02, {0x34, 0x34}},
    { 0xBF, 0x02, {0x34, 0x31}},
    { 0xC0, 0x02, {0x31, 0x31}},
    { 0xC1, 0x02, {0x19, 0x17}},
    { 0xC2, 0x02, {0x13, 0x11}},
    { 0xC3, 0x02, {0x2E, 0x31}},
    { 0xE5, 0x02, {0x31, 0x31}},
    { 0xC4, 0x02, {0x31, 0x2D}},
    { 0xC5, 0x02, {0x19, 0x17}},
    { 0xC6, 0x02, {0x13, 0x11}},
    { 0xC7, 0x02, {0x31, 0x31}},
    { 0xC8, 0x02, {0x31, 0x34}},
    { 0xC9, 0x02, {0x34, 0x34}},
    { 0xCA, 0x02, {0x34, 0x34}},
    { 0xCB, 0x02, {0x34, 0x34}},
    { 0xCC, 0x02, {0x33, 0x2E}},
    { 0xCD, 0x02, {0x03, 0x01}},
    { 0xCE, 0x02, {0x00, 0x02}},
    { 0xCF, 0x02, {0x2E, 0x33}},
    { 0xD0, 0x02, {0x34, 0x34}},
    { 0xD1, 0x02, {0x34, 0x34}},
    { 0xD2, 0x02, {0x34, 0x34}},
    { 0xD3, 0x02, {0x34, 0x31}},
    { 0xD4, 0x02, {0x31, 0x31}},
    { 0xD5, 0x02, {0x10, 0x12}},
    { 0xD6, 0x02, {0x16, 0x18}},
    { 0xD7, 0x02, {0x2D, 0x31}},
    { 0xE6, 0x02, {0x31, 0x31}},
    { 0xD8, 0x05, {0x00, 0x00, 0x00, 0x00, 0x00}},
    { 0xD9, 0x05, {0x00, 0x00, 0x00, 0x00, 0x00}},
    { 0xE7, 0x01, {0x00}},
    { 0xF0, 0x05, {0x55, 0xAA, 0x52, 0x08, 0x05}},
    { 0xED, 0x01, {0x30}},
    { 0xB0, 0x02, {0x17, 0x06}},
    { 0xB8, 0x01, {0x00}},
    { 0xC0, 0x01, {0x0D}},
    { 0xC1, 0x01, {0x0B}},
    { 0xC2, 0x01, {0x00}},
    { 0xC3, 0x01, {0x00}},
    { 0xC4, 0x01, {0x84}},
    { 0xC5, 0x01, {0x82}},
    { 0xC6, 0x01, {0x82}},
    { 0xC7, 0x01, {0x80}},
    { 0xC8, 0x02, {0x0B, 0x20}},
    { 0xC9, 0x02, {0x07, 0x20}},
    { 0xCA, 0x02, {0x01, 0x10}},
    { 0xD1, 0x05, {0x03, 0x05, 0x05, 0x07, 0x00}},
    { 0xD2, 0x05, {0x03, 0x05, 0x09, 0x03, 0x00}},
    { 0xD3, 0x05, {0x00, 0x00, 0x6A, 0x07, 0x10}},
    { 0xD4, 0x05, {0x30, 0x00, 0x6A, 0x07, 0x10}},
    { 0xF0, 0x05, {0x55, 0xAA, 0x52, 0x08, 0x03}},
    { 0xB0, 0x02, {0x00, 0x00}},
    { 0xB1, 0x02, {0x00, 0x00}},
    { 0xB2, 0x05, {0x05, 0x01, 0x13, 0x00, 0x00}},
    { 0xB3, 0x05, {0x05, 0x01, 0x13, 0x00, 0x00}},
    { 0xB4, 0x05, {0x05, 0x01, 0x13, 0x00, 0x00}},
    { 0xB5, 0x05, {0x05, 0x01, 0x13, 0x00, 0x00}},
    { 0xB6, 0x05, {0x02, 0x01, 0x13, 0x00, 0x00}},
    { 0xB7, 0x05, {0x02, 0x01, 0x13, 0x00, 0x00}},
    { 0xB8, 0x05, {0x02, 0x01, 0x13, 0x00, 0x00}},
    { 0xB9, 0x05, {0x02, 0x01, 0x13, 0x00, 0x00}},
    { 0xBA, 0x05, {0x53, 0x01, 0x13, 0x00, 0x00}},
    { 0xBB, 0x05, {0x53, 0x01, 0x13, 0x00, 0x00}},
    { 0xBC, 0x05, {0x53, 0x01, 0x13, 0x00, 0x00}},
    { 0xBD, 0x05, {0x53, 0x01, 0x13, 0x00, 0x00}},
    { 0xC4, 0x01, {0x60}},
    { 0xC5, 0x01, {0x40}},
    { 0xC6, 0x01, {0x64}},
    { 0xC7, 0x01, {0x44}},
    { 0x6F, 0x01, {0x11}},
    { 0xF3, 0x01, {0x01}},
    { 0x11, 0x01, {0x00}},
    { REGFLAG_DELAY, 150, {0x00}},
    { 0x29, 0x01, {0x00}},
    { REGFLAG_DELAY, 50, {0x00}},
    { REGFLAG_END_OF_TABLE, 0x00, {0x00}}
};



static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
    unsigned int i;
    
    for (i = 0; i < count; i++) {
        
        unsigned cmd;
        cmd = table[i].cmd;
        
        switch (cmd) {
            
            case REGFLAG_DELAY:
                MDELAY(table[i].count);
                break;
                
            case REGFLAG_END_OF_TABLE:
                break;
                
            default:
                dsi_set_cmdq_V2(cmd, table[i].count,
                                table[i].para_list, force_update);
        }
        
    }
    
}

// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS * util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}

static void lcm_get_params(LCM_PARAMS * params)
{
    memset(params, 0, sizeof(LCM_PARAMS));
    
    params->type = LCM_TYPE_DSI;
    
    params->width = FRAME_WIDTH;
    params->height = FRAME_HEIGHT;
    
    // enable tearing-free
    params->dbi.te_mode = LCM_DBI_TE_MODE_DISABLED;
    params->dbi.te_edge_polarity = LCM_POLARITY_RISING;
    
    params->dsi.mode = SYNC_EVENT_VDO_MODE;//SYNC_PULSE_VDO_MODE;	//BURST_VDO_MODE;
    
    // DSI
    /* Command mode setting */
    params->dsi.LANE_NUM = LCM_THREE_LANE;//LCM_FOUR_LANE;
    //The following defined the fomat for data coming from LCD engine.
    params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
    params->dsi.data_format.trans_seq = LCM_DSI_TRANS_SEQ_MSB_FIRST;
    params->dsi.data_format.padding = LCM_DSI_PADDING_ON_LSB;
    params->dsi.data_format.format = LCM_DSI_FORMAT_RGB888;
    
    params->dsi.intermediat_buffer_num = 0;	//because DSI/DPI HW design change, this parameters should be 0 when video mode in MT658X; or memory leakage
    
    params->dsi.word_count = 2160;
    params->dsi.vertical_sync_active = 8;
    params->dsi.vertical_backporch = 16;
    params->dsi.PLL_CLOCK = 280;
    params->dsi.lcm_esd_check_table[0].cmd = 10;
    params->dsi.lcm_esd_check_table[0].para_list[0] = -100;
    params->dsi.data_format.format = 2;
    params->dsi.PS = 2;
    params->dsi.noncont_clock_period = 2;
    params->dsi.horizontal_active_pixel = 720;
    params->dsi.vertical_active_line = 1280;
    params->dsi.intermediat_buffer_num = 0;
    params->dsi.vertical_frontporch = 20;
    params->dsi.horizontal_sync_active = 20;
    params->dsi.horizontal_backporch = 80;
    params->dsi.horizontal_frontporch = 80;
    params->dsi.ssc_disable = 1;
    params->dsi.esd_check_enable = 1;
    params->dsi.clk_lp_per_line_enable = 1;
    params->dsi.customization_esd_check_enable = 1;
    params->dsi.noncont_clock = 1;
    params->dsi.lcm_esd_check_table[0].count = 1;
}

static void lcm_init(void)
{
    SET_RESET_PIN(1);
    MDELAY(10);
    SET_RESET_PIN(0);
    MDELAY(20);
    SET_RESET_PIN(1);
    MDELAY(120);
    
    push_table(lcm_initialization_setting,
            sizeof(lcm_initialization_setting) /
            sizeof(struct LCM_setting_table), 1);
}

static void lcm_suspend(void)
{
    unsigned int data_array[16];
    
    data_array[0] = 0x00280500;
    dsi_set_cmdq(data_array, 1, 1);
    MDELAY(20);
    
    data_array[0] = 0x00100500;
    dsi_set_cmdq(data_array, 1, 1);
    MDELAY(150);
    
    SET_RESET_PIN(0);
    MDELAY(20);
}

static void lcm_resume(void)
{
    
    lcm_init();
    //push_table(lcm_sleep_out_setting, sizeof(lcm_sleep_out_setting) /	sizeof(struct LCM_setting_table), 1);
    
}

LCM_DRIVER nt35521_boe50_blj_hd_lcm_drv= {
    .name = "nt35521_boe50_blj_hd",
    .set_util_funcs = lcm_set_util_funcs,
    .get_params     = lcm_get_params,
    .init           = lcm_init,
    .suspend        = lcm_suspend,
    .resume         = lcm_resume,
    .init_power        = lcm_init_power,
    .resume_power = lcm_resume_power,
    .suspend_power = lcm_suspend_power,
};
