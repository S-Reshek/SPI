/*
 * GlobalFunctions.h
 *
 *  Created on: Jun 22, 2014
 *      Author: Luis
 */

#ifndef GLOBALFUNCTIONS_H_
#define GLOBALFUNCTIONS_H_

#include "GPIO.h"
#include "DataTypeDefinitions.h"
#include "MK64F12.h"

#define RED  0x400000
#define GREEN 0x4000000
#define BLUE  0x200000

void yellow();
void red();
void purple();
void blue();
void green();
void white();
void noColor();

void delay(uint16);
uint8 toogleValue(uint8 flag);

uint8 start_function();
uint8 selection_function();
uint8 motor_ON_OFF();
uint8 signal_ON_OFF();

#endif /* GLOBALFUNCTIONS_H_ */
