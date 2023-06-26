#include"stm32l031xx.h"
#include <stdio.h>
#include "gpio.h"
#include "uart.h"

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
