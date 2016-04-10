
/*****************************************************************************
 **************       大学生电器开发部 -- E.D.D     ***************************
 *****************************************************************************
 *  适用于电器开发部12级学习板，STC12@32M晶振
 *  File name: lcd1602.h
 *  Author: E.D.D
 *  Date: 2016-1-20 
 *  Version: V2.0
 *  Description: lcd1602头文件
 *  Copyright (C) E.D.D -- HPU
 *****************************************************************************/
 
#ifndef __LCD1602_H_
#define __LCD1602_H_

#include <STC12C5A60S2.H>
#include "CTypes.h"
#include "delay.h"

#define  LCD_RS  P20 
#define  LCD_WR  P21
#define  LCD_EN  P12 
#define  DATA   P0

void LCD_Init(void);
void LCD_WaitReady(void);
void LCD_WriteData(uint8 dat);
void LCD_WriteCmd(uint8 cmd);
void LCD_ShowString(uint8 x, uint8 y, uint8 *str);

#endif