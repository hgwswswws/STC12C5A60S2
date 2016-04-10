
/*****************************************************************************
 **************       大学生电器开发部 -- E.D.D     ***************************
 *****************************************************************************
 *  适用于电器开发部12级学习板，STC12@32M晶振
 *  File name: usart.c
 *  Author: E.D.D
 *  Date: 2016-1-20 
 *  Version: V2.0
 *  Description: 串口相关函数说明
 *  Copyright (C) E.D.D -- HPU
 *****************************************************************************/
 
#include "uart.h"

xdata uint8 ReceiveBuff[100] = {0};
uint8 FlagFinished = 0;
uint8 NUM_LEDStart, NUM_LEDStop, NUM_LEDPositive,
             NUM_LEDNegative, NUM_LEDError;

/**
  *  函数名称：UartInit
  *  函数参数：无
  *  函数功能：Uart 初始化并开中断
  *  日期：2016-1-20
  */
void UartInit(void)		//9600bps@32MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
	BRT = 0x98;		   //设定独立波特率发生器重装值
	AUXR |= 0x01;		//串口1选择独立波特率发生器为波特率发生器
	AUXR |= 0x10;		//启动独立波特率发生器
	
	ES = 1;
}

/**
  *  函数名称：MessageInit
  *  函数参数：无
  *  函数功能：消息处理 初始化
  *  日期：2016-1-20
  */
void MessageInit(void)
{
   UartSendString("This is a LCD1602 test!!! \r\n");
}

/**
  *  函数名称：UartSendByte
  *  函数参数：一个字节的数据
  *  函数功能：串口发送一个字节
  *  日期：2016-1-20
  */
void UartSendByte(uint8 byte)
{
    SBUF = byte;
    while(!TI);
	 TI = 0;
}

/**
  *  函数名称：UartSendString
  *  函数参数：一个字符串
  *  函数功能：串口发送一个字符串
  *  日期：2016-1-20
  */
void UartSendString(uint8 *string)
{
    while(*string)
	 {
	     UartSendByte(*string++);
	 }
}

/**
  *  函数名称：DealReceiveData
  *  函数参数：无
  *  函数功能：串口接受数据处理
  *  日期：2016-1-20
  */
void DealReceiveData(void)
{
   if(FlagFinished)
	{
	   FlagFinished = 0;
      /** 用于处理数据 本程序不需要调用 **/
	}
}

void uart1_interrupt()  interrupt 4
{
	static uint8 i;
   if(!RI)  return;
   RI = 0;
	if('\n' != SBUF)            //判断是否接受完成的标志
	{	
	   ReceiveBuff[i++] = SBUF;    //将接收到的数据存入缓存中
	}
	else
	{	
		P13 = ~P13;
	   ReceiveBuff[i-1] = '\0';    /* 把接受到的\r给去掉，因为回车是由\r\n组成的 */
		i = 0;   FlagFinished = 1;
	}
	//DealReceiveData();     /* 该函数中有FlagFinished标志位的判断 */
}

