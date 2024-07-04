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
* 文件名称          zf_model_process
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

#include "model.h"
#include "yolo_post_processing.h"

#define MODEL_IN_W	                (160 )
#define MODEL_IN_H                  (128 )
#define MODEL_IN_C	                (3   )
#define MAX_OD_BOX_CNT              (12  )
#define SWAPBYTE(h)                 ((((uint16_t)h << 8)&0xFF00) | ((uint16_t)h >> 8))

typedef struct tagodresult_t
{
    union
    {
        int16_t xyxy[4];
        struct
        {
            int16_t x1;
            int16_t y1;
            int16_t x2;
            int16_t y2;
        };
    };
    float score;
    int label;
} odresult_t;

tensor_dims_t inputDims;
tensor_type_t inputType;
uint8_t* inputData;
tensor_dims_t outputDims;
tensor_type_t outputType;
uint8_t* outputData;
size_t arenaSize;
uint32_t out_size;
yolo::object_detection::PostProcessParams postProcessParams;
TfLiteTensor* outputTensor[3];
float* anchors;
std::vector<yolo::object_detection::DetectionResult> results;

int s_odretcnt = 0;
__attribute__((section(".model_input_buffer"))) volatile uint8_t __attribute((aligned(8))) model_input_buf[MODEL_IN_W * MODEL_IN_H * MODEL_IN_C] = {0};
odresult_t s_odrets[MAX_OD_BOX_CNT];

void draw_rect_on_slice_buffer(uint16_t* pcam, int srcw, int cury, int stride, odresult_t* podret, int retcnt, int slice_height)
{
    int i = 0;
    for(i = 0; i < retcnt; i++, podret++)
    {
        uint32_t color = RGB565_YELLOW;//RGB565_BLUE;//RGB565_PURPLE;//RGB565_RED;//0xffffffff;
        uint16_t* phorline = 0;
        int stripey1 = podret->y1 - cury;
        if(stripey1 >= 0 && stripey1 < slice_height)
        {
            for(int j = 0; j < 2 && stripey1 + j < slice_height; j++)
            {
                phorline = pcam + srcw * (j + stripey1) + podret->x1;
                memset(phorline, color, (podret->x2 - podret->x1) * 2);
            }
        }

        int stripey2 = podret->y2 - cury;
        if(stripey2 >= 0 && stripey2 < slice_height)
        {
            for(int j = 0; j < 2 && stripey2 + j < slice_height; j++)
            {
                phorline = pcam + srcw * (j + stripey2) + podret->x1;
                memset(phorline, color, (podret->x2 - podret->x1) * 2);
            }
        }

        uint16_t* pvtclinel = pcam + podret->x1;
        uint16_t* pvtcliner = pcam + podret->x2 - 2;

        for(int y = cury; y < cury + slice_height; y++)
        {
            if(y > podret->y1 && y < podret->y2)
            {
                memset(pvtclinel, color, 4);
                memset(pvtcliner, color, 4);
            }
            pvtclinel += srcw;
            pvtcliner += srcw;
        }

    }
}

void rgb565stridedtorgb888(const uint16_t* pin, int srcw, int wndw, int wndh, int wndx0, int wndy0,
                           uint8_t* p888, int stride, uint8_t issub128)
{
    const uint16_t* psrc = pin;
    uint32_t datin, datout, datouts[3];
    uint8_t* p888out = p888;

    for(int y = wndy0, y1 = (wndh - wndy0) / stride - wndy0; y < wndh; y += stride, y1--)
    {
        psrc = pin + srcw * y + wndx0;
        for(int x = 0; x < wndw; x += stride * 4)
        {
            datin = SWAPBYTE(psrc[0]);
            psrc += stride;
            datouts[0] = (datin & 31) << 19 | (datin & 63 << 5) << 5 | ((datin >> 8) & 0xf8);

            datin = SWAPBYTE(psrc[0]);
            psrc += stride;
            datout = (datin & 31) << 19 | (datin & 63 << 5) << 5 | ((datin >> 8) & 0xf8);
            datouts[0] |= datout << 24;
            datouts[1] = datout >> 8;

            datin = SWAPBYTE(psrc[0]);
            psrc += stride;
            datout = (datin & 31) << 19 | (datin & 63 << 5) << 5 | ((datin >> 8) & 0xf8);
            datouts[1] |= (datout << 16) & 0xffff0000;
            datouts[2] = datout >> 16;

            datin = SWAPBYTE(psrc[0]);
            psrc += stride;
            datout = (datin & 31) << 19 | (datin & 63 << 5) << 5 | ((datin >> 8) & 0xf8);

            datouts[2] |= datout << 8;

            if(issub128)
            {
                datouts[0] ^= 0x80808080;
                datouts[1] ^= 0x80808080;
                datouts[2] ^= 0x80808080;
            }
            memcpy(p888out, datouts, 3 * 4);
            p888out += 3 * 4;
        }
    }
}

