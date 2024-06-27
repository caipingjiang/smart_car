#ifndef _vofa_h_
#define _vofa_h_

#define CH_COUNT    3               //自定义通道数量


// type： 'd'-->整数 , 'f'-->浮点数  
typedef struct 
{
    int int_data;
    float float_data;  
    char type;              //标记字段，用以标记数据类型
} FireWater_Struct;

typedef struct 
{
    float data[CH_COUNT];	//JustFloat格式只能发送float类型的数据
    unsigned char tail[4];	//帧尾
} JustFloat_Struct;

extern FireWater_Struct FW_Data[CH_COUNT];
extern JustFloat_Struct JF_Data;
void FireWater_Send();
void JustFloat_Send();

#endif