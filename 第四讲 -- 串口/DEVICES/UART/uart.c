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
   UartSendString("   NUM_LED Command \r\n");
	UartSendString("1��START -- start count number\r\n");
	UartSendString("2��STOP -- stop count number\r\n");
	UartSendString("3��POSITIVE -- count up\r\n");
	UartSendString("4��NEGATIVE -- count down\r\n");
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
      if(ReceiveBuff[0] == 'S' && ReceiveBuff[1] == 'T' && ReceiveBuff[2] == 'A' && ReceiveBuff[3] == 'R' && ReceiveBuff[4] == 'T' )
		{
		   NUM_LEDStart = 1;  
		}			
		else if(ReceiveBuff[0] == 'S' && ReceiveBuff[1] == 'T' && ReceiveBuff[2] == 'O' && ReceiveBuff[3] == 'P')
		{
		   NUM_LEDStop = 1;
		}
		else if(ReceiveBuff[0] == 'P' && ReceiveBuff[1] == 'O' && ReceiveBuff[2] == 'S')
		{
		   NUM_LEDPositive = 1; 
         NUM_LEDNegative = 0;			//����
		}
		else if(ReceiveBuff[0] == 'N' && ReceiveBuff[1] == 'E' && ReceiveBuff[2] == 'G')
		{
		   NUM_LEDNegative = 1;
			NUM_LEDPositive = 0;
		}
		else
		{
			NUM_LEDError = 1;
		}
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
	   ReceiveBuff[i] = '\0';
		i = 0;   FlagFinished = 1;
	}
	DealReceiveData();
}