void ezh_copy_slice_to_model_input(uint32_t idx, uint32_t cam_slice_buffer, uint32_t cam_slice_width, uint32_t cam_slice_height, uint32_t max_idx)
{
    static uint8_t* pCurDat;
    uint32_t curY;
    uint32_t s_imgStride = cam_slice_width / MODEL_IN_W;

    if(idx > max_idx)
    {
        return;
    }
    uint32_t ndx = idx;
    curY = ndx * cam_slice_height;
    int wndY = (s_imgStride - (curY - 0) % s_imgStride) % s_imgStride;

    pCurDat = (uint8*)model_input_buf + 3 * ((cam_slice_height * ndx + wndY) * cam_slice_width / s_imgStride / s_imgStride);

    if(curY + cam_slice_height >= 0)
    {
        rgb565stridedtorgb888((uint16_t*)cam_slice_buffer, cam_slice_width, cam_slice_width, cam_slice_height, 0, wndY, pCurDat, s_imgStride, 1);
    }
}
typedef struct
{
    uint16 res_x1;
    uint16 res_y1;
    uint16 res_x2;
    uint16 res_y2;
}od_result_t;
volatile od_result_t od_result;
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     模型的目标信息输出
// 参数说明     odres           目标结构体
// 参数说明     retcnt          目标数量
// 返回参数     void
// 使用示例     zf_model_odresult_out(s_odrets, s_odretcnt);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
int16 target_point[2] = {160,220};  //计算距离的参考点
int16 set_distance = 170;           //设定的距离，小于此距离认为卡片已经靠近小车
int16 distance = 0;                 //计算卡片的距离
uint8 correct_flag = 0;             //矫正完成标志，1为检测到卡片
uint8 mistake_dection_cnt = 0;	   //误识别计数
void zf_model_odresult_out(const odresult_t* odres, int retcnt)
{
    uint16_t center_x = 0, center_y = 0, shortest = set_distance;
    correct_flag = 0;   //清零上次标志
	mistake_dection_cnt = 0;//清零上次计数
    if(retcnt == 0) //没找到卡片
    {
        zf_user_printf("@%d,%d,%d,%d#", center_x, center_y, distance, correct_flag);
        return;
    }
    for(int i = 0; i < retcnt; i++, odres++)    //遍历每幅图片中检测到的卡片
    {
        zf_debug_printf("sc:%d,x1:%d,y1:%d,x2:%d,y2:%d\r\n",
                        (int)(odres->score*100), odres->x1, odres->y1, odres->x2, odres->y2);
        
        // 通过用户串口-串口5发送数据，通过其他单片机接收
        // od_result.res_x1 = odres->x1;
        // od_result.res_y1 = odres->y1;
        // od_result.res_x2 = odres->x2;
        // od_result.res_y2 = odres->y2;
        // user_uart_putchar(0xAA);
        // user_uart_putchar((uint8)i);
        // user_uart_write_buffer((const uint8*)(&od_result), sizeof(od_result));
        // user_uart_putchar(0xFF);
		
        int16_t temp_x = (odres->x1 + odres->x2)/2;
        int16_t temp_y = (odres->y1 + odres->y2)/2;
		int16_t temp_w = (odres->x2 - odres->x1);
		int16_t temp_h = (odres->y2 - odres->y1);
		//过滤掉一些误识别的情况（有时赛道会误识别）
		if(temp_y>SCC8660_H-5 || temp_w*temp_h<800 || temp_w/temp_h>4)
		{
			mistake_dection_cnt++;
			continue;
		}
        distance = sqrt( pow(temp_x - target_point[0], 2) + pow(temp_y - target_point[1], 2) );
        if(distance<shortest)       //更新最近距离的卡片
        {
            shortest = distance;
            center_x = (odres->x1 + odres->x2)/2;
            center_y = (odres->y1 + odres->y2)/2;
        }
    }
	if(mistake_dection_cnt == retcnt)	//全是为误识别
	{
		center_x = 0;
		center_y = 0;
        correct_flag = 0;
		zf_user_printf("@%d,%d,%d,%d#", center_x, center_y, distance, correct_flag);
		return;
	}
    if(center_x != 0 && center_y != 0 && mistake_dection_cnt==0)  //不为零，说明上面的if判断执行过
    {  
		
		ips200_show_int(center_x, center_y, center_x);
		ips200_show_int(center_x+30, center_y, center_y);
		ips200_show_int(center_x, center_y+20, shortest);
		ips200_show_int(center_x+30, center_y+20, sqrt( pow(center_x - 160, 2) + pow(center_y - 170, 2)));
        correct_flag = 1;
        zf_user_printf("@%d,%d,%d,%d#", center_x, center_y, distance, correct_flag);
        
    }

}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     模型初始化
// 返回参数     void
// 使用示例     zf_model_init();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void zf_model_init(void)
{
    if(MODEL_Init() != kStatus_Success)
    {
        zf_debug_printf("Failed initializing model");
        while(1);
    }
    size_t usedSize = MODEL_GetArenaUsedBytes(&arenaSize);
    zf_debug_printf("\r\n%d/%d kB (%0.2f%%) tensor arena used\r\n", usedSize / 1024, arenaSize / 1024, 100.0 * usedSize / arenaSize);

    inputData = MODEL_GetInputTensorData(&inputDims, &inputType);
    outputData = MODEL_GetOutputTensorData(&outputDims, &outputType);
    out_size = MODEL_GetOutputSize();

    postProcessParams.inputImgRows = (int)inputDims.data[1];
    postProcessParams.inputImgCols =	(int)inputDims.data[2];
    postProcessParams.output_size = (int)out_size;
    postProcessParams.originalImageWidth = SCC8660_W;
    postProcessParams.originalImageHeight = SCC8660_H;
    postProcessParams.threshold = 0.4;	//0.4
    postProcessParams.nms = 0.2;
    postProcessParams.numClasses = 1;
    postProcessParams.topN = 0;
    
    anchors = MODEL_GetAnchors();
    for(int i = 0; i < out_size; i ++)
    {
        outputTensor[i] = MODEL_GetOutputTensor(i);
        postProcessParams.anchors[i][0] = *(anchors + 6 * (out_size - 1 - i));
        postProcessParams.anchors[i][1] = *(anchors + 6 * (out_size - 1 - i) + 1);
        postProcessParams.anchors[i][2] = *(anchors + 6 * (out_size - 1 - i) + 2);
        postProcessParams.anchors[i][3] = *(anchors + 6 * (out_size - 1 - i) + 3);
        postProcessParams.anchors[i][4] = *(anchors + 6 * (out_size - 1 - i) + 4);
        postProcessParams.anchors[i][5] = *(anchors + 6 * (out_size - 1 - i) + 5);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     模型运行
// 返回参数     void
// 使用示例     zf_model_run();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void zf_model_run(void)
{
    uint8_t* buf = 0;
    memset(inputData, 0, inputDims.data[1]*inputDims.data[2]*inputDims.data[3]);
    buf = inputData + (inputDims.data[1] - MODEL_IN_H) / 2 * MODEL_IN_W * MODEL_IN_C;
    memcpy(buf, (uint8*)model_input_buf, MODEL_IN_W * MODEL_IN_H * MODEL_IN_C);

    results.clear();
    MODEL_RunInference();

    s_odretcnt = 0;
    if(!(yolo::DetectorPostProcess((const TfLiteTensor**)outputTensor,results, postProcessParams).DoPostProcess()))
    {
        s_odretcnt = 0;
    }
    for(const auto& result : results)
    {
        if(result.m_normalisedVal > postProcessParams.threshold)
        {
            s_odrets[s_odretcnt].x1 = result.m_x0;
            s_odrets[s_odretcnt].x2 = result.m_x0 + result.m_w;
            s_odrets[s_odretcnt].y1 = result.m_y0;
            s_odrets[s_odretcnt].y2 = result.m_y0 + result.m_h;
            s_odrets[s_odretcnt].score = result.m_normalisedVal;
            s_odretcnt ++;
        }
    }
#if IS_UART_OUTPUT_ODRESULT
    if(1)//if(s_odretcnt > 0)
    {
        zf_model_odresult_out(s_odrets, s_odretcnt);
    }
#endif
#if IS_SHOW_SCC8660
    if(s_odretcnt)
    {
        draw_rect_on_slice_buffer((scc8660_image), SCC8660_W,  0, 1, s_odrets, s_odretcnt, SCC8660_H);
    }
    ips200_show_scc8660(scc8660_image);
#endif

}

