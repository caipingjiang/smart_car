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
* �ļ�����          seekfree_assistant_interface
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 8.32.4 or MDK 5.33
* ����ƽ̨          RT1064DVL6A
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����             ����             ��ע
* 2024-1-11        SeekFree         first version
********************************************************************************************************************/

#ifndef _seekfree_assistant_interface_h_
#define _seekfree_assistant_interface_h_



// ���ݷ����豸ö��
typedef enum
{
    SEEKFREE_ASSISTANT_DEBUG_UART,      // ���Դ���    ʹ�õĴ�����DEBUG_UART_INDEX�궨��ָ��
    SEEKFREE_ASSISTANT_WIRELESS_UART,   // ����ת����
    SEEKFREE_ASSISTANT_CH9141,          // CH9141����
    SEEKFREE_ASSISTANT_WIFI_UART,       // WIFIת����
    SEEKFREE_ASSISTANT_WIFI_SPI,        // ����WIFI SPI
    SEEKFREE_ASSISTANT_CUSTOM,          // �Զ���ͨѶ��ʽ ��Ҫ����seekfree_assistant_transfer��seekfree_assistant_receive����
}seekfree_assistant_transfer_device_enum;


void    seekfree_assistant_interface_init   (seekfree_assistant_transfer_device_enum transfer_device);



#endif
