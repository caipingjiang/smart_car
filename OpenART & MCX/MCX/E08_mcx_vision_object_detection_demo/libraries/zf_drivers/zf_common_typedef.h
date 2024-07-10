/*********************************************************************************************************************
* MCX Vision Opensourec Library ����MCX Vision ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2024 SEEKFREE ��ɿƼ�
* 
* ���ļ��� MCX Vision ��Դ���һ����
* 
* MCX Vision ��Դ�� ��������
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
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          zf_common_typedef
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MDK 5.38a
* ����ƽ̨          MCX Vision
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2024-04-21        ZSY            first version
********************************************************************************************************************/
#ifndef _zf_common_typedef_h_
#define _zf_common_typedef_h_

#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdarg.h"
#include "string.h"
#include "stdlib.h"
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

typedef struct {                                
  __IO uint32_t     EZHB_BOOT;                           
  __IO uint32_t     EZHB_CTRL;                           
  __I  uint32_t     reserve1;                           
  __I  uint32_t     EZHB_SP;                             
  __IO uint32_t     reserve2;                     
  __IO uint32_t     reserve3;                
  __IO uint32_t     reserve4;                 
  __IO uint32_t     reserve5;                 
  __IO uint32_t     EZHB_ARM2EZH;                        
  __IO uint32_t     reserve6;                        
  __IO uint32_t     reserve7;                     
 } EZH_ARCH_B_CON_Type;

typedef struct _smartdma_camera_params
{
	uint32_t *smartdma_stack;      
	uint32_t *p_buffer;            
	uint32_t *p_stripe_index;      
	uint32_t *p_buffer_ping_pong;  
} smartdma_camera_param_ts;

typedef struct _QEI_Para{
    uint32_t *coprocessor_stack;
    uint32_t *p_camera_buffer;
    uint32_t *p_AI_buffer;
    uint32_t *p_coord_index;
} QEI_Para;


#define     func_abs(x)             ((x) >= 0 ? (x): -(x))
#define     func_limit_ab(x, a, b)  ((x) < (a) ? (a) : ((x) > (b) ? (b) : (x)))
#endif
