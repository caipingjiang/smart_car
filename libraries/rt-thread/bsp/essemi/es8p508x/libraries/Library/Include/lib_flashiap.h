/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *�ļ����� lib_flashiap.h
 *�� �ߣ� Liut
 *�� ���� V1.00
 *�� �ڣ� 2017/07/14
 *�� ���� flash��д�⺯��ͷ�ļ�
 *�� ע�� ������ ES8P508xоƬ
 ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
 ***************************************************************/
#ifndef __LIBIAP_H__
#define __LIBIAP_H__

#include "ES8P508x.h"
#include "type.h"

/*************IAPģ��궨��************/

/* �Ĵ������� */
#define FlashIAP_RegUnLock() (IAP->UL.UL = 0x49415055)
#define FlashIAP_RegLock()   (IAP->UL.UL = 0x00000000)

/* ʹ��IAP */
#define FlashIAP_Enable()  (IAP->CON.EN = 0x1)
#define FlashIAP_Disable() (IAP->CON.EN = 0x0)

/* ����IAP���� */
#define FlashIAP_REQ() (IAP->CON.FLASH_REQ = 0x1)

/************Flashģ�麯������***********/
ErrorStatus FlashIap_Close_WPROT(uint8_t Page);
ErrorStatus FlashIap_Open_WPROT(uint8_t Page);
ErrorStatus FlashIap_CloseAll_WPROT(void);
ErrorStatus FlashIap_OpenAll_WPROT(void);
ErrorStatus FlashIap_Unlock(void);
ErrorStatus FlashIap_WriteEnd(void);
ErrorStatus FlashIap_ErasePage(uint8_t Page_Addr);
ErrorStatus FlashIap_WriteCont(uint8_t Unit_addr, uint8_t Page_addr, uint32_t Data32);
ErrorStatus FlashIap_WriteWord(uint8_t Unit_addr, uint8_t Page_addr, uint32_t Data32);
ErrorStatus Flash_Read(uint32_t * Ram_Addr, uint32_t Flash_Addr, uint8_t Len);

#endif
/*************************END OF FILE**********************/

