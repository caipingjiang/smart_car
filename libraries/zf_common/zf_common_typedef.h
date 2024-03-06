/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library 即（RT1064DVL6A 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 RT1064DVL6A 开源库的一部分
* 
* RT1064DVL6A 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
* 
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
* 
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
* 
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          zf_common_typedef
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.33
* 适用平台          RT1064DVL6A
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/

#ifndef _zf_common_typedef_h_
#define _zf_common_typedef_h_

#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdarg.h"
#include "string.h"
#include "stdlib.h"
#include "fsl_common.h"
#include "fsl_common_arm.h"

//=================================================== 类型定义 ===================================================

//#define COMPATIBLE_WITH_OLDER_VERSIONS                                       	// 兼容旧版开源库接口
#define USE_ZF_TYPEDEF      (1)                                                 // 是否启用类型定义申明
#if USE_ZF_TYPEDEF
// 数据类型声明
// 尽量使用 stdint.h 定义的类型名称 避免冲突 这里可以裁剪
typedef unsigned char       uint8;                                              // 无符号  8 bits
typedef unsigned short int  uint16;                                             // 无符号 16 bits
typedef unsigned int        uint32;                                             // 无符号 32 bits
typedef unsigned long long  uint64;                                             // 无符号 64 bits

typedef signed char         int8;                                               // 有符号  8 bits
typedef signed short int    int16;                                              // 有符号 16 bits
typedef signed int          int32;                                              // 有符号 32 bits
typedef signed long long    int64;                                              // 有符号 64 bits

typedef volatile uint8      vuint8;                                             // 易变性修饰 无符号  8 bits
typedef volatile uint16     vuint16;                                            // 易变性修饰 无符号 16 bits
typedef volatile uint32     vuint32;                                            // 易变性修饰 无符号 32 bits
typedef volatile uint64     vuint64;                                            // 易变性修饰 无符号 64 bits

typedef volatile int8       vint8;                                              // 易变性修饰 有符号  8 bits
typedef volatile int16      vint16;                                             // 易变性修饰 有符号 16 bits
typedef volatile int32      vint32;                                             // 易变性修饰 有符号 32 bits
typedef volatile int64      vint64;                                             // 易变性修饰 有符号 64 bits

#define ZF_ENABLE       (1)
#define ZF_DISABLE      (0)

#define ZF_TRUE         (1)
#define ZF_FALSE        (0)
#endif
//=================================================== 类型定义 ===================================================


// Compiler Related Definitions 
#ifdef __CC_ARM                         // ARM Compiler 
    #define ALIGN(n)                    __attribute__((aligned(n)))
#elif defined (__IAR_SYSTEMS_ICC__)     // for IAR Compiler 
    #define PRAGMA(x)                   _Pragma(#x)
    #define ALIGN(n)                    PRAGMA(data_alignment=n)
#elif defined (__GNUC__)                // GNU GCC Compiler 
    #define ALIGN(n)                    __attribute__((aligned(n)))
#endif // Compiler Related Definitions 

#if (defined(__ICCARM__))
	// 定义将代码放在ITCM的方式
    #define AT_ITCM_SECTION_INIT(var) var @"ITCM_NonCacheable.init"
	// 定义将代码或者变量放在DTCM的方式
	#if ((!(defined(FSL_FEATURE_HAS_NO_NONCACHEABLE_SECTION) && FSL_FEATURE_HAS_NO_NONCACHEABLE_SECTION)) && defined(FSL_FEATURE_L1ICACHE_LINESIZE_BYTE))
        #define AT_DTCM_SECTION(var) var @"NonCacheable"
        #define AT_DTCM_SECTION_ALIGN(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"NonCacheable"
        #define AT_DTCM_SECTION_INIT(var) var @"NonCacheable.init"
        #define AT_DTCM_SECTION_ALIGN_INIT(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"NonCacheable.init"
    #endif 
	// 定义将代码或者变量放在OCRAM的方式
	#define AT_OCRAM_SECTION(var) var @"OCRAM_CACHE"
    #define AT_OCRAM_SECTION_ALIGN(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"OCRAM_CACHE"
    #define AT_OCRAM_SECTION_INIT(var) var @"OCRAM_CACHE.init"
    #define AT_OCRAM_SECTION_ALIGN_INIT(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"OCRAM_CACHE.init"
	// 定义将代码或者变量放在SDRAM的方式
	#define AT_SDRAM_SECTION(var) var @"SDRAM_CACHE"
    #define AT_SDRAM_SECTION_ALIGN(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"SDRAM_CACHE"
    #define AT_SDRAM_SECTION_INIT(var) var @"SDRAM_CACHE.init"
    #define AT_SDRAM_SECTION_ALIGN_INIT(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"SDRAM_CACHE.init"
	// 定义将代码或者变量放在SDRAM_NONCACHE的方式
	#define AT_SDRAM_NONCACHE_SECTION(var) var @"SDRAM_NonCacheable"
    #define AT_SDRAM_NONCACHE_SECTION_ALIGN(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"SDRAM_NonCacheable"
    #define AT_SDRAM_NONCACHE_SECTION_INIT(var) var @"SDRAM_NonCacheable.init"
    #define AT_SDRAM_NONCACHE_SECTION_ALIGN_INIT(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"SDRAM_NonCacheable.init"
	
	
