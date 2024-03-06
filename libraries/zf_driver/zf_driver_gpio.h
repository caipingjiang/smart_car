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
* �ļ�����          zf_driver_gpio
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 8.32.4 or MDK 5.33
* ����ƽ̨          RT1064DVL6A
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/

#ifndef _zf_driver_gpio_h_
#define _zf_driver_gpio_h_

#include "MIMXRT1064.h"
#include "zf_common_typedef.h"
#include "fsl_gpio.h"


extern GPIO_Type * PORTPTR[];



typedef enum                                                                    // ö�� GPIO ����  ��ö�ٶ��岻�����û��޸�
{
    B0  = (32* 1 + 0 ), B1 ,    B2 ,    B3 ,    
    B9  = (32* 1 + 9 ), B10,    B11,    B12,    B13,    B14,    B15,
    B16 ,               B17,    B18,    B19,    B20,    B21,    B22,    B23,
    B24 ,               B25,    B26,    B27,    B28,    B29,    B30,    B31,
    
    C0  = (32* 2 + 0 ), C1 ,    C2 ,    C3 ,    C4 ,    C5 ,    C6 ,    C7 ,
    C8 ,                C9 ,    C10,    C11,    C12,    C13,    C14,    C15,
    C16,                C17,    C18,    C19,    C20,    C21,    C22,    C23,
    C24,                C25,    C26,    C27,    C28,    C29,    C30,    C31,

    D0  = (32* 3 + 0 ), D1 ,    D2 ,    D3 ,    D4 ,
    D12 = (32* 3 + 12), D13,    D14,    D15,
    D16,                D17,    
    D26 = (32* 3 + 26), D27,    
}gpio_pin_enum;



typedef enum                                                                    // ö�ٶ˿ڸ���   ��ö�ٶ��岻�����û��޸�
{
    GPIO_AF0            = 0x00,                                                 // ���Ÿ��ù���ѡ��  0
    GPIO_AF1            = 0x01,                                                 // ���Ÿ��ù���ѡ��  1
    GPIO_AF2            = 0x02,                                                 // ���Ÿ��ù���ѡ��  2
    GPIO_AF3            = 0x03,                                                 // ���Ÿ��ù���ѡ��  3
    GPIO_AF4            = 0x04,                                                 // ���Ÿ��ù���ѡ��  4
    GPIO_AF5            = 0x05,                                                 // ���Ÿ��ù���ѡ��  5
    GPIO_AF6            = 0x06,                                                 // ���Ÿ��ù���ѡ��  6
    GPIO_AF7            = 0x07,                                                 // ���Ÿ��ù���ѡ��  7
    GPIO_AF8            = 0x08,                                                 // ���Ÿ��ù���ѡ��  8
    GPIO_AF9            = 0x09,                                                 // ���Ÿ��ù���ѡ��  9
    GPIO_AF10           = 0x0A,                                                 // ���Ÿ��ù���ѡ�� 10
    GPIO_AF11           = 0x0B,                                                 // ���Ÿ��ù���ѡ�� 11
    GPIO_AF12           = 0x0C,                                                 // ���Ÿ��ù���ѡ�� 12
    GPIO_AF13           = 0x0D,                                                 // ���Ÿ��ù���ѡ�� 13
    GPIO_AF14           = 0x0E,                                                 // ���Ÿ��ù���ѡ�� 14
    GPIO_AF15           = 0x0F,                                                 // ���Ÿ��ù���ѡ�� 15
}gpio_af_enum;


