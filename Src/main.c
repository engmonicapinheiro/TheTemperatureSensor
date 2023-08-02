#include"stm32l031xx.h"
#include <stdio.h>
#include "../Inc/gpio.h"
#include "uart.h"
#include "../Inc/shiftRegister595.h"

//char key;

// delay loop for the default 2.1 MHz CPU clock with optimizer enabled
void delay(uint32_t msec)
{
    for (uint32_t j=0; j < msec * 419; j++)
    {
        __NOP();
    }
}


int main()
{

	InitGpioClock();
	InitGPIO();
	InitShiftRegisterPins();

	while(1)
	{

		for(uint32_t numbersToDisplay = 0; numbersToDisplay < 256; numbersToDisplay++)
		{
			UpdateLEDsLong(numbersToDisplay);
			delay(1000);
		}




		/* to toggle the green LED */
//		GPIOA->BSRR |= 0x100;
//		delay(200);
//		GPIOA->BSRR |= 0x1000000;
//		delay(200);

	}
}


#if 0

int main()
{

	InitGpioClock();
	InitGPIO();
//	Uart2TxRxInit();
	Uart2SecondPinTxRxInit();

	// Enable interrupt in NVIC
	//NVIC_EnableIRQ(USART2_IRQn);

	//int x;




	while(1)
	{
	//	printf("Hello from STM32L0...\n\r");
	//	Uart2Write('M');

//		key = 1;
		char key = Uart2Read();

		if(key == 'a')
		{
			GPIOA->BSRR |= (1U << 24);
			delay(500);

		}
		else
		{

			GPIOA->BSRR |= (1U << 8);
			delay(500);
		}

	}

	//return 0;
}

#endif
