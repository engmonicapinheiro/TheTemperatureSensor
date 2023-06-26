/*
 * uart.h
 *
 *  Created on: 17 Jun 2023
 *      Author: monicapinheiro
 */

#ifndef UART_H_
#define UART_H_

#include"stm32l031xx.h"


#define UART_BAUDRATE  	9600

void Uart2SecondPinTxRxInit(void);
void Uart2TxRxInit(void);


void Uart2Write(int ch);
char Uart2Read(void);

#endif /* UART_H_ */
