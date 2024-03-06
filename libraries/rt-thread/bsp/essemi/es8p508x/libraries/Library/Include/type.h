/*********************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *�ļ���:  type.h
 *��  ��:  Liut 
 *��  ��:  V1.01
 *��  ��:  2017/11/01
 *��  ��:  type define
 *��  ע:  ������HRSDK-GDB-8P508x
 ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
 **********************************************************/
#ifndef __TYPE_H__
#define __TYPE_H__

typedef enum {DISABLE = 0, ENABLE = !DISABLE} TYPE_FUNCEN,FuncState,TYPE_PINTIE,TYPE_PINTMASK,TYPE_BUZZEN;
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, PinStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;


#endif
