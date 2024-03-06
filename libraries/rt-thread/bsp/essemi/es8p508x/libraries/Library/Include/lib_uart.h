/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *�ļ����� lib_uart.h
 *�� �ߣ� Liut
 *�� ���� V1.00
 *�� �ڣ� 2017/07/14
 *�� ���� UARTģ��⺯��ͷ�ļ�
 *�� ע�� ������ ES8P508xоƬ
 ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
 ***************************************************************/
#ifndef __LIBUART_H__
#define __LIBUART_H__

#include "ES8P508x.h"
#include "type.h"
#include "system_ES8P508x.h"

/* ����ֹ֡ͣλѡ�� */
typedef enum
{
    UART_StopBits_1 = 0x0 , //����ֹ֡ͣλ��1λ
    UART_StopBits_2 = 0x1 , //����ֹ֡ͣλ��2λ
}UART_TYPE_TXFS;

/* ���ݸ�ʽ */
typedef enum
{
    UART_DataMode_7 = 0x0 ,    //���ݸ�ʽ:7λ����
    UART_DataMode_8 = 0x1 ,    //���ݸ�ʽ:8λ����
    UART_DataMode_9 = 0x2 ,    //���ݸ�ʽ:9λ����
    UART_DataMode_7Odd = 0x4 , //���ݸ�ʽ:7λ����+��У��
    UART_DataMode_7Even = 0x5 , //���ݸ�ʽ:7λ����+żУ��
    UART_DataMode_8Odd = 0x6 , //���ݸ�ʽ:8λ����+��У��
    UART_DataMode_8Even = 0x7 , //���ݸ�ʽ:8λ����+żУ��
}UART_TYPE_DATAMOD;

/* �˿ڼ��� */
typedef enum
{
    UART_Polar_Normal = 0x0 ,   //���Ͷ˿ڼ���:����
    UART_Polar_Opposite = 0x1 , //���Ͷ˿ڼ���:����
}UART_TYPE_RTXP;

/* �����ʷ�����ʱ��ѡ�� */
typedef enum
{
    UART_Clock_1 = 0x1 , //�����ʷ�����ʱ��:PCLK
    UART_Clock_2 = 0x2 , //�����ʷ�����ʱ��:PCLK/2
    UART_Clock_4 = 0x3 , //�����ʷ�����ʱ��:PCLK/4
	  UART_Clock_8 = 0x4 , //�����ʷ�����ʱ��:PCLK/8
	  
}UART_TYPE_BCS;

/* UART��ʼ�����ýṹ�嶨�� */
typedef struct
{
    UART_TYPE_TXFS  UART_StopBits;  //����ֹ֡ͣλѡ��
    UART_TYPE_DATAMOD  UART_TxMode; //��������֡��ʽ
    UART_TYPE_RTXP  UART_TxPolar;   //���Ͷ˿ڼ���
    UART_TYPE_DATAMOD  UART_RxMode; //��������֡��ʽ
    UART_TYPE_RTXP  UART_RxPolar;   //���ն˿ڼ���
    uint32_t  UART_BaudRate;        //���䲨����
    UART_TYPE_BCS  UART_ClockSet;   //�����ʷ�����ʱ��ѡ��
}UART_InitStruType;

/* �ж�ѡ�� */
typedef enum
{
    UART_IT_TB = 0x0001 ,
    UART_IT_RB = 0x0002 ,
    UART_IT_RO = 0x0004 ,
    UART_IT_FE = 0x0008 ,
    UART_IT_PE = 0x0010 ,
    UART_IT_TBWE = 0x0020 ,
    UART_IT_TXIDLE = 0x1000 ,
    UART_IT_RXIDLE = 0x2000 ,
}UART_TYPE_IT;

/* ��־λ */
typedef enum
{
	  UART_FLAG_TB = 0x0001 ,
    UART_FLAG_RB = 0x0002 ,
    UART_FLAG_RO = 0x0004 ,
    UART_FLAG_FE = 0x0008 ,
    UART_FLAG_PE = 0x0010 ,
    UART_FLAG_TBWE = 0x0020 ,
    UART_FLAG_TXIDLE = 0x1000 ,
    UART_FLAG_RXIDLE = 0x2000 ,
}UART_TYPE_FLAG;

/*  ����жϱ�־λ */
typedef enum
{
    UART_Clr_RO = 0x0004 ,
    UART_Clr_FE = 0x0008 ,
    UART_Clr_PE = 0x0010 ,
    UART_Clr_TBWE = 0x0020 ,
}UART_CLR_IF;

