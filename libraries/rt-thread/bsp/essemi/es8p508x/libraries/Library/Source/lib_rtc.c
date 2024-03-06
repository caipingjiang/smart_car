/*********************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *�ļ���:  lib_rtc.c
 *��  ��:  Liut
 *��  ��:  V1.00
 *��  ��:  2017/07/14
 *��  ��:  RTCģ�����
 *��  ע:  ������HRSDK-GDB-ES8P508 V1.1
 ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
 **********************************************************/
#include "lib_rtc.h"
#include "lib_scu.h"

/***************************************************************
  ��������RTC_Init
  ��  ����ʵʱʱ�ӳ�ʼ��
  ����ֵ��CLKx:RTCʱ��Դѡ��HOURx��12Сʱ/24Сʱ��ѡ��
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void RTC_Init(RTC_TYPE_CLKS CLKx,RTC_TYPE_TIME HOURx)
{
    uint32_t flag;
	
		if(CLKx == RTC_LOSC )
	  {
		  uint32_t Prot_Temp;

        Prot_Temp = SCU->PROT.PROT;

        if(Prot_Temp != 0)         //д������
            SCU_RegUnLock();       //����

        SCU_XTAL_Enable();         //ʹ���ⲿ32kHZ			
        while(SCU_XTALReadyFlag() != SET);      //�ȴ�ʱ�ӿ���
        
				if(Prot_Temp != 0)     
				    SCU_RegLock();        //��д����
	  }
		
    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;
    RTC->CON.PON = 0;               // ���㣬ʹ��RTC
    RTC->CON.HSWI = HOURx;          // 24Сʱģʽ
    RTC->CON.CLKS = CLKx;           // ʱ��Դѡ��32768Hz

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
}
/***************************************************************
  ��������RTC_StartRead
  ��  ��������ʵʱʱ�Ӷ�����
  ����ֵ����
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void RTC_StartRead(void)
{
    RTC->CON.TMWR = 0;              // ���������Ƕ�
    RTC->CON.TMUP = 1;              // ����������
    while (RTC->CON.TMUP == 1);     //�ȴ������
}

/***************************************************************
  ��������RTC_ReadHourmode
  ��  ������ȡСʱģʽ
  ����ֵ����
  ���ֵ����
  ����ֵ����ǰ��Сʱģʽ
 ***************************************************************/
uint32_t RTC_ReadHourmode(void)
{
    uint32_t flag;
    uint32_t result;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �������������� */
    RTC_StartRead();

    result = RTC->CON.HSWI;

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;

    return result;
}
/***************************************************************
  ��������RTC_ReadSecond
  ��  ������ȡ��
  ����ֵ����
  ���ֵ����
  ����ֵ����ǰ����
 ***************************************************************/
uint32_t RTC_ReadSecond(void)
{
    uint32_t flag;
    uint32_t result;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �������������� */
    RTC_StartRead();

    /* ����ʱ�� */
    result = ((RTC->HMS.SEC & (uint32_t)0x01) * 1);
    result += (((RTC->HMS.SEC >> 1) & (uint32_t)0x01) * 2);
    result += (((RTC->HMS.SEC >> 2) & (uint32_t)0x01) * 4);
    result += (((RTC->HMS.SEC >> 3) & (uint32_t)0x01) * 8);
    result += (((RTC->HMS.SEC >> 4) & (uint32_t)0x01) * 10);
    result += (((RTC->HMS.SEC >> 5) & (uint32_t)0x01) * 20);
    result += (((RTC->HMS.SEC >> 6) & (uint32_t)0x01) * 40);

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;

    return result;
}

/***************************************************************
  ��������RTC_ReadMinute
  ��  ������ȡ��
  ����ֵ����
  ���ֵ����
  ����ֵ����ǰ�ķ�
 ***************************************************************/
uint32_t RTC_ReadMinute(void)
{
    uint32_t flag;
    uint32_t result;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �������������� */
    RTC_StartRead();

    /* ����ʱ�� */
    result = ((RTC->HMS.MIN & (uint32_t)0x01) * 1);
    result += (((RTC->HMS.MIN >> 1) & (uint32_t)0x01) * 2);
    result += (((RTC->HMS.MIN >> 2) & (uint32_t)0x01) * 4);
    result += (((RTC->HMS.MIN >> 3) & (uint32_t)0x01) * 8);
    result += (((RTC->HMS.MIN >> 4) & (uint32_t)0x01) * 10);
    result += (((RTC->HMS.MIN >> 5) & (uint32_t)0x01) * 20);
    result += (((RTC->HMS.MIN >> 6) & (uint32_t)0x01) * 40);

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;

    return result;
}

/***************************************************************
  ��������RTC_ReadHour
  ��  ������ȡСʱ
  ����ֵ����
  ���ֵ����
  ����ֵ����ǰ��Сʱ
 ***************************************************************/
uint32_t RTC_ReadHour(uint32_t *meridiem)
{
    uint32_t flag;
    uint32_t result;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �������������� */
    RTC_StartRead();

    /* ����ʱ�� */
    result = ((RTC->HMS.HOUR & (uint32_t)0x01) * 1);
    result += (((RTC->HMS.HOUR >> 1) & (uint32_t)0x01) * 2);
    result += (((RTC->HMS.HOUR >> 2) & (uint32_t)0x01) * 4);
    result += (((RTC->HMS.HOUR >> 3) & (uint32_t)0x01) * 8);
    result += (((RTC->HMS.HOUR >> 4) & (uint32_t)0x01) * 10);

    if(RTC_ReadHourmode() == RTC_HOUR24)                        //24Сʱģʽ��20Сʱ
    {
        result += (((RTC->HMS.HOUR >> 5) & (uint32_t)0x01) * 20);
    }
    else                                                        //12Сʱģʽ��1 PM,0 AM
    {
        *meridiem = (((RTC->HMS.HOUR >> 5) & (uint32_t)0x01));
    }

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;

    return result;
}

