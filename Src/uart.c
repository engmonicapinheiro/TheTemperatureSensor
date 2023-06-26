/*
 * uart.c
 *
 *  Created on: 17 Jun 2023
 *      Author: monicapinheiro
 */

#include "uart.h"
#include <stdint.h>

uint32_t STM32L0SystemCoreClock = 2097000;

/* UART2_TX = PA9 - D1
 * UART2_RX = PA10 - D0*/
void Uart2SecondPinTxRxInit(void)
{
    /* set PA9 mode to alternate function */
	GPIOA->MODER &= ~(1U << 18);  //bit 18 set to 0
	GPIOA->MODER |= (1U << 19);   //bit 19 set to 1

    /* set PA10 mode to alternate function */
	GPIOA->MODER &= ~(1U << 20);  //bit 20 set to 0
	GPIOA->MODER |= (1U << 21);   //bit 21 set to 1

    /* set alternate function type to UART (AF4) at PA9 (USART2_TX) */
	GPIOA->AFR[1] &= ~(1U << 4);
	GPIOA->AFR[1] &= ~(1U << 5);
	GPIOA->AFR[1] |=  (1U << 6);
	GPIOA->AFR[1] &= ~(1U << 7);

	/* set alternate function type to UART (AF4) at PA10 (USART2_RX) */
	GPIOA->AFR[1] &= ~(1U << 8);
	GPIOA->AFR[1] &= ~(1U << 9);
	GPIOA->AFR[1] |=  (1U << 10);
	GPIOA->AFR[1] &= ~(1U << 11);

    /*** configure the UART module ***/
    /* enable clock access to the UART module - bit 17*/
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	/* configure the baudrate */
//	USART2->BRR = (STM32L0SystemCoreClock / 2400);   //works for baud = 2400
	USART2->BRR = (STM32L0SystemCoreClock / 9600);

    /* configure the transfer direction - bit 3 */
	//USART2->CR1 = (USART_CR1_TE | USART_CR1_RE);
	// Enable transmitter, receiver and receive-interrupt of USART1
	USART2->CR1 = USART_CR1_UE + USART_CR1_TE + USART_CR1_RE + USART_CR1_RXNEIE;
}


void Uart2TxRxInit(void)
{
    /* enable clock access to GPIOA done in InitGpioClock() */
    /* set PA2 mode to alternate function */
	GPIOA->MODER &= ~(1U << 4);  //bit 4 set to 0
	GPIOA->MODER |= (1U << 5);   //bit 5 set to 1

    /* set PA3 mode to alternate function */
	GPIOA->MODER &= ~(1U << 6);  //bit 6 set to 0
	GPIOA->MODER |= (1U << 7);   //bit 7 set to 1


    /* set alternate function type to UART (AF4) at PA2 (USART2_TX) */
	GPIOA->AFR[0] &= ~(1U << 8);
	GPIOA->AFR[0] &= ~(1U << 9);
	GPIOA->AFR[0] |=  (1U << 10);
	GPIOA->AFR[0] &= ~(1U << 11);

	/* set alternate function type to UART (AF4) at PA3 (USART2_RX) */
	GPIOA->AFR[0] &= ~(1U << 12);
	GPIOA->AFR[0] &= ~(1U << 13);
	GPIOA->AFR[0] |=  (1U << 14);
	GPIOA->AFR[0] &= ~(1U << 15);

    /*** configure the UART module ***/
    /* enable clock access to the UART module - bit 17*/
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	/* configure the baudrate */
//	USART2->BRR = (STM32L0SystemCoreClock / 2400);   //works for baud = 2400
	USART2->BRR = (STM32L0SystemCoreClock / 9600);

    /* configure the transfer direction - bit 3 */
	//USART2->CR1 = (USART_CR1_TE | USART_CR1_RE);
	// Enable transmitter, receiver and receive-interrupt of USART1
	USART2->CR1 = USART_CR1_UE + USART_CR1_TE + USART_CR1_RE + USART_CR1_RXNEIE;

    /* enable the UART module */
	//USART2->CR1 |= USART_CR1_UE;

}



char Uart2Read(void)
{
//	if(USART2->ISR & USART_ISR_RXNE)
//	{
//		char temp = USART2->RDR; //fetch the data received
//		USART2->TDR = temp; //send it back out
//		while(!(USART2->ISR &USART_ISR_TC));
//	}



		/* wait for char to arrive*/
			while(!(USART2->ISR & USART_CR1_RXNEIE));
		//	while(!(USART2->ISR & USART_ISR_RXNE)); //fault
			return (USART2->RDR);


		// read the received character
		//    char received=USART2->RDR;
		////    // send echo back
		//    while(!(USART2->ISR & USART_ISR_TXE));
		//    USART2->TDR = received;
		//    return (USART2->TDR);
}

//// Called after each received character
//void USART2_IRQHandler()
//{
//    // read the received character
//    char received=USART2->RDR;
//
//    // send echo back
//    while(!(USART2->ISR & USART_ISR_TXE));
//    USART2->TDR = received;
//}

void Uart2Write(int ch)
{
	/* make sure the transmit data register is empty */
	while(!(USART2->ISR & USART_ISR_TXE));
	/* write 8 bits to the transmit data register */
	USART2->TDR = ch & 0xFF;    //to transmit 8 bits
}

int __io_putchar(int ch)
{
	Uart2Write(ch);
	return ch;

}
