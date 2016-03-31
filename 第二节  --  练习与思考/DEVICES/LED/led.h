
#ifndef  __LED_H_
#define  __LED_H_

/*****************************************************************************
 **************       大学生电器开发部 -- E.D.D     ***************************
 *****************************************************************************
 *  适用于电器开发部15级学习板，STC15@32M晶振
 *  File name：led.h
 *  Author: E.D.D
 *  Date: 2016-1-20 
 *  Version: V2.0
 *  Description: led头文件
 *  Copyright (C) E.D.D -- HPU
 *****************************************************************************/
 
#include <STC12C5A60S2.H>
#include "CTypes.h"
#include "delay.h"

void Led_Init(void);
void Led_Scan(void);

#endif
