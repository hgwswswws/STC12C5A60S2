
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
#include "timer.h"
#include "delay.h"
#include "num_led.h"


extern uint8 NUM_LEDStart, NUM_LEDStop, NUM_LEDPositive,
             NUM_LEDNegative, NUM_LEDError;
extern uint8 flag;

uint32 countnum = 0;

void main(void)                                   /* 指令操作  首先发送指令 START   开启数码管                            */
{                                                 /*           再发送指令   POSITIVE  向上计数  或者   NEGATIVE  向下计数 */
	uint8 temp1, temp2;
	EA = 1;    /* 开总中断 */                      /* 如果想要停止 发送指令   STOP  停止计数 , 想要恢复计数再发送 START */
   UartInit();                                    /* 发送接收均为文本模式， 波特率9600， 发送指令时一定要加回车，不然识别不出指令 */
	Timer0Init();
	NUM_LED_Init();
	MessageInit();        
	while(1)
	{                                                 /*  重点学习标志位的运用 ,这是一个重点， 重点， 重点 */
	   if (NUM_LEDStart)
		{
			TR0 = 1;
		   NUM_LEDStart = 0;
			NUM_LEDPositive = temp1;
			NUM_LEDNegative = temp2;
		}
		if (NUM_LEDStop)
		{
		   NUM_LEDStop = 0;
			temp1 = NUM_LEDPositive;
			temp2 = NUM_LEDNegative;
			NUM_LEDPositive = 0;
			NUM_LEDNegative = 0;
		}
		if (NUM_LEDPositive && flag)
		{
			flag = 0;
		   countnum++;
		}
		if (NUM_LEDNegative && flag)        /* 这个标志位为什么没有清除??? */
		{
			flag = 0;
		   countnum--;
		}
		if (NUM_LEDError)
		{
			 NUM_LEDError = 0;
		    UartSendString("The Command Is Error!!!");
		}
		NUM_Shownum(countnum);
	}
}