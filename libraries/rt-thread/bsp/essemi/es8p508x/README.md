# HRSDK-GDB-ES8P508 开发板 BSP 说明
标签： EastSoft、国产MCU、Cortex-M0、ES8P5088FLLQ

## 1. 简介

本文档为上海东软载波微电子开发团队为 HRSDK-GDB-ES8P508 开发板提供的 BSP (板级支持包) 说明。
通过阅读本文档，开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。

### 1.1  开发板介绍

主要内容如下：
HRSDK-GDB-ES8P508x 是东软载波微电子官方推出的一款基于 ARM Cortex-M0 内核的开发板，最高主频为 48MHz，可满足基础功能测试及高端功能扩展等开发需求。

开发板外观如下图所示：

HRSDK-GDB-ES8P508x-V1.0

![ES8P508](figures/HRSDK-GDB-ES8P508x-V1.0.jpg)

该开发板常用 **板载资源** 如下：

- MCU：ES8P5088FLLQ，主频 48MHz，24KB SRAM，128KB FLASH，45 GPIOs
- 常用外设
  - LED：1个，(PA14)
  - 按键：1个(MRSTN)
- 常用接口：GPIO、UART、SPI、I2C
- 调试接口，ESLinkⅡ(EastSoft 官方推出的开发工具，有标准版和mini版两种版本，均自带 CDC 串口功能) SWD 下载

外设支持:

本 BSP 目前对外设的支持情况如下：

| **片上外设**      | **支持情况** | **备注**                            |
| :---------------- | :----------: | :-----------------------------------|
| GPIO              |     支持     | 45 GPIOs                            |
| UART              |     支持     | UART0/1/2/3/4/5                     |


更多详细信息请咨询[上海东软载波微电子技术支持](http://www.essemi.com/)

## 2. 快速上手

本 BSP 为开发者提供 MDK4 工程。下面以 MDK4 开发环境为例，介绍如何将系统运行起来。

### 硬件连接

使用 ESLinkⅡ (自带 CDC 串口)或 Jlink 等调试工具连接开发板到 PC，拨动开关选择使用调试工具供电或使用外部电源供电。若使用 Jlink 等调试工具，还需要将 UART5_TX(PB13)、UART5_RX(PB12)、GND 接到串口工具上。

使用ESlinkⅡ(mini)连接开发板如下图所示：

ESLinkⅡ(mini) + HRSDK-GDB-ES8P508-V1.0

![ESLinkII](figures/ESLinkII-mini.jpg)

### 编译下载

双击 project.uvprojx 文件，打开 MDK4 工程，工程默认配置使用 JLink 下载程序，在通过 JLink 连接开发板的基础上，点击下载按钮即可下载程序到开发板，如果使用 ESLinkⅡ，则选择 "CMSIS-DAP Debugger"，连接正常后即可编译并下载程序到开发板。

### 运行结果

下载程序成功之后，系统会自动运行，观察串口输出的信息，同时开发板LED闪烁。

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.2 build Jul 12 2019
 2006 - 2019 Copyright by rt-thread team
msh />
```
## 3. 进阶使用

此 BSP 默认只开启了 GPIO 和 uart5 的功能，如果需使用 SPI 等更多高级功能，需要利用 ENV 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=MDK4` 命令重新生成工程。

更多 Env 工具的详细介绍请参考 [RT-Thread 文档中心](https://www.rt-thread.org/document/site/)

## 4. 联系人信息

- [wangyongquan](https://github.com/wangyq2018) 

## 5. 参考

- [ EastSoft 官网](http://www.essemi.com)

