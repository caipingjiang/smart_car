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
* �ļ�����          zf_model_process
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
#ifndef _zf_model_process_h_
#define _zf_model_process_h_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */ 
#include "zf_common_headfile.h"

    
#define IS_SHOW_SCC8660             (true)      // �Ƿ�������Ļ��ʾ
#define IS_UART_OUTPUT_ODRESULT     (true)      // �Ƿ��������ش������Ŀ��������Ϣ

void ezh_copy_slice_to_model_input(uint32_t idx, uint32_t cam_slice_buffer, uint32_t cam_slice_width, uint32_t cam_slice_height, uint32_t max_idx);
void zf_model_init(void);
void zf_model_run(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif
