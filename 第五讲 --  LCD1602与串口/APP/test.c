
/*****************************************************************************
 **************       大学生电器开发部 -- E.D.D     ***************************
 *****************************************************************************
 *  适用于电器开发部12级学习板，STC12@32M晶振
 *  File name: test.c
 *  Author: E.D.D
 *  Date: 2016-1-20 
 *  Version: V2.0
 *  Description: 主函数
 *  Copyright (C) E.D.D -- HPU
 *****************************************************************************/
 
#include <STC12C5A60S2.H>
#include "uart.h"
#include "delay.h"
#include "lcd1602.h"

extern uint8 FlagFinished;
extern xdata uint8 ReceiveBuff[100];

void main()            /* 功能：使用串口发送数据，并在1602上面显示 波特率：9600 */
{
	EA = 1;
   LCD_Init();
   UartInit();
	MessageInit();
	LCD_ShowString(0, 0,"welcome to CHINA");        /* 第一行显示 */
	while(1)
	{
	   if(FlagFinished)                             /* 接收完成 */
		{
		   FlagFinished = 0;
			LCD_ShowString(0,1,"                ");   /* 将第二行清空  16个空格 */
			LCD_ShowString(0,1,ReceiveBuff);          /* 显示串口发送的数据 */ 
		}
	}
}

                       /* 警告： 两个函数没有调用 */
