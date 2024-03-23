#include "zf_common_headfile.h"
#include "vofa.h"

//FireWater��������
//ʹ��ʾ����
// int8    data_1 = -13;
// uint16  data_2 = 234;
// float   data_3 = 3.4;
// FW_Data[0].type = 'd';
// FW_Data[1].type = 'd';
// FW_Data[2].type = 'f';
// FW_Data[0].int_data   = data_1;
// FW_Data[1].int_data   = data_2;
// FW_Data[2].float_data = data_3;
//����FW_Data[x].type���Բ�������ѭ�����ж���
// void FireWater_Send();

// FireWaterע�����
// ��Ҫ���˸���������(.type)��ֵ ,  .int_data �� .float_dataҪ��.typeƥ��!
// ��Ҫ���˸���������(.type)��ֵ ,  .int_data �� .float_dataҪ��.typeƥ��!
// ��Ҫ���˸���������(.type)��ֵ ,  .int_data �� .float_dataҪ��.typeƥ��!
static char data_str[12];
FireWater_Struct FW_Data[CH_COUNT] = {[0 ... CH_COUNT-1] = {0, 0, 'd'}};//�����ʼ���﷨��������0��CH_COUNT-1��Ԫ�س�ʼ��Ϊ0, 0.0, 'd'}

void FireWater_Send()
{
    for(uint8 i = 0; i < CH_COUNT; i++)
    {
        switch (FW_Data[i].type) 
        {
            case 'd':
                snprintf(data_str, sizeof(data_str), "%d", FW_Data[i].int_data);
                break;
            case 'f':
                snprintf(data_str, sizeof(data_str), "%f", FW_Data[i].float_data);
                break;			
            default:
                wireless_uart_send_string("error: Unknown type!\n");
                continue;
        }
        if(i != CH_COUNT-1)
        {
            wireless_uart_send_string(data_str);
            wireless_uart_send_string(",");
        }
        else
        {
            wireless_uart_send_string(data_str);
            wireless_uart_send_string("\n");
        }
    }
}

//JustFloat��������
//ʹ��ʾ����
//JF_Data.data[0] = Kp_T;
//JF_Data.data[1] = Kd_T;
//JF_Data.data[2] = 0.45;
//JF_Data.data[3] = -3.36;
//JustFloat_Send();

JustFloat_Struct JF_Data;

void JustFloat_Send()
{
    JF_Data.tail[0] = 0x00;
	JF_Data.tail[1] = 0x00;
	JF_Data.tail[2] = 0x80;
	JF_Data.tail[3] = 0x7f;
    wireless_uart_send_buffer((const uint8*)JF_Data.data, sizeof(float) * CH_COUNT);
 	wireless_uart_send_buffer((const uint8*)JF_Data.tail, 4);
}

//����ͼ��
#define		IMG_ID			0
#define 	IMG_SIZE		188*120
#define 	IMG_WIDTH		188	
#define 	IMG_HEIGHT		120
#define		IMG_FORMAT		24
// �ȷ���ǰ��֡
int preFrame[7] = {
    IMG_ID, 
    IMG_SIZE, 
    IMG_WIDTH, 
    IMG_HEIGHT, 
    IMG_FORMAT, 
    0x7F800000, 
    0x7F800000
};

//ʹ��ʾ��Image_Send(&mt9v03x_image[0][0], MT9V03X_IMAGE_SIZE);
void Image_Send(const uint8 *image_addr, uint32 image_size)
{
    wireless_uart_send_buffer((const uint8*)preFrame, sizeof(int) * 7);
    wireless_uart_send_buffer((uint8 *)image_addr, image_size);
}