/***************************************************************
  ��������RTC_ReadDay
  ��  ������ȡ��
  ����ֵ����
  ���ֵ����
  ����ֵ����ǰ����
 ***************************************************************/
uint32_t RTC_ReadDay(void)
{
    uint32_t flag;
    uint32_t result;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;
    /* �������������� */
    RTC_StartRead();

    /* ����ʱ�� */
    result = ((RTC->YMDW.DAY & (uint32_t)0x01) * 1);
    result += (((RTC->YMDW.DAY >> 1) & (uint32_t)0x01) * 2);
    result += (((RTC->YMDW.DAY >> 2) & (uint32_t)0x01) * 4);
    result += (((RTC->YMDW.DAY >> 3) & (uint32_t)0x01) * 8);
    result += (((RTC->YMDW.DAY >> 4) & (uint32_t)0x01) * 10);
    result += (((RTC->YMDW.DAY >> 5) & (uint32_t)0x01) * 20);

    /* ����RTCд���� */
    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
    return result;
}

/***************************************************************
  ��������RTC_ReadMonth
  ��  ������ȡ��
  ����ֵ����
  ���ֵ����
  ����ֵ����ǰ����
 ***************************************************************/
uint32_t RTC_ReadMonth(void)
{
    uint32_t flag;
    uint32_t result;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �������������� */
    RTC_StartRead();

    /* ����ʱ�� */
    result = ((RTC->YMDW.MON & (uint32_t)0x01) * 1);
    result += (((RTC->YMDW.MON >> 1) & (uint32_t)0x01) * 2);
    result += (((RTC->YMDW.MON >> 2) & (uint32_t)0x01) * 4);
    result += (((RTC->YMDW.MON >> 3) & (uint32_t)0x01) * 8);
    result += (((RTC->YMDW.MON >> 4) & (uint32_t)0x01) * 10);

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;

    return result;
}

/***************************************************************
  ��������RTC_ReadYear
  ��  ������ȡ��
  ����ֵ����
  ���ֵ����
  ����ֵ����ǰ����
 ***************************************************************/
uint32_t RTC_ReadYear(void)
{
    uint32_t flag;
    uint32_t result;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �������������� */
    RTC_StartRead();

    /* ����ʱ�� */
    result = ((RTC->YMDW.YEAR & (uint32_t)0x01) * 1);
    result += (((RTC->YMDW.YEAR >> 1) & (uint32_t)0x01) * 2);
    result += (((RTC->YMDW.YEAR >> 2) & (uint32_t)0x01) * 4);
    result += (((RTC->YMDW.YEAR >> 3) & (uint32_t)0x01) * 8);
    result += (((RTC->YMDW.YEAR >> 4) & (uint32_t)0x01) * 10);
    result += (((RTC->YMDW.YEAR >> 5) & (uint32_t)0x01) * 20);
    result += (((RTC->YMDW.YEAR >> 6) & (uint32_t)0x01) * 40);
    result += (((RTC->YMDW.YEAR >> 7) & (uint32_t)0x01) * 80);
    result += 2000;

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;

    return result;
}
/***************************************************************
  ��������RTC_ReadWeek
  ��  ������ȡ����
  ����ֵ����
  ���ֵ����
  ����ֵ����ǰ������
 ***************************************************************/
uint32_t RTC_ReadWeek(void)
{
    uint32_t flag;
    uint32_t result;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �������������� */
    RTC_StartRead();

    /* ����ʱ�� */
    switch(RTC->YMDW.WEEK)
    {
        case 0x00: result = 0;break;
        case 0x01: result = 1;break;
        case 0x02: result = 2;break;
        case 0x03: result = 3;break;
        case 0x04: result = 4;break;
        case 0x05: result = 5;break;
        case 0x06: result = 6;break;
        default:   result = 0;break;
    }

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;

    return result;
}

/***************************************************************
  ��������RTC_StartRead
  ��  ��������ʵʱʱ��д����
  ����ֵ����
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void RTC_StartWrite(void)
{
    /* ����д�������� */
    RTC->CON.TMWR = 1;              // ����������д
    RTC->CON.TMUP = 1;              // ����д����
    while (RTC->CON.TMUP == 1);     //�ȴ�д���
}

/***************************************************************
  ��������RTC_WriteSecond
  ��  �����޸���
  ����ֵ��second: ��
  ���ֵ����
  ����ֵ����
 ***************************************************************/
