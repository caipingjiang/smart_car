/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *�ļ�����  
 *��  ��:  AE 
 *��  ��:  V1.00
 *��  ��:  2017/07/14
 *��  ����  
 *��  ע��  ������ ES8P508оƬ
 ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
 ***************************************************************/
#include "lib_aes.h"

/***************************************************************
��������AES_Init
��  ����AES���ܳ�ʼ������
����ֵ��AES_InitStruct ��ʼ���ṹ��
���ֵ����
����ֵ����
***************************************************************/
void AES_Init(AES_InitStruType * AES_InitStruct)
{


	AES_Reset();

	AES->CON.ENCRYPT = AES_InitStruct->MODE;
	return;
}

/***************************************************************
��������AES_WriteKey
��  ����AESд����Կ����
����ֵ��AES_KEY ��д����Կ
���ֵ����
����ֵ����
***************************************************************/
void AES_WriteKey(uint32_t *AES_KEY)
{
	uint32_t *address = AES_KEY;
	
	AES->KEY3.AES_KEY3 = *address;
	address ++;
	AES->KEY2.AES_KEY2 = *address;
	address ++;
	AES->KEY1.AES_KEY1 = *address;
	address ++;
	AES->KEY0.AES_KEY0 = *address;
}

/***************************************************************
��������AES_ReadKey
��  ����AES������Կ����
����ֵ����
���ֵ��AES_DATA������Կ���λ��
����ֵ����
***************************************************************/
void AES_ReadKey(uint32_t * AES_KEY)
{
	uint32_t *address = AES_KEY;
	
	*address = AES->KEY3.AES_KEY3;
	address ++;
	*address = AES->KEY2.AES_KEY2;
	address ++;
	*address = AES->KEY1.AES_KEY1;
	address ++;
	*address = AES->KEY0.AES_KEY0;
	return;
}

/***************************************************************
��������AES_WriteData
��  ����AESд�����ݺ���
����ֵ��AES_DATA ��д������
���ֵ����
����ֵ����
***************************************************************/
void AES_WriteData(uint32_t *AES_DATA)
{
	uint32_t *address = AES_DATA;
	
	AES->DATA3.AES_DATA3 = *address;
	address ++;
	AES->DATA2.AES_DATA2 = *address;
	address ++;
	AES->DATA1.AES_DATA1 = *address;
	address ++;
	AES->DATA0.AES_DATA0 = *address;
}

/***************************************************************
��������AES_WriteData
��  ����AES�������ݺ���
����ֵ����
���ֵ��AES_DATA�������ݴ��λ��
����ֵ����
***************************************************************/
void AES_ReadData(uint32_t * AES_DATA)
{
	uint32_t *address = AES_DATA;
	
	*address = AES->DATA3.AES_DATA3;
	address ++;
	*address = AES->DATA2.AES_DATA2;
	address ++;
	*address = AES->DATA1.AES_DATA1;
	address ++;
	*address = AES->DATA0.AES_DATA0;
	return;
}

/***************************************************************
��������AES_ITConfig
��  ����AES�ж�ʹ��
����ֵ��AES_IE
	NewState Enable/Disable
���ֵ����
����ֵ����
***************************************************************/
void AES_ITConfig(AES_TYPE_IT AES_IE, TYPE_FUNCEN NewState)
{
	uint32_t Word = AES->CON.Word&0xffffff8e;
	
	if(AES->CON.GO_DONE == 1)
	{
		return;
	}
	
	if (NewState == ENABLE)
		Word |= (uint32_t)AES_IE;
	else
		
		Word &= ~(uint32_t)AES_IE;

	AES->CON.Word = Word;
	return;

}

/***************************************************************
��������AES_GetFlagStatus
��  ����AES����ض��жϱ�־����
����ֵ��IFName 
		AES_IF_IF �ӽ�������ж�
���ֵ����
����ֵ���жϱ�־���
***************************************************************/
FlagStatus AES_GetFlagStatus(AES_TYPE_IF IFName)
{

	if(AES->CON.Word & IFName) {
		return SET;
	}
	return RESET;
}

/***************************************************************
��������AES_ClearITPendingBit
��  ����AES����ض��жϱ�־����
����ֵ��IFName 
		AES_IF_DONE �ӽ�������ж�
���ֵ����
����ֵ����
***************************************************************/
void AES_ClearITPendingBit(void)
{
	/* ���ǵ�IF��GO_DONE��ͬһ��word�У���IF��ֵ���ܻ����һЩ���� 
	 * ����GO_DONE��1ʱ��ȡֵ�����GO_DONE���0������ֵ����ԭ����1�ٶ�����и�ֵ
	 * �ò�����Ҫ���в���
	 */
	
	if(AES->CON.GO_DONE == SET)
	{
		return;
	}

	AES->CON.IF = SET;

	return;
}

/***************************************************************
��������AES_GetDoneStatus
��  ����AES����Ƿ��/�������
����ֵ����
���ֵ����
����ֵ��AES_DONE_NO ����δ���
	AES_DONE_YES δ���ܻ��߼����Ѿ����
***************************************************************/
AES_TYPE_DONE AES_GetDoneStatus(void)
{
	if(AES->CON.GO_DONE == 1)
	{
		return AES_DONE_NO;
	}

	return AES_DONE_YES;
}

/***************************************************************
��������AES_Reset
��  ����AES��λ
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void AES_Reset(void)
{
	AES->DATA0.Word = 0x00000000;
	AES->DATA1.Word = 0x00000000;
	AES->DATA2.Word = 0x00000000;
	AES->DATA3.Word = 0x00000000;

	AES->KEY0.Word = 0x00000000;
	AES->KEY1.Word = 0x00000000;
	AES->KEY2.Word = 0x00000000;
	AES->KEY3.Word = 0x00000000;

	AES->CON.Word = 0x00000000;
}


