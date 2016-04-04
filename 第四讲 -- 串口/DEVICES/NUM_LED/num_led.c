
/*****************************************************************************
 **************       大学生电器开发部 -- E.D.D     ***************************
 *****************************************************************************
 *  适用于电器开发部12级学习板，STC12@32M晶振
 *  File name: num_led.c
 *  Author: E.D.D
 *  Date: 2016-1-20 
 *  Version: V2.0
 *  Description: 定时器相关函数说明
 *  Copyright (C) E.D.D -- HPU
 *****************************************************************************/
 
#include "num_led.h"

code uint8 NUM_TABLE[] = {0xC0, 0XF9, 0XA4, 0XB0, 0X99, 0x92, 0X82, 0XF8, 0X80, 0X90,0xff};
volatile uint8 NUM_Buff[7];   //最后一位是LED灯

/**
  *  函数名称：NUM_LED_Init
  *  函数参数：无
  *  函数功能：num_led 初始化
  *  日期：2016-1-20
  */
void NUM_LED_Init(void)
{
	uint8 i;
   P11 = 0;
	P0M1 = 0x00; P0M0 = 0xff;   /* 强推挽输出  */
	P0 = 0xff;                  /*消除失效数据 */
	for(i = 0;i < 7;i++)
	{
	   NUM_Buff[i] = 0xff;
	}
}

/**
  *  函数名称：NUM_Show
  *  函数参数：数码管位数，显示数据 num从零开始
  *  函数功能：数字单个显示
  *  日期：2016-1-20
  */
void NUM_ShowScan(void)
{
	static uint8 num;
	
	P11 = 1;                     /* 消除鬼影 */
	P2 &= ~(7<<0); P2 |= (num%7<<0);
	P0 = NUM_Buff[(num++)%7];    /* 循环扫描数据 */
	P11 = 0;                     /* 送出数据显示 */
}

/**
  *  函数名称：NUM_Shownum
  *  函数参数：数码管显示数字
  *  函数功能：显示数字
  *  日期：2016-1-20
  */
void NUM_Shownum(uint32 longnum)
{ 
	uint8 n;
	n = 6;                       /* 数码管最大的位数  6次循环 */
   while(n)
	{
	   NUM_Buff[n-1] = NUM_TABLE[longnum%10];
		longnum /= 10; 
		n--;  
	}
}

/**
  *  函数名称：NUM_ShowLED
  *  函数参数：LED显示
  *  函数功能：LED显示数字
  *  日期：2016-1-20
  */
void NUM_ShowLED(uint8 dt)
{
    NUM_Buff[6] = ~dt;
}