ErrorStatus RTC_WriteSecond(uint32_t second)
{
    uint32_t flag = 0;
    uint32_t sec_buf = 0;

    /* ���������� */
    if (second >= 60)
        return ERROR;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �����µ�ֵ */
    if (second >= 40)
    {
        sec_buf |= (uint32_t)1<<6;
        second -= 40;
    }
    else
    {
        sec_buf &= ~(uint32_t)1<<6;
    }

    if (second >= 20)
    {
        sec_buf |= (uint32_t)1<<5;
        second -= 20;
    }
    else
    {
        sec_buf &= ~(uint32_t)1<<5;
    }

    if (second >= 10)
    {
        sec_buf |= (uint32_t)1<<4;
        second -= 10;
    }
    else
    {
        sec_buf &= ~(uint32_t)1<<4;
    }

    if (second >= 8)
    {
        sec_buf |= (uint32_t)1<<3;
        second -= 8;
    }
    else
    {
        sec_buf &= ~(uint32_t)1<<3;
    }

    if (second >= 4)
    {
        sec_buf |= (uint32_t)1<<2;
        second -= 4;
    }
    else
    {
        sec_buf &= ~(uint32_t)1<<2;
    }

    if (second >= 2)
    {
        sec_buf |= (uint32_t)1<<1;
        second -= 2;
    }
    else
    {
        sec_buf &= ~(uint32_t)1<<1;
    }

    if (second >= 1)
    {
        sec_buf |= (uint32_t)1;
        second -= 1;
    }
    else
    {
        sec_buf &= ~(uint32_t)1;
    }

    RTC->HMS.SEC = sec_buf;

    /* ����д�������� */
    RTC_StartWrite();

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
    return SUCCESS;
}

/***************************************************************
  ��������RTC_WriteMinute
  ��  �����޸���
  ����ֵ��minute: ��
  ���ֵ����
  ����ֵ����
 ***************************************************************/
ErrorStatus RTC_WriteMinute(uint32_t minute)
{
    uint32_t flag;
    uint32_t min_buf = 0;

    /* ���������� */
    if (minute >= 60)
        return ERROR;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �����µ�ֵ */
    if (minute >= 40) 
    {
        min_buf |= (uint32_t)1<<6;
        minute -= 40;
    } 
    else 
    {
        min_buf &= ~(uint32_t)1<<6;
    }

    if (minute >= 20) 
    {
        min_buf |= (uint32_t)1<<5;
        minute -= 20;
    } 
    else 
    {
        min_buf &= ~(uint32_t)1<<5;
    }

    if (minute >= 10)
    {
        min_buf |= (uint32_t)1<<4;
        minute -= 10;
    } 
    else 
    {
        min_buf &= ~(uint32_t)1<<4;
    }

    if (minute >= 8) 
    {
        min_buf |= (uint32_t)1<<3;
        minute -= 8;
    } 
    else 
    {
        min_buf &= ~(uint32_t)1<<3;
    }

    if (minute >= 4) 
    {
        min_buf |= (uint32_t)1<<2;
        minute -= 4;
    } 
    else 
    {
        min_buf &= ~(uint32_t)1<<2;
    }

    if (minute >= 2) 
    {
        min_buf |= (uint32_t)1<<1;
        minute -= 2;
    } 
    else 
    {
        min_buf &= ~(uint32_t)1<<1;
    }

    if (minute >= 1) 
    {
        min_buf |= (uint32_t)1;
        minute -= 1;
    } 
    else 
    {
        min_buf &= ~(uint32_t)1;
    }

    RTC->HMS.MIN = min_buf;

    /* ����д�������� */
    RTC_StartWrite();

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
    return SUCCESS;
}


/***************************************************************
  ��������RTC_WriteHour
  ��  �����޸�ʱ
  ����ֵ��hour: ʱ
  ���ֵ����
  ����ֵ����
 ***************************************************************/
ErrorStatus RTC_WriteHour(uint32_t hour, uint32_t meridiem)
{
    uint32_t flag,mode;
    uint32_t hour_buf = 0;

    /* ���������� */
    if (hour >= 24)
        return ERROR;

    mode = RTC_ReadHourmode();

    if(mode == RTC_HOUR12 && hour > 12)     //12Сʱģʽ���ɴ���12Сʱ
        return ERROR;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �����µ�ֵ */
    if(mode == RTC_HOUR24)
    {
        if (hour >= 20)
        {
            hour_buf |= (uint32_t)1<<5;
            hour -= 20;
        }
        else
        {
            hour_buf &= ~((uint32_t)1<<5);
        }
    }
    else
    {
        if(meridiem == 1)
            hour_buf |= (uint32_t)1<<5;
        else
            hour_buf &= ~((uint32_t)1<<5);
    }

    if (hour >= 10)
    {
        hour_buf |= (uint32_t)1<<4;
        hour -= 10;
    }
    else
    {
        hour_buf &= ~((uint32_t)1<<4);
    }

    if (hour >= 8)
    {
        hour_buf |= (uint32_t)1<<3;
        hour -= 8;
    }
    else
    {
        hour_buf &= ~((uint32_t)1<<3);
    }

    if (hour >= 4)
    {
        hour_buf |= (uint32_t)1<<2;
        hour -= 4;
    }
    else
    {
        hour_buf &= ~((uint32_t)1<<2);
    }

    if (hour >= 2)
    {
        hour_buf |= (uint32_t)1<<1;
        hour -= 2;
    }
    else
    {
        hour_buf &= ~((uint32_t)1<<1);
    }

    if (hour >= 1)
    {
        hour_buf |= (uint32_t)1;
        hour -= 1;
    }
    else
    {
        hour_buf &= ~(uint32_t)1;
    }

    RTC->HMS.HOUR = hour_buf;

    /* ����д�������� */
    RTC_StartWrite();

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
    return SUCCESS;
}

