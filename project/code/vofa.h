#ifndef _vofa_h_
#define _vofa_h_

#define CH_COUNT    5               //�Զ���ͨ������


// type�� 'd'-->���� , 'f'-->������  
typedef struct 
{
    int int_data;
    float float_data;  
    char type;              //����ֶΣ����Ա����������
} FireWater_Struct;

typedef struct 
{
    float data[CH_COUNT];	//JustFloat��ʽֻ�ܷ���float���͵�����
    unsigned char tail[4];	//֡β
} JustFloat_Struct;

extern FireWater_Struct FW_Data[CH_COUNT];
extern JustFloat_Struct JF_Data;
void FireWater_Send();
void JustFloat_Send();

#endif