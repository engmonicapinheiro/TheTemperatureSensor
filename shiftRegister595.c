/*
 * shiftRegister595.c
 *
 *  Created on: 2 Jul 2023
 *      Author: monicapinheiro
 */
#include "shiftRegister595.h"


void UpdateLEDsLong(int value)
{
	//pulls the chip latch low
	GPIOB->ODR &= ~(1U << 6);  //latch pin PB6

	int mask = 0b10000000;

	for(int i = 0; i < 8; i++)
	{
		//send one bit of data
		char state = ((value & mask) > 0);

		if(state == 1)
		{
			GPIOB->ODR |= (1U << 7);  //pin data
		}
		else if(state == 0)
		{
			GPIOB->ODR &= ~(1U << 7);
		}

		//pulse the clock pin so the shift register receives the bit of data
		GPIOB->ODR |= (1U << 1);  //clock pin PB1
		delayms(10);
		GPIOB->ODR &= ~(1U << 1);  //clock pin PB1

		mask >>= 1;
	}
	//pulls the latch high shifting our data into being displayed
	GPIOB->ODR |= (1U << 6);  //latch pin PB6
}


// delay loop for the default 2.1 MHz CPU clock with optimizer enabled
void delayms(uint32_t msec)
{
    for (uint32_t j=0; j < msec * 419; j++)
    {
        __NOP();
    }
}