typedef enum
{
    // ��һ���ò��������Ը��������Լ����
    HYS_EN              = 1<<IOMUXC_SW_PAD_CTL_PAD_HYS_SHIFT,                   //�ͺ�ʹ��
            
    PULLDOWN_100K       = 0<<IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT,                   //�˿�Ϊ����ʱ��Ч
    PULLUP_47K          = 1<<IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT,                   //�˿�Ϊ����ʱ��Ч
    PULLUP_100K         = 2<<IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT,                   //�˿�Ϊ����ʱ��Ч
    PULLUP_22K          = 3<<IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT,                   //�˿�Ϊ����ʱ��Ч
        
    PULL_EN             = 1<<IOMUXC_SW_PAD_CTL_PAD_PKE_SHIFT | 1<<IOMUXC_SW_PAD_CTL_PAD_PUE_SHIFT,
    KEEPER_EN           = 1<<IOMUXC_SW_PAD_CTL_PAD_PKE_SHIFT,                   //������ʹ��
                
    OD_EN               = 1<<IOMUXC_SW_PAD_CTL_PAD_ODE_SHIFT,                   //��©ʹ��
        
    SPEED_50MHZ         = 0<<IOMUXC_SW_PAD_CTL_PAD_SPEED_SHIFT,
    SPEED_100MHZ        = 1<<IOMUXC_SW_PAD_CTL_PAD_SPEED_SHIFT,
    SPEED_200MHZ        = 3<<IOMUXC_SW_PAD_CTL_PAD_SPEED_SHIFT,
        
    DSE_DIS             = 0<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //�������ǿ������
    DSE_R0              = 1<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //3.3Vʱ150ohm  1.8Vʱ260ohm
    DSE_R0_2            = 2<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //R/2
    DSE_R0_3            = 3<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //R/3
    DSE_R0_4            = 4<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //R/4
    DSE_R0_5            = 5<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //R/5
    DSE_R0_6            = 6<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //R/6
    DSE_R0_7            = 7<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //R/7
            
    SRE_SLOW            = 0<<IOMUXC_SW_PAD_CTL_PAD_SRE_SHIFT,
    SRE_FAST            = 1<<IOMUXC_SW_PAD_CTL_PAD_SRE_SHIFT,
    
    // ������ò�������ݵ��ڲ���
    GPI_ANAOG_IN        = SPEED_100MHZ | DSE_R0_6,                              // ģ������
    GPI_FLOATING_IN     = SPEED_100MHZ | DSE_R0,                                // ��������
    GPI_PULL_DOWN       = SPEED_100MHZ | DSE_R0 | PULLDOWN_100K | PULL_EN,      // ��������
    GPI_PULL_UP         = SPEED_100MHZ | DSE_R0 | PULLUP_47K    | PULL_EN,      // ��������
        
    GPO_PUSH_PULL       = SPEED_100MHZ | DSE_R0,                                // �������
    GPO_OPEN_DTAIN      = SPEED_100MHZ | DSE_R0 | OD_EN,                        // ��©���
    GPO_AF_PUSH_PULL    = SPEED_100MHZ | DSE_R0,                                // �����������
    GPO_AF_OPEN_DTAIN   = SPEED_100MHZ | DSE_R0 | OD_EN,                        // ���ÿ�©���
    
    // ����GPIO���ò���
    FAST_GPI_PULL_DOWN  = SPEED_200MHZ | DSE_R0 | PULLDOWN_100K | PULL_EN,      // ��������
    FAST_GPI_PULL_UP    = SPEED_200MHZ | DSE_R0 | PULLUP_47K    | PULL_EN,      // ��������
    
    FAST_GPO_PUSH_PULL  = SPEED_200MHZ | DSE_R0,

}gpio_mode_enum;


typedef enum // ö�ٶ˿ڷ���
{
    GPI         = 0x00, // ����ܽ����뷽��      
    GPO         = 0x01, // ����ܽ��������
}gpio_dir_enum;

typedef enum // ö�ٶ˿ڵ�ƽ
{
    GPIO_LOW    = 0x00, // ����ܽų�ʼ����ƽΪ��      
    GPIO_HIGH   = 0x01, // ����ܽų�ʼ����ƽΪ��
}gpio_level_enum;


//���Ÿ�������----------------------------------------------------
void        afio_init(uint32 muxRegister, uint32 muxMode, uint32 inputRegister, uint32 inputDaisy, uint32 configRegister, uint32 inputOnfield, uint32 pinconf);
void        gpio_iomuxc(gpio_pin_enum pin, uint32 pinconf);


//ͨ��GPIO����---------------------------------------------------
void        gpio_set_level              (gpio_pin_enum pin, uint8 dat);
uint8       gpio_get_level              (gpio_pin_enum pin);
void        gpio_toggle_level           (gpio_pin_enum pin);
void        gpio_set_dir                (gpio_pin_enum pin, gpio_dir_enum dir, gpio_mode_enum pinconf);
void        gpio_init                   (gpio_pin_enum pin, gpio_dir_enum dir, uint8 dat, uint32 pinconf);

//-------------------------------------------------------------------------------------------------------------------
// �������     ��Ӧ IO ��λΪ�͵�ƽ
// ����˵��     x           ѡ������� (��ѡ��Χ�� zf_driver_gpio.h �� gpio_pin_enum ö��ֵȷ��)
// ���ز���     void
// ʹ��ʾ��     gpio_low(B5);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
#define     gpio_low(pin)               GPIO_ClearPinsOutput(PORTPTR[pin >> 5],1 << (pin & 0x1f))

