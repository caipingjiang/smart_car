/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *�ļ�����  lib_aes.c
 *��  �ߣ�  zoux
 *��  ����  V1.00
 *��  �ڣ�  2017/07/14
 *��  ����  AESģ��⺯��
 *��  ע��  ������ ES8P508xоƬ
 ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
 ***************************************************************/
#ifndef __LIBAES_H__
#define __LIBAES_H__

#include "ES8P508x.h"
#include "type.h"

/* ���ܽ���ģʽѡ��λ */
typedef enum {
	AES_MODE_DECRYPT = 0,	/* ���� */
	AES_MODE_ENCRYPT = 1,	/* ���� */
}AES_TYPE_MODE;

/* ����/���ܿ���λ */
typedef enum {
	AES_DONE_YES = 0,	/* ������� */
	AES_DONE_NO = 1,	/* ���ڼ��� */
}AES_TYPE_DONE;

/* �ӽ������ݽṹ�� */
typedef struct {
	uint32_t DATA[4];
}AES_DATA_TypeDef;

typedef enum {
	AES_IF_IF = 0x80,
}AES_TYPE_IF;

typedef enum {
	AES_IT_IT = 0x40,
}AES_TYPE_IT;

/* �ӽ�����Կ�ṹ�� */
typedef struct {
	uint32_t KEY[4];
}AES_KEY_TypeDef;

/* �ӽ��ܳ�ʼ�ṹ�� */
typedef struct {
	AES_TYPE_MODE MODE;	/* ���ܻ��߽��� */
}AES_InitStruType;

/* �ӽ���ʹ�ܣ���ʼ���� */
#define AES_Enable()	(AES->CON.GO_DONE = 1)
/* ����ģ��ر� */
#define AES_Disable()	(AES->CON.GO_DONE = 0)


/********************* ADCģ�麯������ *********************/
void AES_Init(AES_InitStruType * AES_InitStruct);
void AES_WriteKey(uint32_t *AES_KEY);
void AES_ReadKey(uint32_t * AES_KEY);

void AES_WriteData(uint32_t *AES_DATA);
void AES_ReadData(uint32_t * AES_DATA);

void AES_ITConfig(AES_TYPE_IT AES_IE, TYPE_FUNCEN NewState);
void AES_ClearITPendingBit(void);
FlagStatus AES_GetFlagStatus(AES_TYPE_IF Flag);

AES_TYPE_DONE AES_GetDoneStatus(void);
void AES_Reset(void);

#endif

