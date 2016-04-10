
/*****************************************************************************
 **************       大学生电器开发部 -- E.D.D     ***************************
 *****************************************************************************
 *  适用于电器开发部12级学习板，STC12@32M晶振
 *  File name: usart.h
 *  Author: E.D.D
 *  Date: 2016-1-20 
 *  Version: V2.0
 *  Description: 串口头文件
 *  Copyright (C) E.D.D -- HPU
 *****************************************************************************/
 
#ifndef __UART_H_
#define __UART_H_

#include <STC12C5A60S2.H>
#include "CTypes.h"

void UartInit(void);
void MessageInit(void);
void DealReceiveData(void);
void UartSendByte(uint8 byte);
void UartSendString(uint8 *string);

#endif