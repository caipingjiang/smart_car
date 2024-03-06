/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library 即（RT1064DVL6A 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 RT1064DVL6A 开源库的一部分
* 
* RT1064DVL6A 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
* 
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
* 
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
* 
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          zf_driver_encoder
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.33
* 适用平台          RT1064DVL6A
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/

#ifndef _zf_driver_encoder_h_
#define _zf_driver_encoder_h_

#include "zf_common_typedef.h"

typedef enum
{
    QTIMER1_ENCODER1_CH1_C0  = 2 * 2, 
    QTIMER1_ENCODER2_CH1_C2  = 3 * 2,
                                    
    QTIMER2_ENCODER1_CH1_C3  = 4 * 2,                                            
    QTIMER2_ENCODER2_CH1_C5  = 5 * 2, 
                                    
    QTIMER3_ENCODER1_CH1_B16 = 6 * 2, QTIMER3_ENCODER1_CH1_C6,                        
    QTIMER3_ENCODER2_CH1_B18 = 7 * 2, QTIMER3_ENCODER2_CH1_C8,                         
                                    
    QTIMER4_ENCODER1_CH1_C9  = 8 * 2,
    QTIMER4_ENCODER2_CH1_C11 = 9 * 2,
}encoder_channel1_enum;             
                                    
typedef enum                        
{                                   
    QTIMER1_ENCODER1_CH2_C1  = 2 * 2,
    QTIMER1_ENCODER2_CH2_C24 = 3 * 2,
                                            
    QTIMER2_ENCODER1_CH2_C4  = 4 * 2, QTIMER2_ENCODER1_CH2_C25,
    QTIMER2_ENCODER2_CH2_C25 = 5 * 2,
                                   
    QTIMER3_ENCODER1_CH2_B17 = 6 * 2, QTIMER3_ENCODER1_CH2_C7,                         
    QTIMER3_ENCODER2_CH2_B19 = 7 * 2, QTIMER3_ENCODER2_CH2_C26,  
                                            
    QTIMER4_ENCODER1_CH2_C10 = 8 * 2,
    QTIMER4_ENCODER2_CH2_C27 = 9 * 2,
}encoder_channel2_enum;

typedef enum
{
    QTIMER1_ENCODER1 = 2,
    QTIMER1_ENCODER2,
    
    QTIMER2_ENCODER1,
    QTIMER2_ENCODER2,
    
    QTIMER3_ENCODER1,
    QTIMER3_ENCODER2,
    
    QTIMER4_ENCODER1,
    QTIMER4_ENCODER2,
}encoder_index_enum;

int16   encoder_get_count       (encoder_index_enum encoder_n);
void    encoder_clear_count     (encoder_index_enum encoder_n);

void    encoder_quad_init       (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin);
void    encoder_dir_init        (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin);

#endif