/***************************************************************
  ��������RTC_WriteDay
  ��  �����޸���
  ����ֵ��day: ��
  ���ֵ����
  ����ֵ����
 ***************************************************************/
ErrorStatus RTC_WriteDay(uint32_t day)
{
    uint32_t flag;
    uint32_t day_buf = 0;

    /* ���������� */
    if ((day == 0) || (day >= 32))
        return ERROR;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �����µ�ֵ */
    if (day >= 20) 
    {
        day_buf |= (uint32_t)1<<5;
        day -= 20;
    } 
    else 
    {
        day_buf &= ~((uint32_t)1<<5);
    }

    if (day >= 10)
    {
        day_buf |= (uint32_t)1<<4;
        day -= 10;
    } 
    else 
    {
        day_buf &= ~((uint32_t)1<<4);
    }

    if (day >= 8) 
    {
        day_buf |= (uint32_t)1<<3;
        day -= 8;
    } 
    else 
    {
        day_buf &= ~((uint32_t)1<<3);
    }

    if (day >= 4) 
    {
        day_buf |= (uint32_t)1<<2;
        day -= 4;
    } 
    else 
    {
        day_buf &= ~((uint32_t)1<<2);
    }

    if (day >= 2) 
    {
        day_buf |= (uint32_t)1<<1;
        day -= 2;
    } 
    else 
    {
        day_buf &= ~((uint32_t)1<<1);
    }

    if (day >= 1)
    {
        day_buf |= (uint32_t)1;
        day -= 1;
    } 
    else 
    {
        day_buf &= ~(uint32_t)1;
    }

    RTC->YMDW.DAY = day_buf;

    /* ����д�������� */
    RTC_StartWrite();

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
    return SUCCESS;
}


/***************************************************************
  ��������RTC_WriteMonth
  ��  �����޸���
  ����ֵ��month: ��
  ���ֵ����
  ����ֵ����
 ***************************************************************/
ErrorStatus RTC_WriteMonth(uint32_t month)
{
    uint32_t flag;
    uint32_t month_buf = 0;

    /* ���������� */
    if ((month == 0) || (month >= 13))
        return ERROR;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �����µ�ֵ */
    if (month >= 10)
    {
        month_buf |= (uint32_t)1<<4;
        month -= 10;
    }
    else
    {
        month_buf &= ~((uint32_t)1<<4);
    }

    if (month >= 8)
    {
        month_buf |= (uint32_t)1<<3;
        month -= 8;
    }
    else
    {
        month_buf &= ~((uint32_t)1<<3);
    }

    if (month >= 4)
    {
        month_buf |= (uint32_t)1<<2;
        month -= 4;
    }
    else
    {
        month_buf &= ~((uint32_t)1<<2);
    }

    if (month >= 2)
    {
        month_buf |= (uint32_t)1<<1;
        month -= 2;
    }
    else
    {
        month_buf &= ~((uint32_t)1<<1);
    }

    if (month >= 1)
    {
        month_buf |= (uint32_t)1;
        month -= 1;
    }
    else
    {
        month_buf &= ~(uint32_t)1;
    }

    RTC->YMDW.MON = month_buf;

    /* ����д�������� */
    RTC_StartWrite();

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
    return SUCCESS;
}

/***************************************************************
  ��������RTC_WriteYear
  ��  �����޸���
  ����ֵ��year: ��
  ���ֵ����
  ����ֵ����
 ***************************************************************/
ErrorStatus RTC_WriteYear(uint32_t year)
{
    uint32_t flag;
    uint32_t year_buf = 0;

    /* ���������� */
    if ((year < 2000) || (year > 2099))
        return ERROR;

    /* ��ת�� */
    year -= 2000;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �����µ�ֵ */
    if (year >= 80)
    {
        year_buf |= (uint32_t)1<<7;
        year -= 80;
    }
    else
    {
        year_buf &= ~((uint32_t)1<<7);
    }

    if (year >= 40)
    {
        year_buf |= (uint32_t)1<<6;
        year -= 40;
    }
    else
    {
        year_buf &= ~((uint32_t)1<<6);
    }

    if (year >= 20)
    {
        year_buf |= (uint32_t)1<<5;
        year -= 20;
    }
    else
    {
        year_buf &= ~((uint32_t)1<<5);
    }

    if (year >= 10)
    {
        year_buf |= (uint32_t)1<<4;
        year -= 10;
    }
    else
    {
        year_buf &= ~((uint32_t)1<<4);
    }

    if (year >= 8)
    {
        year_buf |= (uint32_t)1<<3;
        year -= 8;
    }
    else
    {
        year_buf &= ~((uint32_t)1<<3);
    }

    if (year >= 4)
    {
        year_buf |= (uint32_t)1<<2;
        year -= 4;
    }
    else
    {
        year_buf &= ~((uint32_t)1<<2);
    }

    if (year >= 2)
    {
        year_buf |= (uint32_t)1<<1;
        year -= 2;
    }
    else
    {
        year_buf &= ~((uint32_t)1<<1);
    }

    if (year >= 1)
    {
        year_buf |= (uint32_t)1;
        year -= 1;
    }
    else
    {
        year_buf &= ~(uint32_t)1;
    }

    RTC->YMDW.YEAR = year_buf;

    /* ����д�������� */
    RTC_StartWrite();

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
    return SUCCESS;
}

