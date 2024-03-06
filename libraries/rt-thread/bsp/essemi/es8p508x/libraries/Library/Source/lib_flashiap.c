/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *�ļ�����  lib_flashiap.c
 *��  �ߣ�  Liut
 *��  ����  V1.00
 *��  �ڣ�  2017/07/14
 *��  ����  flash��д�⺯��
 *��  ע��  ������ ES8P508xоƬ
 ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
 ***************************************************************/
#include "lib_flashiap.h"

/***************************************************************
  ��������FlashIap_Close_WPROT
  ��  ����IAP�ر�д����
  ����ֵ��Page:0-63,ÿpage��Ӧ2K�ֽ�,64 ΪINFO��
  ���ֵ����
  ����ֵ���ɹ���ʧ��
 ***************************************************************/
ErrorStatus FlashIap_Close_WPROT(uint8_t Page)
{
    if(Page > 64)
        return ERROR;

    if(Page == 64)
    {
        IAP->WPROT2.Word = 0x00000000;
        return SUCCESS;
    }

    if(Page < 32)
    {
        IAP->WPROT0.Word &=~ ((uint32_t)0x1 << Page);
    }
    else
    {
        Page -= 32;
        IAP->WPROT1.Word &=~ ((uint32_t)0x1 << Page);
    }

    return SUCCESS;
}

/***************************************************************
  ��������FlashIap_Open_WPROT
  ��  ����IAP����д����
  ����ֵ��Page:0-63,ÿpage��Ӧ2K�ֽ�,,64 ΪINFO��
  ���ֵ����
  ����ֵ���ɹ���ʧ��
 ***************************************************************/
ErrorStatus FlashIap_Open_WPROT(uint8_t Page)
{
    if(Page > 64)
        return ERROR;

    if(Page == 64)
    {
        IAP->WPROT2.Word = 0x00000001;
        return SUCCESS;
    }

    if(Page < 32)
    {
        IAP->WPROT0.Word &=~ ((uint32_t)0x1 << Page);
        IAP->WPROT0.Word |=  ((uint32_t)0x1 << Page);
    }
    else
    {
        Page -= 32;
        IAP->WPROT1.Word &=~ ((uint32_t)0x1 << Page);
        IAP->WPROT1.Word |=  ((uint32_t)0x1 << Page);
    }

    return SUCCESS;
}

/***************************************************************
  ��������FlashIap_CloseAll_WPROT
  ��  ����IAP�ر�����д����
  ����ֵ��Page:0-63,ÿpage��Ӧ2K�ֽ�
  ���ֵ����
  ����ֵ���ɹ���ʧ��
 ***************************************************************/
ErrorStatus FlashIap_CloseAll_WPROT(void)
{
    IAP->WPROT0.Word = 0x00000000;
    IAP->WPROT1.Word = 0x00000000;
    IAP->WPROT2.Word = 0x00000000;

    return SUCCESS;
}
/***************************************************************
  ��������FlashIap_OpenAll_WPROT
  ��  ����IAP������д����
  ����ֵ��
  ���ֵ����
  ����ֵ���ɹ���ʧ��
 ***************************************************************/
ErrorStatus FlashIap_OpenAll_WPROT(void)
{
    IAP->WPROT0.Word = 0xFFFFFFFF;
    IAP->WPROT1.Word = 0xFFFFFFFF;
    IAP->WPROT2.Word = 0xFFFFFFFF;

    return SUCCESS;
}

/***************************************************************
  ��������FlashIap_Unlock
  ��  ����IAP�������������
  ����ֵ����
  ���ֵ����
  ����ֵ���ɹ���ʧ��
 ***************************************************************/
ErrorStatus FlashIap_Unlock(void)
{
    uint16_t Temp16;

    FlashIAP_RegUnLock();              //���� IAP

    FlashIAP_Enable();                 //ʹ��IAP

    FlashIAP_REQ();                    //��������

    for(Temp16 = 0; Temp16 < 0xFFFF; Temp16++)    //�ȴ�FLASHӦ���ź�
    {
        if(IAP->CON.FLASH_ACK != 0)
            break;
    }

    if(Temp16 == 0xFFFF)
        return ERROR;
    else
        return SUCCESS;
}

/***************************************************************
  ��������FlashIap_WriteEnd
  ��  ����IAPд����
  ����ֵ����
  ���ֵ����
  ����ֵ���ɹ���ʧ��
 ***************************************************************/
ErrorStatus FlashIap_WriteEnd(void)
{
    uint32_t  Temp32;

    FlashIAP_RegUnLock();                           //IAP����

    IAP->CON.Word &= 0xFFFFFFEE;                    //IAP����FLASH����(����)

    for(Temp32 = 0; Temp32 < 0xFFFF; Temp32++)      //�ȴ�FLASHӦ���ź�(����)
    {
        if(IAP->CON.FLASH_ACK == 0)
            break;
    }

    if(Temp32 == 0xFFFF)
        return ERROR;
    else
        return SUCCESS;
}

/***************************************************************
  ��������FlashIap_ErasePage
  ��  ����IAPҳ����
  ����ֵ��Page_Addr��ҳ��ַ
  ���ֵ����
  ����ֵ���ɹ���ʧ��
 ***************************************************************/
