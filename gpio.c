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

//define all the pins of the 74HC595 as output
void InitShiftRegisterPins(void)
{
	//latch pin = pin D5, PB6- MODER6
	GPIOB->MODER |= (1U << 12);
	GPIOB->MODER &= ~(1U << 13);

	//data pin = pin D4, PB7 - MODER7
	GPIOB->MODER |= (1U << 14);
	GPIOB->MODER &= ~(1U << 15);

	//clock pin = pin D6, PB1 - MODER1
	GPIOB->MODER |= (1U << 2);
	GPIOB->MODER &= ~(1U << 3);
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


