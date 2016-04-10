
/*****************************************************************************
 **************       ��ѧ������������ -- E.D.D     ***************************
 *****************************************************************************
 *  �����ڵ���������12��ѧϰ�壬STC12@32M����
 *  File name: test.c
 *  Author: E.D.D
 *  Date: 2016-1-20 
 *  Version: V2.0
 *  Description: ������
 *  Copyright (C) E.D.D -- HPU
 *****************************************************************************/
 
#include <STC12C5A60S2.H>
#include "uart.h"
#include "delay.h"
#include "lcd1602.h"

extern uint8 FlagFinished;
extern xdata uint8 ReceiveBuff[100];

void main()            /* ���ܣ�ʹ�ô��ڷ������ݣ�����1602������ʾ �����ʣ�9600 */
{
	EA = 1;
   LCD_Init();
   UartInit();
	MessageInit();
	LCD_ShowString(0, 0,"welcome to CHINA");        /* ��һ����ʾ */
	while(1)
	{
	   if(FlagFinished)                             /* ������� */
		{
		   FlagFinished = 0;
			LCD_ShowString(0,1,"                ");   /* ���ڶ������  16���ո� */
			LCD_ShowString(0,1,ReceiveBuff);          /* ��ʾ���ڷ��͵����� */ 
		}
	}
}

                       /* ���棺 ��������û�е��� */
