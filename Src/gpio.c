/*
 * gpio.c
 *
 *  Created on: Jun 5, 2023
 *      Author: monicapinheiro
 */

#include "gpio.h"


void InitGpioClock(void)
{
	RCC->IOPENR |= RCC_IOPENR_IOPAEN;
	RCC->IOPENR |= RCC_IOPENR_IOPBEN;
}


void InitGPIO(void)
{
	/* PA8 configured as an output pin */
	GPIOA->MODER |= (1U << 16);
	GPIOA->MODER &= ~(1U << 17);

	/*PB4 configured as an input pin */
	GPIOB->MODER &= ~(1U << 8);
	GPIOB->MODER &= ~(1U << 9);
}


//pushbutton in PB4 (D12)
//The pushbutton is active low, meaning the led is always on
//so activation means when you read zero
void PushButton(void)
{
	//check (read) if the input data register is set high or low
	if(GPIOB->IDR & BUTTON)
	{
		GPIOA->BSRR |= (1U << 8);
	}
	else
	{
		GPIOA->BSRR |= (1U << 24);
	}
}