/***************************************************************
  ��������RTC_WriteWeek
  ��  �����޸�����
  ����ֵ��week: ���ڣ�0-6��
  ���ֵ����
  ����ֵ����
 ***************************************************************/
ErrorStatus RTC_WriteWeek(uint32_t week)
{
    uint32_t flag;

    /* ���������� */
    if (week > 6)
        return ERROR;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    RTC->YMDW.WEEK = week;

    /* ����д�������� */
    RTC->CON.TMWR = 1;      // ����������д
    RTC->CON.TMUP = 1;      // ����д����
    while (RTC->CON.TMUP == 1);

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
    return SUCCESS;
}

/***************************************************************
  ��������RTC_ReadWeekAlarmMinute
  ��  ������ȡ��
  ����ֵ����
  ���ֵ����
  ����ֵ����ǰ�ķ�
 ***************************************************************/
uint32_t RTC_ReadWeekAlarmMinute(void)
{
    uint32_t flag;
    uint32_t result;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �������������� */
    RTC_StartRead();

    /* ����ʱ�� */
    result = ((RTC->WA.WM & (uint32_t)0x01) * 1);
    result += (((RTC->WA.WM >> 1) & (uint32_t)0x01) * 2);
    result += (((RTC->WA.WM >> 2) & (uint32_t)0x01) * 4);
    result += (((RTC->WA.WM >> 3) & (uint32_t)0x01) * 8);
    result += (((RTC->WA.WM >> 4) & (uint32_t)0x01) * 10);
    result += (((RTC->WA.WM >> 5) & (uint32_t)0x01) * 20);
    result += (((RTC->WA.WM >> 6) & (uint32_t)0x01) * 40);

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;

    return result;
}

/***************************************************************
  ��������RTC_ReadWeekAlarmHour
  ��  ������ȡСʱ
  ����ֵ����
  ���ֵ����
  ����ֵ����ǰ��Сʱ
 ***************************************************************/
uint32_t RTC_ReadWeekAlarmHour(uint32_t *meridiem)
{
    uint32_t flag;
    uint32_t result;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �������������� */
    RTC_StartRead();

    /* ����ʱ�� */
    result = ((RTC->WA.WH & (uint32_t)0x01) * 1);
    result += (((RTC->WA.WH >> 1) & (uint32_t)0x01) * 2);
    result += (((RTC->WA.WH >> 2) & (uint32_t)0x01) * 4);
    result += (((RTC->WA.WH >> 3) & (uint32_t)0x01) * 8);
    result += (((RTC->WA.WH >> 4) & (uint32_t)0x01) * 10);

    if(RTC_ReadHourmode() == RTC_HOUR24)                        //24Сʱģʽ��20Сʱ
    {
        result += (((RTC->WA.WH >> 5) & (uint32_t)0x01) * 20);
    }
    else                                                        //12Сʱģʽ��1 PM,0 AM
    {
        *meridiem = (((RTC->WA.WH >> 5) & (uint32_t)0x01));
    }

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;

    return result;
}

/***************************************************************
  ��������RTC_ReadWeekAlarmWeek
  ��  ������ȡ����
  ����ֵ����
  ���ֵ����
  ����ֵ����ǰ������
 ***************************************************************/
uint32_t RTC_ReadWeekAlarmWeek(void)
{
    uint32_t flag;
    uint32_t result;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �������������� */
    RTC_StartRead();

    /* ����ʱ�� */
    switch(RTC->WA.WW)
    {
        case 0x00: result = 0;break;
        case 0x01: result = 1;break;
        case 0x02: result = 2;break;
        case 0x03: result = 3;break;
        case 0x04: result = 4;break;
        case 0x05: result = 5;break;
        case 0x06: result = 6;break;
        default:   result = 0;break;
    }

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;

    return result;
}


/***************************************************************
  ��������RTC_ReadDayAlarmMinute
  ��  ������ȡ����
  ����ֵ����
  ���ֵ����
  ����ֵ����ǰ�ķ���
 ***************************************************************/
uint32_t RTC_ReadDayAlarmMinute(void)
{
    uint32_t flag;
    uint32_t result;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �������������� */
    RTC_StartRead();

    /* ����ʱ�� */
    result = ((RTC->DA.DM & (uint32_t)0x01) * 1);
    result += (((RTC->DA.DM >> 1) & (uint32_t)0x01) * 2);
    result += (((RTC->DA.DM >> 2) & (uint32_t)0x01) * 4);
    result += (((RTC->DA.DM >> 3) & (uint32_t)0x01) * 8);
    result += (((RTC->DA.DM >> 4) & (uint32_t)0x01) * 10);
    result += (((RTC->DA.DM >> 5) & (uint32_t)0x01) * 20);
    result += (((RTC->DA.DM >> 6) & (uint32_t)0x01) * 40);

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;

    return result;
}

/***************************************************************
  ��������RTC_ReadDaykAlarmHour
  ��  ������ȡСʱ
  ����ֵ����
  ���ֵ����
  ����ֵ����ǰ��Сʱ
 ***************************************************************/
