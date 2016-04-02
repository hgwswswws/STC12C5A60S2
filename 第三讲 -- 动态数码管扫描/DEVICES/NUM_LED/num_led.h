
/*****************************************************************************
 **************       ��ѧ������������ -- E.D.D     ***************************
 *****************************************************************************
 *  �����ڵ���������12��ѧϰ�壬STC12@32M����
 *  File name: num_led.h
 *  Author: E.D.D
 *  Date: 2016-1-20 
 *  Version: V2.0
 *  Description: �����ͷ�ļ�
 *  Copyright (C) E.D.D -- HPU
 *****************************************************************************/

#ifndef  __NUM_LED_H_
#define  __NUM_LED_H_

#include <STC12C5A60S2.H>
#include "CTypes.h"

void NUM_LED_Init(void);
void NUM_ShowScan(void);
void NUM_ShowLED(uint8 dt);
void NUM_Shownum(uint32 longnum);

#endif
