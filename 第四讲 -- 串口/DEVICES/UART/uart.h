
#ifndef __UART_H_
#define __UART_H_

#include <STC12C5A60S2.H>
#include "CTypes.h"

void UartInit(void);
void MessageInit(void);
void DealReceiveData(void);
void UartSendByte(uint8 byte);
void UartSendString(uint8 *string);

#endif