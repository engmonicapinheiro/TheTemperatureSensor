/*
 * shiftRegister595.h
 *
 *  Created on: 2 Jul 2023
 *      Author: monicapinheiro
 */

#ifndef SHIFTREGISTER595_H_
#define SHIFTREGISTER595_H_

#include"stm32l031xx.h"
#include<stdint.h>
#include "gpio.h"

enum BitOrder
{
	LSBFIRST = 0,
	MSBFIRST = 1
};

void UpdateLEDsLong(int value);
void delayms(uint32_t msec);

#endif /* SHIFTREGISTER595_H_ */
