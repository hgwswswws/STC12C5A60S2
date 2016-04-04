
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
#include "timer.h"
#include "delay.h"
#include "num_led.h"


extern uint8 NUM_LEDStart, NUM_LEDStop, NUM_LEDPositive,
             NUM_LEDNegative, NUM_LEDError;
extern uint8 flag;

uint32 countnum = 0;

void main(void)                                   /* ָ�����  ���ȷ���ָ�� START   ���������                            */
{                                                 /*           �ٷ���ָ��   POSITIVE  ���ϼ���  ����   NEGATIVE  ���¼��� */
	uint8 temp1, temp2;
	EA = 1;    /* �����ж� */                      /* �����Ҫֹͣ ����ָ��   STOP  ֹͣ���� , ��Ҫ�ָ������ٷ��� START */
   UartInit();                                    /* ���ͽ��վ�Ϊ�ı�ģʽ�� ������9600�� ����ָ��ʱһ��Ҫ�ӻس�����Ȼʶ�𲻳�ָ�� */
	Timer0Init();
	NUM_LED_Init();
	MessageInit();        
	while(1)
	{                                                 /*  �ص�ѧϰ��־λ������ ,����һ���ص㣬 �ص㣬 �ص� */
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
		if (NUM_LEDNegative && flag)        /* �����־λΪʲôû�����??? */
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