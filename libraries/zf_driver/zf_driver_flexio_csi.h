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
* 文件名称          zf_driver_flexio_csi
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

#ifndef _zf_driver_flexio_csi_h_
#define _zf_driver_flexio_csi_h_


#include "zf_common_typedef.h"
#include "fsl_edma.h"


//此枚举定义不允许用户修改
typedef enum    //FLEXIO 引脚定义
{
    FLEXIO2_D00_C0,
    FLEXIO2_D01_C1,
    FLEXIO2_D02_C2,
    FLEXIO2_D03_C3,
    FLEXIO2_D04_C4,
    FLEXIO2_D05_C5,
    FLEXIO2_D06_C6,
    FLEXIO2_D07_C7,
    FLEXIO2_D08_C8,
    FLEXIO2_D09_C9,
    FLEXIO2_D10_C10,
    FLEXIO2_D11_C11,
    FLEXIO2_D12_C12,
    FLEXIO2_D13_C13,
    FLEXIO2_D14_C14,
    FLEXIO2_D15_C15,
    FLEXIO2_D16_C16,
    FLEXIO2_D17_C17,
    FLEXIO2_D18_C18,
    FLEXIO2_D19_C19,
    FLEXIO2_D20_C20,
    FLEXIO2_D21_C21,
    FLEXIO2_D22_C22,
    FLEXIO2_D23_C23,
    FLEXIO2_D24_C24,
    FLEXIO2_D25_C25,
    FLEXIO2_D26_C26,
    FLEXIO2_D27_C27,
    FLEXIO2_D28_C28,
    FLEXIO2_D29_C29,
    FLEXIO2_D30_C30,
    FLEXIO2_D31_C31,
}flexio_pin_enum;






void flexio_csi_enable(uint8 enable);
void flexio_csi_flag_clear(void);
void flexio_csi_dma_restart(uint8 *dest_addr);
void flexio_csi_enable_rxdma(void);
void flexio_csi_init(flexio_pin_enum dat_pin_start, flexio_pin_enum pclk_pin, flexio_pin_enum href_pin, uint16 width, uint16 height, uint8 *dest_addr, edma_callback callback);

















#endif
