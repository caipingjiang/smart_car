/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library ����RT1064DVL6A ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
* 
* ���ļ��� RT1064DVL6A ��Դ���һ����
* 
* RT1064DVL6A ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
* 
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
* 
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
* 
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          zf_common_typedef
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 8.32.4 or MDK 5.33
* ����ƽ̨          RT1064DVL6A
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
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

//=================================================== ���Ͷ��� ===================================================

//#define COMPATIBLE_WITH_OLDER_VERSIONS                                       	// ���ݾɰ濪Դ��ӿ�
#define USE_ZF_TYPEDEF      (1)                                                 // �Ƿ��������Ͷ�������
#if USE_ZF_TYPEDEF
// ������������
// ����ʹ�� stdint.h ������������� �����ͻ ������Բü�
typedef unsigned char       uint8;                                              // �޷���  8 bits
typedef unsigned short int  uint16;                                             // �޷��� 16 bits
typedef unsigned int        uint32;                                             // �޷��� 32 bits
typedef unsigned long long  uint64;                                             // �޷��� 64 bits

typedef signed char         int8;                                               // �з���  8 bits
typedef signed short int    int16;                                              // �з��� 16 bits
typedef signed int          int32;                                              // �з��� 32 bits
typedef signed long long    int64;                                              // �з��� 64 bits

typedef volatile uint8      vuint8;                                             // �ױ������� �޷���  8 bits
typedef volatile uint16     vuint16;                                            // �ױ������� �޷��� 16 bits
typedef volatile uint32     vuint32;                                            // �ױ������� �޷��� 32 bits
typedef volatile uint64     vuint64;                                            // �ױ������� �޷��� 64 bits

typedef volatile int8       vint8;                                              // �ױ������� �з���  8 bits
typedef volatile int16      vint16;                                             // �ױ������� �з��� 16 bits
typedef volatile int32      vint32;                                             // �ױ������� �з��� 32 bits
typedef volatile int64      vint64;                                             // �ױ������� �з��� 64 bits

#define ZF_ENABLE       (1)
#define ZF_DISABLE      (0)

#define ZF_TRUE         (1)
#define ZF_FALSE        (0)
#endif
//=================================================== ���Ͷ��� ===================================================


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
	// ���彫�������ITCM�ķ�ʽ
    #define AT_ITCM_SECTION_INIT(var) var @"ITCM_NonCacheable.init"
	// ���彫������߱�������DTCM�ķ�ʽ
	#if ((!(defined(FSL_FEATURE_HAS_NO_NONCACHEABLE_SECTION) && FSL_FEATURE_HAS_NO_NONCACHEABLE_SECTION)) && defined(FSL_FEATURE_L1ICACHE_LINESIZE_BYTE))
        #define AT_DTCM_SECTION(var) var @"NonCacheable"
        #define AT_DTCM_SECTION_ALIGN(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"NonCacheable"
        #define AT_DTCM_SECTION_INIT(var) var @"NonCacheable.init"
        #define AT_DTCM_SECTION_ALIGN_INIT(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"NonCacheable.init"
    #endif 
	// ���彫������߱�������OCRAM�ķ�ʽ
	#define AT_OCRAM_SECTION(var) var @"OCRAM_CACHE"
    #define AT_OCRAM_SECTION_ALIGN(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"OCRAM_CACHE"
    #define AT_OCRAM_SECTION_INIT(var) var @"OCRAM_CACHE.init"
    #define AT_OCRAM_SECTION_ALIGN_INIT(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"OCRAM_CACHE.init"
	// ���彫������߱�������SDRAM�ķ�ʽ
	#define AT_SDRAM_SECTION(var) var @"SDRAM_CACHE"
    #define AT_SDRAM_SECTION_ALIGN(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"SDRAM_CACHE"
    #define AT_SDRAM_SECTION_INIT(var) var @"SDRAM_CACHE.init"
    #define AT_SDRAM_SECTION_ALIGN_INIT(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"SDRAM_CACHE.init"
	// ���彫������߱�������SDRAM_NONCACHE�ķ�ʽ
	#define AT_SDRAM_NONCACHE_SECTION(var) var @"SDRAM_NonCacheable"
    #define AT_SDRAM_NONCACHE_SECTION_ALIGN(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"SDRAM_NonCacheable"
    #define AT_SDRAM_NONCACHE_SECTION_INIT(var) var @"SDRAM_NonCacheable.init"
    #define AT_SDRAM_NONCACHE_SECTION_ALIGN_INIT(var, alignbytes) SDK_PRAGMA(data_alignment = alignbytes) var @"SDRAM_NonCacheable.init"
	
	
#elif(defined(__CC_ARM) || defined(__ARMCC_VERSION))
	// ���彫�������ITCM�ķ�ʽ
    #define AT_ITCM_SECTION_INIT(var) __attribute__((section("ITCM_NonCacheable.init"))) var
	// ���彫������߱�������DTCM�ķ�ʽ
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
	
	// ���彫������߱�������OCRAM�ķ�ʽ
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
	
	
	// ���彫������߱�������SDRAM�ķ�ʽ
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
	// ���彫������߱�������SDRAM_NONCACHE�ķ�ʽ
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
