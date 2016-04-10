
/*****************************************************************************
 **************       大学生电器开发部 -- E.D.D     ***************************
 *****************************************************************************
 *  适用于电器开发部12级学习板，STC12@32M晶振
 *  File name: lcd1602.c
 *  Author: E.D.D
 *  Date: 2016-1-20 
 *  Version: V2.0
 *  Description: lcd1602相关函数说明
 *  Copyright (C) E.D.D -- HPU
 *****************************************************************************/
 
#include "lcd1602.h"

/**
  *  函数名称：LCD_Init
  *  函数参数：无
  *  函数功能：lcd1602 初始化
  *  日期：2016-1-20
  */
void LCD_Init(void)
{
    LCD_WriteCmd(0x38);  //16*2显示，5*7点阵，8位数据接口
	 delay_ms(5);
	 LCD_WriteCmd(0x38);  //16*2显示，5*7点阵，8位数据接口
	 delay_ms(5);
	 LCD_WriteCmd(0x38);  //16*2显示，5*7点阵，8位数据接口
	 delay_ms(5);
    LCD_WriteCmd(0x0C);  //显示器开，光标关闭
    LCD_WriteCmd(0x06);  //文字不动，地址自动+1
    LCD_WriteCmd(0x01);  //清屏
}

/**
  *  函数名称：LCD_WaitReady
  *  函数参数：无
  *  函数功能：lcd1602 检测忙函数
  *  日期：2016-1-20
  */
void LCD_WaitReady(void)
{
   uint8 sta;
	DATA = 0xff;
	LCD_WR = 1;
	LCD_RS = 0;
	do
	{
	   LCD_EN = 1;
	   sta = DATA;
		LCD_EN = 0;
	}while(sta & 0x80);     /* 检测bit7位的值 */
}

/**
  *  函数名称：LCD_WriteCmd
  *  函数参数：一个字节的指令
  *  函数功能：lcd1602 写指令
  *  日期：2016-1-20
  */
void LCD_WriteCmd(uint8 cmd)
{
//	LCD_WaitReady();         //可以用一个延时代替
	LCD_RS = 0;
	LCD_WR = 0;
	DATA = cmd;
	delay_us(1);             /* 由于stc12指令速度太快 加延时 */
	LCD_EN = 1;
	LCD_EN = 0;
	delay_ms(5);
}

/**
  *  函数名称：LCD_WriteData
  *  函数参数：一个字节的数据
  *  函数功能：lcd1602 写数据
  *  日期：2016-1-20
  */
void LCD_WriteData(uint8 dat)
{
//   LCD_WaitReady();
	LCD_RS = 1;
	LCD_WR = 0;
	DATA = dat;
	delay_us(1);
	LCD_EN = 1;
	LCD_EN = 0;
	delay_ms(5);
}

/**
  *  函数名称：LCD_ShowString
  *  函数参数：坐标值 、字符串
  *  函数功能：lcd1602 设置坐标
  *  日期：2016-1-20
  */
void LCD_ShowString(uint8 x, uint8 y, uint8 *str)
{
   LCD_WriteCmd((((y & 1) << 6) + x) | 0x80);   /* 设置光标的位置 */
	while(*str)
	{
	    LCD_WriteData(*str++);
	}
}


