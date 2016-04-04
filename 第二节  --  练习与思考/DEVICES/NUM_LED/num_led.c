
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

uint8 code NUM_TABLE[10] = {0xC0, 0XF9, 0XA4, 0XB0, 0X99, 0x92, 0X82, 0XF8, 0X80, 0X90};

/**
  *  函数名称：NUM_LED_Init
  *  函数参数：无
  *  函数功能：num_led 初始化
  *  日期：2016-1-20
  */
void NUM_LED_Init(void)
{
   P11 = 0;
//	P0M1 = 0x00; P0M0 = 0xff;   /* 强推挽输出  */
	P0 = 0xff;                  /* 消除失效数据 */
}

/**
  *  函数名称：NUM_ShowScan
  *  函数参数：无
  *  函数功能：数字单个显示
  *  日期：2016-1-20
  */
void NUM_ShowScan(void)
{
	static uint8 num = 0;

	P11 = 1;                     /* 消除鬼影 */
	P2 &= (uint8)~(7<<0);    /* 将后三位清零 */
	P2 |= (uint8)(5<<0);     /* 将低三位置于 1 1 0 */
	P0 = NUM_TABLE[num++];    /* 循环扫描数据 */
	num %= 10;
	P11 = 0;                     /* 送出数据显示 */
}




