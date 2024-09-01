/*********************************************************************************************************************
* MCX Vision Opensourec Library ����MCX Vision ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2024 SEEKFREE ��ɿƼ�
* 
* ���ļ��� MCX Vision ��Դ���һ����
* 
* MCX Vision ��Դ�� ��������
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
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          zf_driver_gpio
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MDK 5.38a
* ����ƽ̨          MCX Vision
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2024-04-21        ZSY            first version
********************************************************************************************************************/
#include "zf_driver_gpio.h"

#define PORT_CLOCKS                                                          \
    {                                                                        \
        kCLOCK_Port0, kCLOCK_Port1, kCLOCK_Port2, kCLOCK_Port3, kCLOCK_Port4 \
    }
    
static GPIO_Type *const s_gpioBases[] = GPIO_BASE_PTRS;
static const clock_ip_name_t s_gpioclock[] = GPIO_CLOCKS;
static const clock_ip_name_t s_portclock[] = PORT_CLOCKS;
static PORT_Type *s_portbaseptrs[] = PORT_BASE_PTRS;

const port_pin_config_t pullup_config = {
                                            kPORT_PullUp,
                                            kPORT_LowPullResistor,
                                            kPORT_FastSlewRate,
                                            kPORT_PassiveFilterDisable,
                                            kPORT_OpenDrainDisable,
                                            kPORT_HighDriveStrength,
                                            kPORT_MuxAlt0,
                                            kPORT_InputBufferEnable,
                                            kPORT_InputNormal,
                                            kPORT_UnlockRegister};

const port_pin_config_t pulldown_config = {
                                            kPORT_PullDown,
                                            kPORT_LowPullResistor,
                                            kPORT_FastSlewRate,
                                            kPORT_PassiveFilterDisable,
                                            kPORT_OpenDrainDisable,
                                            kPORT_LowDriveStrength,
                                            kPORT_MuxAlt0,
                                            kPORT_InputBufferEnable,
                                            kPORT_InputNormal,
                                            kPORT_UnlockRegister};

const port_pin_config_t opendrain_config = {
                                            kPORT_PullDisable,
                                            kPORT_LowPullResistor,
                                            kPORT_FastSlewRate,
                                            kPORT_PassiveFilterDisable,
                                            kPORT_OpenDrainEnable,
                                            kPORT_LowDriveStrength,
                                            kPORT_MuxAlt0,
                                            kPORT_InputBufferEnable,
                                            kPORT_InputNormal,
                                            kPORT_UnlockRegister};    
                                            
//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO�������
//  @param      pin         ѡ������� (��ѡ��Χ�� common.h ��gpio_pin_enumö��ֵȷ��)
//  @param      dat         0���͵�ƽ 1���ߵ�ƽ
//  @return     void
//  Sample usage:           gpio_set(B9, 1);//B9 ����ߵ�ƽ
//-------------------------------------------------------------------------------------------------------------------
void gpio_set_level(gpio_struct gpio_t, uint8 dat)
{
    GPIO_PinWrite(gpio_t.gpio, (gpio_t.pin), dat);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO״̬��ȡ
//  @param      pin         ѡ������� (��ѡ��Χ�� common.h ��gpio_pin_enumö��ֵȷ��)
//  @return     uint8       0���͵�ƽ 1���ߵ�ƽ
//  Sample usage:           uint8 status = gpio_get(B9);//��ȡB9���ŵ�ƽ
//-------------------------------------------------------------------------------------------------------------------
uint8 gpio_get_level(gpio_struct gpio_t)
{
    return (GPIO_PinRead(gpio_t.gpio,(gpio_t.pin)));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO ��ת
//  @param      pin         ѡ������� (��ѡ��Χ�� common.h ��gpio_pin_enumö��ֵȷ��)
//  @return     void        
//  Sample usage:           gpio_toggle(B9);//B9���ŵ�ƽ��ת
//-------------------------------------------------------------------------------------------------------------------
void gpio_toggle_level(gpio_struct gpio_t)
{
    GPIO_PortToggle(gpio_t.gpio,1<<(gpio_t.pin));
}

void gpio_set_dir(gpio_struct gpio_t, gpio_dir_enum dir)
{
    if (GPI == dir)
    {
        gpio_t.gpio->PDDR &= GPIO_FIT_REG(~(1UL << gpio_t.pin));
    }
    else
    {
        gpio_t.gpio->PDDR |= GPIO_FIT_REG((1UL << gpio_t.pin));
    }
}

void gpio_init(gpio_struct gpio_t, gpio_dir_enum dir, uint8 dat, gpio_mode_enum mode)
{
    gpio_pin_config_t gpio_config;
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0U; instance < ARRAY_SIZE(s_gpioBases); instance++)
    {
        if (s_gpioBases[instance] == gpio_t.gpio)
        {
            break;
        }
    }
    
    if ((instance < ARRAY_SIZE(s_gpioclock)) && (kCLOCK_IpInvalid != s_gpioclock[instance]))
    {
        CLOCK_EnableClock(s_gpioclock[instance]);
        CLOCK_EnableClock(s_portclock[instance]);
    }
    
    switch(mode)
    {
        case PULL_UP:
        {
            PORT_SetPinConfig(s_portbaseptrs[instance], gpio_t.pin, &pullup_config);
            break;
        }
        case PULL_DOWN:
        {
            PORT_SetPinConfig(s_portbaseptrs[instance], gpio_t.pin, &pulldown_config);
            break;
        }
        case OPEN_DTAIN:
        {
            PORT_SetPinConfig(s_portbaseptrs[instance], gpio_t.pin, &opendrain_config);
            break;
        }
    }
    
    if(GPO == dir)      
    {
        gpio_config.pinDirection = kGPIO_DigitalOutput; 
        
    }
    else if(GPI == dir) 
    {
        gpio_config.pinDirection = kGPIO_DigitalInput;
    }
    
    if(dat)     gpio_config.outputLogic =  1;
    else        gpio_config.outputLogic =  0;

    GPIO_PinInit(gpio_t.gpio, gpio_t.pin, &gpio_config);
}