#elif(defined(__CC_ARM) || defined(__ARMCC_VERSION))
	// 定义将代码放在ITCM的方式
    #define AT_ITCM_SECTION_INIT(var) __attribute__((section("ITCM_NonCacheable.init"))) var
	// 定义将代码或者变量放在DTCM的方式
	#if ((!(defined(FSL_FEATURE_HAS_NO_NONCACHEABLE_SECTION) && FSL_FEATURE_HAS_NO_NONCACHEABLE_SECTION)) && defined(FSL_FEATURE_L1ICACHE_LINESIZE_BYTE))
        #if(defined(__CC_ARM))
			#define AT_DTCM_SECTION(var) __attribute__((section("NonCacheable"), zero_init)) var
			#define AT_DTCM_SECTION_ALIGN(var, alignbytes) \
				__attribute__((section("NonCacheable"), zero_init)) __attribute__((aligned(alignbytes))) var
		#else
			#define AT_DTCM_SECTION(var) __attribute__((section(".bss.NonCacheable"))) var
			#define AT_DTCM_SECTION_ALIGN(var, alignbytes) \
				__attribute__((section(".bss.NonCacheable"))) __attribute__((aligned(alignbytes))) var
		#endif

        #define AT_DTCM_SECTION_INIT(var) __attribute__((section("NonCacheable.init"))) var
        #define AT_DTCM_SECTION_ALIGN_INIT(var, alignbytes) \
            __attribute__((section("NonCacheable.init"))) __attribute__((aligned(alignbytes))) var
    #endif
	
	// 定义将代码或者变量放在OCRAM的方式
    #if(defined(__CC_ARM))
		#define AT_OCRAM_SECTION(var) __attribute__((section("OCRAM_CACHE"), zero_init)) var
		#define AT_OCRAM_SECTION_ALIGN(var, alignbytes) \
			__attribute__((section("OCRAM_CACHE"), zero_init)) __attribute__((aligned(alignbytes))) var
	#else
		#define AT_OCRAM_SECTION(var) __attribute__((section(".bss.OCRAM_CACHE"))) var
		#define AT_OCRAM_SECTION_ALIGN(var, alignbytes) \
			__attribute__((section(".bss.OCRAM_CACHE"))) __attribute__((aligned(alignbytes))) var
	#endif

    #define AT_OCRAM_SECTION_INIT(var) __attribute__((section("OCRAM_CACHE.init"))) var
    #define AT_OCRAM_SECTION_ALIGN_INIT(var, alignbytes) \
        __attribute__((section("OCRAM_CACHE.init"))) __attribute__((aligned(alignbytes))) var
	
	
	// 定义将代码或者变量放在SDRAM的方式
	#if(defined(__CC_ARM))
		#define AT_SDRAM_SECTION(var) __attribute__((section("SDRAM_CACHE"), zero_init)) var
		#define AT_SDRAM_SECTION_ALIGN(var, alignbytes) \
			__attribute__((section("SDRAM_CACHE"), zero_init)) __attribute__((aligned(alignbytes))) var
	#else
		#define AT_SDRAM_SECTION(var) __attribute__((section(".bss.SDRAM_CACHE"))) var
		#define AT_SDRAM_SECTION_ALIGN(var, alignbytes) \
			__attribute__((section(".bss.SDRAM_CACHE"))) __attribute__((aligned(alignbytes))) var
	#endif
	
    #define AT_SDRAM_SECTION_INIT(var) __attribute__((section("SDRAM_CACHE.init"))) var
    #define AT_SDRAM_SECTION_ALIGN_INIT(var, alignbytes) \
        __attribute__((section("SDRAM_CACHE.init"))) __attribute__((aligned(alignbytes))) var
	// 定义将代码或者变量放在SDRAM_NONCACHE的方式
	#if(defined(__CC_ARM))
		#define AT_SDRAM_NONCACHE_SECTION(var) __attribute__((section("SDRAM_NonCacheable"), zero_init)) var
		#define AT_SDRAM_NONCACHE_SECTION_ALIGN(var, alignbytes) \
			__attribute__((section("SDRAM_NonCacheable"), zero_init)) __attribute__((aligned(alignbytes))) var
	#else
		#define AT_SDRAM_NONCACHE_SECTION(var) __attribute__((section(".bss.SDRAM_NonCacheable"))) var
		#define AT_SDRAM_NONCACHE_SECTION_ALIGN(var, alignbytes) \
			__attribute__((section(".bss.SDRAM_NonCacheable"))) __attribute__((aligned(alignbytes))) var
	#endif
	
    #define AT_SDRAM_NONCACHE_SECTION_INIT(var) __attribute__((section("SDRAM_NonCacheable.init"))) var
    #define AT_SDRAM_NONCACHE_SECTION_ALIGN_INIT(var, alignbytes) \
        __attribute__((section("SDRAM_NonCacheable.init"))) __attribute__((aligned(alignbytes))) var
	
#endif

#endif