//-------------------------------------------------------------------------------------------------------------------
// �������     ��Ӧ IO ��λΪ�ߵ�ƽ
// ����˵��     x           ѡ������� (��ѡ��Χ�� zf_driver_gpio.h �� gpio_pin_enum ö��ֵȷ��)
// ���ز���     void
// ʹ��ʾ��     gpio_high(B5);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
#define     gpio_high(pin)              GPIO_SetPinsOutput(PORTPTR[pin >> 5],1 << (pin & 0x1f))


#ifdef COMPATIBLE_WITH_OLDER_VERSIONS                                           // ���ݾɰ汾��Դ��ӿ�����
#define     gpio_set(pin, dat)          (gpio_set_level((pin), (dat)))
#define     gpio_get(pin)               (gpio_get_level((pin)))
#define     gpio_dir(pin, dir, mode)    (gpio_set_dir((pin), (dir), (mode)))
#define     gpio_toggle(pin)            (gpio_toggle_level((pin)))
#endif


#define     PORTB_DR           		    GPIO1->DR                   // B�˿���������Ĵ���
#define     PORTC_DR           		    GPIO2->DR                   // C�˿���������Ĵ���
#define     PORTD_DR           		    GPIO3->DR                   // D�˿���������Ĵ���


//------------------------------------------------------
//���º�������ʵ�ֿ���GPIO�Ĳ���������GPIO��߿ɴ�150M��IO��ת�ٶ�


void        fast_gpio_set_level         (gpio_pin_enum pin, uint8 dat);
uint8       fast_gpio_get_level         (gpio_pin_enum pin);
void        fast_gpio_toggle_level      (gpio_pin_enum pin);
void        fast_gpio_set_dir           (gpio_pin_enum pin, gpio_dir_enum dir, gpio_mode_enum pinconf);
void        fast_gpio_init              (gpio_pin_enum pin, gpio_dir_enum dir, uint8 dat, uint32 pinconf);

#define     PORTB_FAST_DR               GPIO6->DR                   // B�˿���������Ĵ���
#define     PORTC_FAST_DR               GPIO7->DR                   // C�˿���������Ĵ���
#define     PORTD_FAST_DR               GPIO8->DR                   // D�˿���������Ĵ���
                                                                    
#define     PORTB_FAST_PSR              GPIO6->PSR                  // B�˿���������Ĵ���
#define     PORTC_FAST_PSR              GPIO7->PSR                  // C�˿���������Ĵ���
#define     PORTD_FAST_PSR              GPIO8->PSR                  // D�˿���������Ĵ���
                                                                    
#define     PORTB_FAST_SET(X)           GPIO6->DR_SET    = 1<<X     // B�˿ڿ���GPIO��һ�Ĵ���     Xѡ��˿ں� 5����ʾB5
#define     PORTC_FAST_SET(X)           GPIO7->DR_SET    = 1<<X     // C�˿ڿ���GPIO��һ�Ĵ���     Xѡ��˿ں� 5����ʾC5
#define     PORTD_FAST_SET(X)           GPIO8->DR_SET    = 1<<X     // D�˿ڿ���GPIO��һ�Ĵ���     Xѡ��˿ں� 5����ʾD5
                                                                                                
#define     PORTB_FAST_CLR(X)           GPIO6->DR_CLEAR  = 1<<X     // B�˿ڿ���GPIO�õͼĴ���     Xѡ��˿ں� 5����ʾB5
#define     PORTC_FAST_CLR(X)           GPIO7->DR_CLEAR  = 1<<X     // C�˿ڿ���GPIO�õͼĴ���     Xѡ��˿ں� 5����ʾC5
#define     PORTD_FAST_CLR(X)           GPIO8->DR_CLEAR  = 1<<X     // D�˿ڿ���GPIO�õͼĴ���     Xѡ��˿ں� 5����ʾD5
                                                                                                
#define     PORTB_FAST_TOGGLE(X)        GPIO6->DR_TOGGLE = 1<<X     // B�˿ڿ���GPIOȡ���Ĵ���     Xѡ��˿ں� 5����ʾB5
#define     PORTC_FAST_TOGGLE(X)        GPIO7->DR_TOGGLE = 1<<X     // C�˿ڿ���GPIOȡ���Ĵ���     Xѡ��˿ں� 5����ʾC5
#define     PORTD_FAST_TOGGLE(X)        GPIO8->DR_TOGGLE = 1<<X     // D�˿ڿ���GPIOȡ���Ĵ���     Xѡ��˿ں� 5����ʾD5






#endif
