/*
 * gpio.h
 *
 *  Created on: Jun 5, 2023
 *      Author: monicapinheiro
 */

#ifndef GPIO_H_
#define GPIO_H_

#include"stm32l031xx.h"

#define BUTTON (1U << 4)


void InitGpioClock(void);
void InitGPIO(void);
void PushButton(void);

void InitShiftRegisterPins(void);


#endif /* GPIO_H_ */