uint32_t RTC_ReadDayAlarmHour(uint32_t *meridiem)
{
    uint32_t flag;
    uint32_t result;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �������������� */
    RTC_StartRead();

    /* ����ʱ�� */
    result = ((RTC->DA.DH & (uint32_t)0x01) * 1);
    result += (((RTC->DA.DH >> 1) & (uint32_t)0x01) * 2);
    result += (((RTC->DA.DH >> 2) & (uint32_t)0x01) * 4);
    result += (((RTC->DA.DH >> 3) & (uint32_t)0x01) * 8);
    result += (((RTC->DA.DH >> 4) & (uint32_t)0x01) * 10);

    if(RTC_ReadHourmode() == RTC_HOUR24)                        //24Сʱģʽ��20Сʱ
    {
        result += (((RTC->DA.DH >> 5) & (uint32_t)0x01) * 20);
    }
    else                                                        //12Сʱģʽ��1 PM,0 AM
    {
        *meridiem = (((RTC->DA.DH >> 5) & (uint32_t)0x01));
    }

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;

    return result;
}

/***************************************************************
  ��������RTC_WriteWeekAlarmMinute
  ��  �����޸ķ���
  ����ֵ��minute: ����
  ���ֵ����
  ����ֵ����
 ***************************************************************/
ErrorStatus RTC_WriteWeekAlarmMinute(uint32_t minute)
{
    uint32_t flag;
    uint32_t minute_buf = 0;

    /* ���������� */
    if (minute >= 60)
        return ERROR;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �����µ�ֵ */
    if (minute >= 40)
    {
        minute_buf |= (uint32_t)1<<6;
        minute -= 40;
    }
    else
    {
        minute_buf &= ~(uint32_t)1<<6;
    }

    if (minute >= 20)
    {
        minute_buf |= (uint32_t)1<<5;
        minute -= 20;
    }
    else
    {
        minute_buf &= ~(uint32_t)1<<5;
    }

    if (minute >= 10)
    {
        minute_buf |= (uint32_t)1<<4;
        minute -= 10;
    }
    else
    {
        minute_buf &= ~(uint32_t)1<<4;
    }

    if (minute >= 8)
    {
        minute_buf |= (uint32_t)1<<3;
        minute -= 8;
    }
    else
    {
        minute_buf &= ~(uint32_t)1<<3;
    }

    if (minute >= 4)
    {
        minute_buf |= (uint32_t)1<<2;
        minute -= 4;
    }
    else
    {
        minute_buf &= ~(uint32_t)1<<2;
    }

    if (minute >= 2)
    {
        minute_buf |= (uint32_t)1<<1;
        minute -= 2;
    }
    else
    {
        minute_buf &= ~(uint32_t)1<<1;
    }

    if (minute >= 1)
    {
        minute_buf |= (uint32_t)1;
        minute -= 1;
    }
    else
    {
        minute_buf &= ~(uint32_t)1;
    }

    RTC->WA.WM = minute_buf;

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
    return SUCCESS;
}

/***************************************************************
  ��������RTC_WriteWeekAlarmHour
  ��  �����޸�Сʱ
  ����ֵ��hour: Сʱ
          meridiem��(����12Сʱģʽʱ��Ч)
                    0 AM
                    1 PM
  ���ֵ����
  ����ֵ����
 ***************************************************************/
ErrorStatus RTC_WriteWeekAlarmHour(uint32_t hour, uint32_t meridiem)
{
    uint32_t flag,mode;
    uint32_t hour_buf = 0;

    /* ���������� */
    if (hour >= 24)
        return ERROR;

    mode = RTC_ReadHourmode();

    if(mode == RTC_HOUR12 && hour > 12)     //12Сʱģʽ���ɴ���12Сʱ
        return ERROR;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �����µ�ֵ */
    if(mode == RTC_HOUR24)
    {
        if (hour >= 20)
        {
            hour_buf |= (uint32_t)1<<5;
            hour -= 20;
        }
        else
        {
            hour_buf &= ~((uint32_t)1<<5);
        }
    }
    else
    {
        if(meridiem == 1)
            hour_buf |= (uint32_t)1<<5;
        else
            hour_buf &= ~((uint32_t)1<<5);
    }

    if (hour >= 10)
    {
        hour_buf |= (uint32_t)1<<4;
        hour -= 10;
    }
    else
    {
        hour_buf &= ~((uint32_t)1<<4);
    }

    if (hour >= 8)
    {
        hour_buf |= (uint32_t)1<<3;
        hour -= 8;
    } 
    else
    {
        hour_buf &= ~((uint32_t)1<<3);
    }

    if (hour >= 4)
    {
        hour_buf |= (uint32_t)1<<2;
        hour -= 4;
    } 
    else
    {
        hour_buf &= ~((uint32_t)1<<2);
    }

    if (hour >= 2)
    {
        hour_buf |= (uint32_t)1<<1;
        hour -= 2;
    } 
    else
    {
        hour_buf &= ~((uint32_t)1<<1);
    }

    if (hour >= 1)
    {
        hour_buf |= (uint32_t)1;
        hour -= 1;
    } 
    else
    {
        hour_buf &= ~(uint32_t)1;
    }

    RTC->WA.WH = hour_buf;


    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
    return SUCCESS;
}
/***************************************************************
  ��������RTC_WriteWeekAlarmWeek
  ��  �����޸�����
  ����ֵ��week: ���ڣ�0-6��
  ���ֵ����
  ����ֵ����
 ***************************************************************/
ErrorStatus RTC_WriteWeekAlarmWeek(uint32_t week)
{
    uint32_t flag;

    /* ���������� */
    if (week > 6)
        return ERROR;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    RTC->WA.WW = week;

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
    return SUCCESS;
}

