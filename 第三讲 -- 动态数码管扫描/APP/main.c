
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
#include "timer.h"
#include "num_led.h"
#include "delay.h"

extern uint8 flag;

void main()
{
   uint8 i = 255, n = 0;
   NUM_LED_Init();
	Timer0Init();
	while(1)
	{
		if(flag)
		{
			flag = 0;
		   NUM_Shownum(i--);
			NUM_ShowLED(1<<(n++));
         n &= 0x07;			
		}
	}
}
