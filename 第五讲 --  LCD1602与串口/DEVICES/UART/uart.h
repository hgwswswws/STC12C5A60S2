
/*****************************************************************************
 **************       ��ѧ������������ -- E.D.D     ***************************
 *****************************************************************************
 *  �����ڵ���������12��ѧϰ�壬STC12@32M����
 *  File name: usart.h
 *  Author: E.D.D
 *  Date: 2016-1-20 
 *  Version: V2.0
 *  Description: ����ͷ�ļ�
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