/* ���͡������ж�ģʽ */
typedef enum
{
    UART_TRBIM_Byte = 0x0 ,     //�ж�:�ֽ�
    UART_TRBIM_HalfWord = 0x1 , //�ж�:����
    UART_TRBIM_Word = 0x2 ,     //�ж�:��
}UART_TYPE_TRBIM;

/*************UARTģ��궨��************/
/* ����ʹ�ܿ��� */
#define UART0_TxEnable() (UART0->CON.TXEN = 1)
#define UART1_TxEnable() (UART1->CON.TXEN = 1)
#define UART2_TxEnable() (UART2->CON.TXEN = 1)
#define UART3_TxEnable() (UART3->CON.TXEN = 1)
#define UART4_TxEnable() (UART4->CON.TXEN = 1)
#define UART5_TxEnable() (UART5->CON.TXEN = 1)
#define UART0_TxDisable() (UART0->CON.TXEN = 0)
#define UART1_TxDisable() (UART1->CON.TXEN = 0)
#define UART2_TxDisable() (UART2->CON.TXEN = 0)
#define UART3_TxDisable() (UART3->CON.TXEN = 0)
#define UART4_TxDisable() (UART4->CON.TXEN = 0)
#define UART5_TxDisable() (UART5->CON.TXEN = 0)

/* ����ʹ�ܿ��� */
#define UART0_RxEnable() (UART0->CON.RXEN = 1)
#define UART1_RxEnable() (UART1->CON.RXEN = 1)
#define UART2_RxEnable() (UART2->CON.RXEN = 1)
#define UART3_RxEnable() (UART3->CON.RXEN = 1)
#define UART4_RxEnable() (UART4->CON.RXEN = 1)
#define UART5_RxEnable() (UART5->CON.RXEN = 1)
#define UART0_RxDisable() (UART0->CON.RXEN = 0)
#define UART1_RxDisable() (UART1->CON.RXEN = 0)
#define UART2_RxDisable() (UART2->CON.RXEN = 0)
#define UART3_RxDisable() (UART3->CON.RXEN = 0)
#define UART4_RxDisable() (UART4->CON.RXEN = 0)
#define UART5_RxDisable() (UART5->CON.RXEN = 0)

/* ��������λ */
#define UART0_TxRst() (UART0->CON.TRST = 1)
#define UART1_TxRst() (UART1->CON.TRST = 1)
#define UART2_TxRst() (UART2->CON.TRST = 1)
#define UART3_TxRst() (UART3->CON.TRST = 1)
#define UART4_TxRst() (UART4->CON.TRST = 1)
#define UART5_TxRst() (UART5->CON.TRST = 1)

/* ��������λ */
#define UART0_RxRst() (UART0->CON.RRST = 1)
#define UART1_RxRst() (UART1->CON.RRST = 1)
#define UART2_RxRst() (UART2->CON.RRST = 1)
#define UART3_RxRst() (UART3->CON.RRST = 1)
#define UART4_RxRst() (UART4->CON.RRST = 1)
#define UART5_RxRst() (UART5->CON.RRST = 1)

/************UARTģ�麯������***********/
void UART_Init(UART_TypeDef* UARTx,UART_InitStruType* UART_InitStruct);
void UART_ITConfig(UART_TypeDef* UARTx,UART_TYPE_IT UART_IT,TYPE_FUNCEN NewState);
void UART_TBIMConfig(UART_TypeDef* UARTx,UART_TYPE_TRBIM Type);
void UART_RBIMConfig(UART_TypeDef* UARTx,UART_TYPE_TRBIM Type);
void UART_SendByte(UART_TypeDef* UARTx,uint8_t Temp08);
void UART_SendHalfWord(UART_TypeDef* UARTx,uint16_t Temp16);
void UART_SendWord(UART_TypeDef* UARTx,uint32_t Temp32);
uint8_t UART_RecByte(UART_TypeDef* UARTx);
uint16_t UART_RecHalfWord(UART_TypeDef* UARTx);
uint32_t UART_RecWord(UART_TypeDef* UARTx);
FlagStatus UART_GetFlagStatus(UART_TypeDef* UARTx,UART_TYPE_FLAG UART_Flag);
ITStatus UART_GetITStatus(UART_TypeDef* UARTx,UART_TYPE_IT UART_Flag);
void UART_ClearITPendingBit(UART_TypeDef* UARTx,UART_CLR_IF UART_Flag);

#endif

/*************************END OF FILE**********************/