/***************************************************************
  ��������RTC_WriteDayAlarmMinute
  ��  �����޸ķ���
  ����ֵ��minute: ����
  ���ֵ����
  ����ֵ����
 ***************************************************************/
ErrorStatus RTC_WriteDayAlarmMinute(uint32_t minute)
{
    uint32_t flag,minute_buf;

    /* ���������� */
    if (minute >= 60)
        return ERROR;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �����µ�ֵ */
    if (minute >= 40)
    {
        minute_buf |= (uint32_t)1<<6;
        minute -= 40;
    }
    else
    {
        minute_buf &= ~(uint32_t)1<<6;
    }

    if (minute >= 20)
    {
        minute_buf |= (uint32_t)1<<5;
        minute -= 20;
    }
    else
    {
        minute_buf &= ~(uint32_t)1<<5;
    }

    if (minute >= 10)
    {
        minute_buf |= (uint32_t)1<<4;
        minute -= 10;
    }
    else
    {
        minute_buf &= ~(uint32_t)1<<4;
    }

    if (minute >= 8)
    {
        minute_buf |= (uint32_t)1<<3;
        minute -= 8;
    }
    else
    {
        minute_buf &= ~(uint32_t)1<<3;
    }

    if (minute >= 4)
    {
        minute_buf |= (uint32_t)1<<2;
        minute -= 4;
    }
    else
    {
        minute_buf &= ~(uint32_t)1<<2;
    }

    if (minute >= 2)
    {
        minute_buf |= (uint32_t)1<<1;
        minute -= 2;
    }
    else
    {
        minute_buf &= ~(uint32_t)1<<1;
    }

    if (minute >= 1)
    {
        minute_buf |= (uint32_t)1;
        minute -= 1;
    }
    else
    {
        minute_buf &= ~(uint32_t)1;
    }

    RTC->DA.DM = minute_buf;


    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
    return SUCCESS;
}

/***************************************************************
  ��������RTC_WriteDayAlarmHour
  ��  �����޸�Сʱ
  ����ֵ��hour: Сʱ
          meridiem��(����12Сʱģʽʱ��Ч)
                    0 AM
                    1 PM
  ���ֵ����
  ����ֵ����
 ***************************************************************/
ErrorStatus RTC_WriteDayAlarmHour(uint32_t hour, uint32_t meridiem)
{
    uint32_t flag,mode;
    uint32_t hour_buf = 0;

    /* ���������� */
    if (hour >= 24)
        return ERROR;

    mode = RTC_ReadHourmode();

    if(mode == RTC_HOUR12 && hour > 12)     //12Сʱģʽ���ɴ���12Сʱ
        return ERROR;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �����µ�ֵ */
    if(mode == RTC_HOUR24)
    {
        if (hour >= 20)
        {
            hour_buf |= (uint32_t)1<<5;
            hour -= 20;
        }
        else
        {
            hour_buf &= ~((uint32_t)1<<5);
        }
    }
    else
    {
        if(meridiem == 1)
            hour_buf |= (uint32_t)1<<5;
        else
            hour_buf &= ~((uint32_t)1<<5);
    }

    if (hour >= 10)
    {
        hour_buf |= (uint32_t)1<<4;
        hour -= 10;
    }
    else
    {
        hour_buf &= ~((uint32_t)1<<4);
    }

    if (hour >= 8) 
    {
        hour_buf |= (uint32_t)1<<3;
        hour -= 8;
    }
    else
    {
        hour_buf &= ~((uint32_t)1<<3);
    }

    if (hour >= 4) 
    {
        hour_buf |= (uint32_t)1<<2;
        hour -= 4;
    }
    else
    {
        hour_buf &= ~((uint32_t)1<<2);
    }

    if (hour >= 2) 
    {
        hour_buf |= (uint32_t)1<<1;
        hour -= 2;
    }
    else
    {
        hour_buf &= ~((uint32_t)1<<1);
    }

    if (hour >= 1) 
    {
        hour_buf |= (uint32_t)1;
        hour -= 1;
    }
    else
    {
        hour_buf &= ~(uint32_t)1;
    }

    RTC->DA.DH = hour_buf;

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
    return SUCCESS;
}


/***************************************************************
  ��������RTC_InterruptEnable
  ��  ����ʹ��ʵʱʱ�ӵ�ĳЩ�ж�
  ����ֵ��src: ʵʱʱ�ӵ��ж�Դ
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void RTC_InterruptEnable(RTC_Interrupt_Source src)
{
    uint32_t flag;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �����µ�ֵ */
    switch (src)
    {
        case RTC_Interrupt_Source_Second:
            RTC->IE.SCDIE = 1;
            break;
        case RTC_Interrupt_Source_Minute:
            RTC->IE.MINIE = 1;
            break;
        case RTC_Interrupt_Source_Hour:
            RTC->IE.HORIE = 1;
            break;
        case RTC_Interrupt_Source_Day:
            RTC->IE.DAYIE = 1;
            break;
        case RTC_Interrupt_Source_Month:
            RTC->IE.MONIE = 1;
            break;
        case RTC_Interrupt_Source_DayALE:
            RTC->IE.DALE = 1;
            break;
        case RTC_Interrupt_Source_WeekALE:
            RTC->IE.WALE = 1;
            break;
        default:
            break;
    }

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;

    NVIC->ISER[0] |= (1 << 20); // ʹ��NVIC�ж�
    return;
}

