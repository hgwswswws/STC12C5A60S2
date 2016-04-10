
/*****************************************************************************
 **************       ��ѧ������������ -- E.D.D     ***************************
 *****************************************************************************
 *  �����ڵ���������12��ѧϰ�壬STC12@32M����
 *  File name: usart.c
 *  Author: E.D.D
 *  Date: 2016-1-20 
 *  Version: V2.0
 *  Description: ������غ���˵��
 *  Copyright (C) E.D.D -- HPU
 *****************************************************************************/
 
#include "uart.h"

xdata uint8 ReceiveBuff[100] = {0};
uint8 FlagFinished = 0;
uint8 NUM_LEDStart, NUM_LEDStop, NUM_LEDPositive,
             NUM_LEDNegative, NUM_LEDError;

/**
  *  �������ƣ�UartInit
  *  ������������
  *  �������ܣ�Uart ��ʼ�������ж�
  *  ���ڣ�2016-1-20
  */
void UartInit(void)		//9600bps@32MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//���������ʷ�����ʱ��ΪFosc,��1T
	BRT = 0x98;		   //�趨���������ʷ�������װֵ
	AUXR |= 0x01;		//����1ѡ����������ʷ�����Ϊ�����ʷ�����
	AUXR |= 0x10;		//�������������ʷ�����
	
	ES = 1;
}

/**
  *  �������ƣ�MessageInit
  *  ������������
  *  �������ܣ���Ϣ���� ��ʼ��
  *  ���ڣ�2016-1-20
  */
void MessageInit(void)
{
   UartSendString("This is a LCD1602 test!!! \r\n");
}

/**
  *  �������ƣ�UartSendByte
  *  ����������һ���ֽڵ�����
  *  �������ܣ����ڷ���һ���ֽ�
  *  ���ڣ�2016-1-20
  */
void UartSendByte(uint8 byte)
{
    SBUF = byte;
    while(!TI);
	 TI = 0;
}

/**
  *  �������ƣ�UartSendString
  *  ����������һ���ַ���
  *  �������ܣ����ڷ���һ���ַ���
  *  ���ڣ�2016-1-20
  */
void UartSendString(uint8 *string)
{
    while(*string)
	 {
	     UartSendByte(*string++);
	 }
}

/**
  *  �������ƣ�DealReceiveData
  *  ������������
  *  �������ܣ����ڽ������ݴ���
  *  ���ڣ�2016-1-20
  */
void DealReceiveData(void)
{
   if(FlagFinished)
	{
	   FlagFinished = 0;
      /** ���ڴ������� ��������Ҫ���� **/
	}
}

void uart1_interrupt()  interrupt 4
{
	static uint8 i;
   if(!RI)  return;
   RI = 0;
	if('\n' != SBUF)            //�ж��Ƿ������ɵı�־
	{	
	   ReceiveBuff[i++] = SBUF;    //�����յ������ݴ��뻺����
	}
	else
	{	
		P13 = ~P13;
	   ReceiveBuff[i-1] = '\0';    /* �ѽ��ܵ���\r��ȥ������Ϊ�س�����\r\n��ɵ� */
		i = 0;   FlagFinished = 1;
	}
	//DealReceiveData();     /* �ú�������FlagFinished��־λ���ж� */
}