ErrorStatus FlashIap_ErasePage(uint8_t Page_Addr)
{
    uint16_t  Temp16;
    uint32_t temp;

    temp = __get_PRIMASK();                 //��ȡPRIMASK�Ĵ�����ǰ״̬
    __disable_irq();                        //���������ж�

    if(FlashIap_Unlock() == ERROR)
    {
        __set_PRIMASK(temp);                //�ָ�PRIMASK�Ĵ���״̬
        return ERROR;
    }

    if(FlashIap_CloseAll_WPROT() == ERROR)
    {
        __set_PRIMASK(temp);
        return ERROR;
    }

    IAP->ADDR.IAPPA = Page_Addr;            //����ҳ��ַ   

    IAP->TRIG.TRIG = 0x00005EA1;            //����������

    for(Temp16 = 0; Temp16 < 0xFFFF; Temp16++)  
    {                                       //�ж�IAP����״̬
        if((IAP->STA.Word & (uint32_t)0x01) == (uint32_t)0x00)
            break;
    }

    if(Temp16 == 0xFFFF)
    {
        __set_PRIMASK(temp);                //�ָ�PRIMASK�Ĵ���״̬
        return ERROR;
    }

    for(Temp16 = 0; Temp16 < 0xFFFF; Temp16++)  
    {
        if((IAP->STA.Word & (uint32_t)0x02) == (uint32_t)0x02) //�ж�IAPҳ������־
            break;
    }

    if(Temp16 == 0xFFFF)
    {
        __set_PRIMASK(temp);                //�ָ�PRIMASK�Ĵ���״̬
        return ERROR;
    }

    if(FlashIap_WriteEnd() == ERROR)
    {
        __set_PRIMASK(temp);                //�ָ�PRIMASK�Ĵ���״̬
        return ERROR;
    }

    if(FlashIap_OpenAll_WPROT() == ERROR)
    {
        __set_PRIMASK(temp);
        return ERROR;
    }

    __set_PRIMASK(temp);                    //�ָ�PRIMASK�Ĵ���״̬

    return SUCCESS;
}  

/***************************************************************
  ��������FlashIap_WriteCont
  ��  ����IAP����д
  ����ֵ��Unit_addr����Ԫ��ַ �� Page_addr��ҳ��ַ �� Data32������
  ���ֵ����
  ����ֵ���ɹ���ʧ��
 ***************************************************************/
ErrorStatus FlashIap_WriteCont(uint8_t Unit_addr, uint8_t Page_addr, uint32_t Data32)
{
    uint16_t  temp16;

    IAP->ADDR.IAPPA = Page_addr;       //�����ַ 
    IAP->ADDR.IAPCA = Unit_addr;

    IAP->DATA.DATA = Data32;          //��������
    IAP->TRIG.TRIG = 0x00005DA2;      //����������

    for(temp16 = 0; temp16 < 0xFFFF; temp16++)
    {
        if((IAP->STA.Word & (uint32_t)0x01) == (uint32_t)0x00)  //�ж�IAP����״̬
            break;
    }

    if(temp16 == 0xFFFF)
        return ERROR;

    for(temp16 = 0; temp16 < 0xFFFF; temp16++)
    {
        if((IAP->STA.Word & 0x04)==0x04)  //�ж�IAP��̽�����־
            break;
    }

    if(temp16 == 0xFFFF)
        return ERROR;

    return SUCCESS;
}

/***************************************************************
  ��������FlashIap_WriteWord
  ��  ����IAPдһ����
  ����ֵ��Unit_addr����Ԫ��ַ �� Page_addr��ҳ��ַ �� Data32������
  ���ֵ����
  ����ֵ���ɹ���ʧ��
 ***************************************************************/
ErrorStatus FlashIap_WriteWord(uint8_t Unit_addr, uint8_t Page_addr, uint32_t Data32)
{
    uint32_t temp;

    temp = __get_PRIMASK();                 //��ȡPRIMASK�Ĵ�����ǰ״̬
    __disable_irq();                        //���������ж�

    if(FlashIap_Unlock() == ERROR)
    {
        __set_PRIMASK(temp);                //�ָ�PRIMASK�Ĵ���״̬
        return ERROR;
    }

    if(FlashIap_CloseAll_WPROT() == ERROR)
    {
        __set_PRIMASK(temp);                //�ر�����д����״̬
        return ERROR;
    }

    if(FlashIap_WriteCont(Unit_addr, Page_addr, Data32) == ERROR)
    {
        __set_PRIMASK(temp);                //�ָ�PRIMASK�Ĵ���״̬
        return ERROR;
    }

    if(FlashIap_WriteEnd() == ERROR)
    {
        __set_PRIMASK(temp);                //�ָ�PRIMASK�Ĵ���״̬
        return ERROR;
    }

    if(FlashIap_OpenAll_WPROT() == ERROR)
    {
        __set_PRIMASK(temp);                //������д����״̬
        return ERROR;
    }

    __set_PRIMASK(temp);                    //�ָ�PRIMASK�Ĵ���״̬

    return SUCCESS;
}

/***************************************************************
  ��������Flash_Read
  ��  ����Flash������
  ����ֵ��Ram_Addr���������ݵĴ�ŵ�ַ �� Flash_Addr��Flash��ַ��0x00000000 ~ 0x0001FFFF���� Len����ȡ���ֳ���
  ���ֵ������������
  ����ֵ���ɹ���ʧ��
 ***************************************************************/
ErrorStatus Flash_Read(uint32_t * Ram_Addr, uint32_t Flash_Addr,  uint8_t Len)
{
    uint8_t  i;
    uint32_t *ram_addr32;
    const uint32_t *flash_addr32;

    ram_addr32 = (uint32_t *)Ram_Addr;
    flash_addr32 = (const uint32_t *)Flash_Addr;

    if((Len == 0) & (Len>(0x20000 - Flash_Addr) / 4))  //�ж϶�ȡ�����Ƿ�Ϸ�
    {
        return ERROR;
    }

    for(i=0; i<Len; i++)
    {
        *ram_addr32 = *flash_addr32;
        ram_addr32++;
        flash_addr32++;
    }

    return SUCCESS;
}

/*************************END OF FILE**********************/

