
/*****************************************************************************
 **************       ��ѧ������������ -- E.D.D     ***************************
 *****************************************************************************
 *  �����ڵ���������12��ѧϰ�壬STC12@32M����
 *  File name: lcd1602.c
 *  Author: E.D.D
 *  Date: 2016-1-20 
 *  Version: V2.0
 *  Description: lcd1602��غ���˵��
 *  Copyright (C) E.D.D -- HPU
 *****************************************************************************/
 
#include "lcd1602.h"

/**
  *  �������ƣ�LCD_Init
  *  ������������
  *  �������ܣ�lcd1602 ��ʼ��
  *  ���ڣ�2016-1-20
  */
void LCD_Init(void)
{
    LCD_WriteCmd(0x38);  //16*2��ʾ��5*7����8λ���ݽӿ�
	 delay_ms(5);
	 LCD_WriteCmd(0x38);  //16*2��ʾ��5*7����8λ���ݽӿ�
	 delay_ms(5);
	 LCD_WriteCmd(0x38);  //16*2��ʾ��5*7����8λ���ݽӿ�
	 delay_ms(5);
    LCD_WriteCmd(0x0C);  //��ʾ���������ر�
    LCD_WriteCmd(0x06);  //���ֲ�������ַ�Զ�+1
    LCD_WriteCmd(0x01);  //����
}

/**
  *  �������ƣ�LCD_WaitReady
  *  ������������
  *  �������ܣ�lcd1602 ���æ����
  *  ���ڣ�2016-1-20
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
	}while(sta & 0x80);     /* ���bit7λ��ֵ */
}

/**
  *  �������ƣ�LCD_WriteCmd
  *  ����������һ���ֽڵ�ָ��
  *  �������ܣ�lcd1602 дָ��
  *  ���ڣ�2016-1-20
  */
void LCD_WriteCmd(uint8 cmd)
{
//	LCD_WaitReady();         //������һ����ʱ����
	LCD_RS = 0;
	LCD_WR = 0;
	DATA = cmd;
	delay_us(1);             /* ����stc12ָ���ٶ�̫�� ����ʱ */
	LCD_EN = 1;
	LCD_EN = 0;
	delay_ms(5);
}

/**
  *  �������ƣ�LCD_WriteData
  *  ����������һ���ֽڵ�����
  *  �������ܣ�lcd1602 д����
  *  ���ڣ�2016-1-20
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
  *  �������ƣ�LCD_ShowString
  *  ��������������ֵ ���ַ���
  *  �������ܣ�lcd1602 ��������
  *  ���ڣ�2016-1-20
  */
void LCD_ShowString(uint8 x, uint8 y, uint8 *str)
{
   LCD_WriteCmd((((y & 1) << 6) + x) | 0x80);   /* ���ù���λ�� */
	while(*str)
	{
	    LCD_WriteData(*str++);
	}
}


