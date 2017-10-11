/*
 * GlobalFunctions.c
 *
 *  Created on: Jun 22, 2014
 *      Author: Luis
 */

#include "GlobalFunctions.h"


uint8 signal_On_Off = BIT_OFF;
uint8 motor_On_Off = BIT_OFF;
uint8 MK_ini = TRUE;

void delay(uint16 delay){
	volatile int counter, counter2; /** contadores para lograr el delay */
	
	for(counter2=16; counter2 > 0; counter2--){ /** se recorre el contador desde el valor maximo hasta 0 */
		for(counter=delay; counter > 0; counter--); 

	}
}

void yellow(){ //Assingning valies to get color YELLOW
	GPIOB->PDOR = ~(RED);  /** se le asigna el color rojo al LED */
	GPIOE->PDOR = ~(GREEN);/** se le asigna el color verde al LED */
}

void red(){ //Assingning valies to get color RED
	GPIOB->PDOR = ~(RED);/** se le asigna el color rojo al LED */
	GPIOE->PDOR = ~(0x0);/** no se le asigna color al LED */
}

void purple(){ //Assingning valies to get color PURPLE
	GPIOB->PDOR = ~(RED + BLUE); /** se le asigna el color rojo y azul al LED */
	GPIOE->PDOR = ~(0x0);/** no se le asigna color al LED */
}

void blue(){ //Assingning valies to get color BLUE
	GPIOB->PDOR = ~(BLUE);/** se le asigna el color azul al LED */
	GPIOE->PDOR = ~(0x0);/** no se le asigna color al LED */
}

void green(){ //Assingning valies to get color GREEN
	GPIOB->PDOR = ~(0x0);/** no se le asigna color al LED */
	GPIOE->PDOR = ~(GREEN);/** se le asigna el color verde al LED */
}

void white(){
	GPIOB->PDOR = ~(RED + BLUE);/** se le asigna el color rojo y azul al LED */
	GPIOE->PDOR = ~(GREEN);/** se le asigna el color verde al LED */
}

void noColor(){
	GPIOB->PDOR = ~(0x0);/** no se le asigna color al LED */
	GPIOE->PDOR = ~(0x0);
}
