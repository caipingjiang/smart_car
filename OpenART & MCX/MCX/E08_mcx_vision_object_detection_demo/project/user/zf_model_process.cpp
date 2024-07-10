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
* �ļ�����          zf_model_process
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
// �������     ģ�͵�Ŀ����Ϣ���
// ����˵��     odres           Ŀ��ṹ��
// ����˵��     retcnt          Ŀ������
// ���ز���     void
// ʹ��ʾ��     zf_model_odresult_out(s_odrets, s_odretcnt);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
int16 target_point[2] = {160,220};  //�������Ĳο���
int16 set_distance = 170;           //�趨�ľ��룬С�ڴ˾�����Ϊ��Ƭ�Ѿ�����С��
int16 distance = 0;                 //���㿨Ƭ�ľ���
uint8 correct_flag = 0;             //������ɱ�־��1Ϊ��⵽��Ƭ
uint8 mistake_dection_cnt = 0;	   //��ʶ�����
void zf_model_odresult_out(const odresult_t* odres, int retcnt)
{
    uint16_t center_x = 0, center_y = 0, shortest = set_distance;
    correct_flag = 0;   //�����ϴα�־
	mistake_dection_cnt = 0;//�����ϴμ���
    if(retcnt == 0) //û�ҵ���Ƭ
    {
        zf_user_printf("@%d,%d,%d,%d#", center_x, center_y, distance, correct_flag);
        return;
    }
    for(int i = 0; i < retcnt; i++, odres++)    //����ÿ��ͼƬ�м�⵽�Ŀ�Ƭ
    {
        zf_debug_printf("sc:%d,x1:%d,y1:%d,x2:%d,y2:%d\r\n",
                        (int)(odres->score*100), odres->x1, odres->y1, odres->x2, odres->y2);
        
        // ͨ���û�����-����5�������ݣ�ͨ��������Ƭ������
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
		//���˵�һЩ��ʶ����������ʱ��������ʶ��
		if(temp_y>SCC8660_H-5 || temp_w*temp_h<800 || temp_w/temp_h>4)
		{
			mistake_dection_cnt++;
			continue;
		}
        distance = sqrt( pow(temp_x - target_point[0], 2) + pow(temp_y - target_point[1], 2) );
        if(distance<shortest)       //�����������Ŀ�Ƭ
        {
            shortest = distance;
            center_x = (odres->x1 + odres->x2)/2;
            center_y = (odres->y1 + odres->y2)/2;
        }
    }
	if(mistake_dection_cnt == retcnt)	//ȫ��Ϊ��ʶ��
	{
		center_x = 0;
		center_y = 0;
        correct_flag = 0;
		zf_user_printf("@%d,%d,%d,%d#", center_x, center_y, distance, correct_flag);
		return;
	}
    if(center_x != 0 && center_y != 0 && mistake_dection_cnt==0)  //��Ϊ�㣬˵�������if�ж�ִ�й�
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
// �������     ģ�ͳ�ʼ��
// ���ز���     void
// ʹ��ʾ��     zf_model_init();
// ��ע��Ϣ     
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
// �������     ģ������
// ���ز���     void
// ʹ��ʾ��     zf_model_run();
// ��ע��Ϣ     
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

