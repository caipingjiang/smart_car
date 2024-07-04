/*********************************************************************************************************************
* MCX Vision Opensourec Library 即（MCX Vision 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2024 SEEKFREE 逐飞科技
* 
* 本文件是 MCX Vision 开源库的一部分
* 
* MCX Vision 开源库 是免费软件
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
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MDK 5.38a
* 适用平台          MCX Vision
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2024-04-21        ZSY            first version
********************************************************************************************************************/
#include "zf_model_process.h"
#if defined(__cplusplus)
extern "C" // mian文件是C++文件，如果需要包含C语言的头文件，就需要使用extern "C"
{
#endif /* __cplusplus */ 
#include "zf_common_headfile.h"

// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完

// 核心板下载完代码需要手动复位！！！
// 核心板下载完代码需要手动复位！！！
// 核心板下载完代码需要手动复位！！！.
    
// 如果程序运行后，模块上的Core灯闪烁，说明程序进入了HardFault，就需要检测是否有数组越界，外设没有初始化，外设时钟没有设置等情况
    
// *************************** 例程测试说明 ***************************
// 1.使用DAP下载器连接模块,将IPS2.0屏幕插到模块上，注意引脚方向
// 
// 2.MCX Vision下载本例程，
// 
// 3.复位核心板（需要手动复位） 
// 
// 4.屏幕会显示实时图像并运行模型框出目标
//
// 5.DEBUG和用户串口会输出目标的信息，具体在zf_model_process.cpp文件的zf_model_odresult_out函数查看
//   如果将用户串口连接1064的串口4，使用提供的1064例程，可以接收并解析目标检测的数据

// *************************** 例程注意事项 ***************************
// 1.默认的分辨率是QVGA，摄像头的分辨率可以再zf_device_scc8660.h文件中修改FRAME_SIZE宏定义
//
// 2.如果不加屏幕显示，QVGA和QQVGA的帧率约30帧，加了屏幕显示，QVGA约20帧，QQVGA约30帧
//
// 3.注意，QVGA图像数组加模型占用基本占满整个RAM，无法添加其他的算法，如果需要写其他算法，建议去掉模型或者使用QQVGA像素
//
// 4.模型的训练参考MCX Vision说明书
//
// **************************** 代码区域 ****************************
    
int main(void)
{
    // 时钟和调试串口-串口4初始化
    zf_board_init();
    // 用户串口-串口5初始化
    user_uart_init();
    // 延时300ms
    system_delay_ms(300);
    // 使用C++编译无法使用printf，可以使用zf_debug_printf和zf_user_printf替代
    zf_debug_printf("debug_uart_init_finish\r\n");  // 使用调试串口-串口4发送数据
    zf_user_printf("user_uart_init_finish\r\n");    // 使用用户串口-串口5发送数据

    // 屏幕初始化
    ips200_init();
    // 摄像头初始化
    scc8660_init();
    // 模型初始化，模型的输出阈值修改函数中的postProcessParams.threshold参数，范围是0 - 1，默认为0.4，参数越小，越容易识别到目标
    zf_model_init();
    while (1)
    {	ips200_draw_line(160-2, 170, 160+2,170,RGB565_RED);
        if(scc8660_finish)
        {
            scc8660_finish = 0;
            // 模型运行并显示图像
            zf_model_run();
        }
    }
}

// **************************** 代码区域 ****************************
#if defined(__cplusplus)
}
#endif /* __cplusplus */