/***************************************************************
  ��������RTC_InterruptDisable
  ��  ��������ʵʱʱ�ӵ�ĳЩ�ж�
  ����ֵ��src: ʵʱʱ�ӵ��ж�Դ
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void RTC_InterruptDisable(RTC_Interrupt_Source src)
{
    uint32_t flag;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    /* �����µ�ֵ */
    switch (src)
    {
        case RTC_Interrupt_Source_Second:
            RTC->IE.SCDIE = 0;
            break;
        case RTC_Interrupt_Source_Minute:
            RTC->IE.MINIE = 0;
            break;
        case RTC_Interrupt_Source_Hour:
            RTC->IE.HORIE = 0;
            break;
        case RTC_Interrupt_Source_Day:
            RTC->IE.DAYIE = 0;
            break;
        case RTC_Interrupt_Source_Month:
            RTC->IE.MONIE = 0;
            break;
        case RTC_Interrupt_Source_DayALE:
            RTC->IE.DALE = 0;
            break;
        case RTC_Interrupt_Source_WeekALE:
            RTC->IE.WALE = 0;
            break;
        default:
            break;
    }
    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
    return;
}

/***************************************************************
  ��������RTC_GetITStatus
  ��  ������ȡʵʱʱ�ӵ�ĳЩ�ж�״̬
  ����ֵ��src: ʵʱʱ�ӵ��ж�Դ
  ���ֵ����
  ����ֵ���жϱ�־
 ***************************************************************/
ITStatus RTC_GetITStatus(RTC_Interrupt_Source src)
{
    ITStatus result = RESET;

    switch (src) 
    {
        case RTC_Interrupt_Source_Second:
            if(RTC->IE.SCDIE)
            result = SET;
            break;
        case RTC_Interrupt_Source_Minute:
            if(RTC->IE.MINIE)
                result = SET;
            break;
        case RTC_Interrupt_Source_Hour:
            if(RTC->IE.HORIE)
                result = SET;
            break;
        case RTC_Interrupt_Source_Day:
            if(RTC->IE.DAYIE)
                result = SET;
            break;
        case RTC_Interrupt_Source_Month:
            if(RTC->IE.MONIE)
                result = SET;
            break;
        case RTC_Interrupt_Source_DayALE:
            if(RTC->IE.DALE)
                result = SET;
            break;
        case RTC_Interrupt_Source_WeekALE:
            if(RTC->IE.WALE)
                result = SET;
            break;
        default:
            result = RESET;
            break;
    }

    return result;
}

/***************************************************************
  ��������RTC_GetFlagStatus
  ��  ������ȡʵʱʱ�ӵ�ĳЩ�жϱ�־
  ����ֵ��src: ʵʱʱ�ӵ��ж�Դ
  ���ֵ����
  ����ֵ���жϱ�־
 ***************************************************************/
FlagStatus RTC_GetFlagStatus(RTC_Interrupt_Source src)
{
    FlagStatus result = RESET;

    switch (src) 
    {
        case RTC_Interrupt_Source_Second:
            if(RTC->IF.SCDIF)
                result = SET;
            break;
        case RTC_Interrupt_Source_Minute:
            if(RTC->IF.MINIF)
                result = SET;
            break;
        case RTC_Interrupt_Source_Hour:
            if(RTC->IF.HORIF)
                result = SET;
            break;
        case RTC_Interrupt_Source_Day:
            if(RTC->IF.DAYIF)
                result = SET;
            break;
        case RTC_Interrupt_Source_Month:
            if(RTC->IF.MONIF)
                result = SET;
            break;
        case RTC_Interrupt_Source_DayALE:
            if(RTC->IF.DAFG)
                result = SET;
            break;
        case RTC_Interrupt_Source_WeekALE:
            if(RTC->IF.WAFG)
                result = SET;
            break;
        default:
            result = RESET;
            break;
    }

    return result;
}

/***************************************************************
  ��������RTC_ClearITPendingBit
  ��  �������ָ�����жϱ�־λ
  ����ֵ��src: ʵʱʱ�ӵ��ж�Դ
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void RTC_ClearITPendingBit(RTC_Interrupt_Source src)
{
    uint32_t flag;

    /* ���RTCд���� */
    flag = RTC->WP.WP;
    if (flag == 0x00000000)
        RTC->WP.WP = 0x55AAAA55;

    switch (src)
    {
        case RTC_Interrupt_Source_Second:
            RTC->IF.Word = RTC_Interrupt_Source_Second;
            break;
        case RTC_Interrupt_Source_Minute:
            RTC->IF.Word = RTC_Interrupt_Source_Minute;
            break;
        case RTC_Interrupt_Source_Hour:
            RTC->IF.Word = RTC_Interrupt_Source_Hour;
            break;
        case RTC_Interrupt_Source_Day:
            RTC->IF.Word = RTC_Interrupt_Source_Day;
            break;
        case RTC_Interrupt_Source_Month:
            RTC->IF.Word = RTC_Interrupt_Source_Month;
            break;
        case RTC_Interrupt_Source_DayALE:
            RTC->IF.Word = RTC_Interrupt_Source_DayALE;
            break;
        case RTC_Interrupt_Source_WeekALE:
            RTC->IF.Word = RTC_Interrupt_Source_WeekALE;
            break;
        default:

            break;
    }

    /* ����RTCд���� */
    if (flag == 0x00000000)
        RTC->WP.WP = 0x00000000;
    return;
}

/*************************END OF FILE**********************/


