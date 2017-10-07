/**
	\file
	\brief
		This is the source file for the GPIO device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.
		i.e., this is the application programming interface (API) for the GPIO peripheral.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Interrupts are not implemented in this API implementation.
 */
#include "MK64F12.h"
#include "GPIO.h"



static GPIO_interruptFlags_t GPIO_intrStatusFlag;

void PORTD_IRQHandler(){
	GPIO_intrStatusFlag.flagPortD = TRUE; /** Se le da la bandera de verdadeso a la interrupcion  */
	GPIO_clearInterrupt(GPIO_D); /** se limpia la interrupcion */
}

void PORTC_IRQHandler(){
	GPIO_intrStatusFlag.flagPortC = TRUE;/** Se le da la bandera de verdadeso a la interrupcion  */
	GPIO_clearInterrupt(GPIO_C);/** se limpia la interrupcion */
}


void PORTA_IRQHandler(){
	GPIO_intrStatusFlag.flagPortA  = TRUE;/** Se le da la bandera de verdadeso a la interrupcion  */
	GPIO_clearInterrupt(GPIO_A);/** se limpia la interrupcion */
}


void PORTB_IRQHandler(){
	GPIO_intrStatusFlag.flagPortB  = TRUE;/** Se le da la bandera de verdadeso a la interrupcion  */
	GPIO_clearInterrupt(GPIO_B);/** se limpia la interrupcion */
}
uint8 GPIO_getIRQStatus(GPIO_portNameType gpio){
	/** enviamos el valor de la bandera segun se pide*/
	switch (gpio) {
		case GPIO_A:
			return(GPIO_intrStatusFlag.flagPortA);
			break;
		case GPIO_B:
			return(GPIO_intrStatusFlag.flagPortB);
			break;
		case GPIO_C:
			return(GPIO_intrStatusFlag.flagPortC);
			break;
		case GPIO_D:
			return(GPIO_intrStatusFlag.flagPortD);
			break;
		case GPIO_E:
			return(GPIO_intrStatusFlag.flagPortE);
			break;
		default:
			return(ERROR);
			break;
	}

}

uint8 GPIO_clearIRQStatus(GPIO_portNameType gpio){
	/** Se limpia la bandera de la interrupcion segun se pida */
	switch (gpio) {
		case GPIO_A:
			GPIO_intrStatusFlag.flagPortA = FALSE;
			break;
		case GPIO_B:
			GPIO_intrStatusFlag.flagPortB = FALSE;
			break;
		case GPIO_C:
			GPIO_intrStatusFlag.flagPortC = FALSE;
			break;
		case GPIO_D:
			GPIO_intrStatusFlag.flagPortD = FALSE;
			break;
		case GPIO_E:
			GPIO_intrStatusFlag.flagPortE = FALSE;
			break;
		default:
			return(ERROR);
			break;
	}

	return(TRUE);

}


void GPIO_clearInterrupt(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
	{
		case GPIO_A: /** GPIO A is selected*/
			PORTA->ISFR=0xFFFFFFFF;
			break;
		case GPIO_B: /** GPIO B is selected*/
			PORTB->ISFR=0xFFFFFFFF;
			break;
		case GPIO_C: /** GPIO C is selected*/
			PORTC->ISFR = 0xFFFFFFFF;
			break;
		case GPIO_D: /** GPIO D is selected*/
			PORTD->ISFR=0xFFFFFFFF;
			break;
		default: /** GPIO E is selected*/
			PORTE->ISFR=0xFFFFFFFF;
			break;

	}// end switch
}
uint8 GPIO_clockGating(GPIO_portNameType portName){
	switch(portName){/** Selecting the GPIO for clock enabling*/
		case GPIO_A: /** GPIO A is selected*/
			SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
			break;
		case GPIO_B: /** GPIO B is selected*/
			SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
			break;
		case GPIO_C: /** GPIO C is selected*/
			SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
		break;
		case GPIO_D: /** GPIO D is selected*/
			SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
			break;
		case GPIO_E: /** GPIO E is selected*/
			SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
			break;
		default: /**If doesn't exist the option*/
			return(FALSE);
	}// end switch
/**Successful configuration*/
	return(TRUE);
}// end function

uint8 GPIO_pinControlRegister(GPIO_portNameType portName,uint8 pin,const GPIO_pinControlRegisterType*  pinControlRegister){

	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			PORTA->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_B:/** GPIO B is selected*/
			PORTB->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_C:/** GPIO C is selected*/
			PORTC->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_D:/** GPIO D is selected*/
			PORTD->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_E: /** GPIO E is selected*/
			PORTE->PCR[pin]= *pinControlRegister;
		default:/**If doesn't exist the option*/
			return(FALSE);
		break;
		}
	/**Successful configuration*/
	return(TRUE);
}

void GPIO_writePORT(GPIO_portNameType portName, uint32 Data){
	switch(portName){
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PDOR = Data;
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PDOR = Data;
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PDOR = Data;
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PDOR = Data;
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PDOR = Data;
		default:/**If doesn't exist the option*/
		break;
		}	/**Successful configuration*/
}

uint32 GPIO_readPORT(GPIO_portNameType portName){
	switch(portName){
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PDIR;
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PDIR;
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PDIR;
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PDIR;
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PDIR;
		default:/**If doesn't exist the option*/
			return(FALSE);
		break;
		}
	/**Successful configuration*/
	return(TRUE);
}

uint8 GPIO_readPIN(GPIO_portNameType portName, uint8 pin){
	uint32 inputValue;
	uint32 pin_Mask = 1;
	pin_Mask = 1<<pin;
	switch(portName){
		case GPIO_A:/** GPIO A is selected*/
			inputValue = GPIOA->PDIR & pin_Mask;
			break;
		case GPIO_B:/** GPIO B is selected*/
			inputValue = GPIOB->PDIR & pin_Mask;
			break;
		case GPIO_C:/** GPIO C is selected*/
			inputValue = GPIOC->PDIR & pin_Mask;
			break;
		case GPIO_D:/** GPIO D is selected*/
			inputValue = GPIOD->PDIR & pin_Mask;
			break;
		case GPIO_E: /** GPIO E is selected*/
			inputValue = GPIOE->PDIR & pin_Mask;
		default:/**If doesn't exist the option*/
			return(FALSE);
		break;
		}
	/**Successful configuration*/
	return(inputValue);
}

void GPIO_setPIN(GPIO_portNameType portName, uint8 pin){
	uint32 setPIN = 1;
	setPIN = 1<<pin;
	switch(portName){
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PSOR |= setPIN;
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PSOR |= setPIN;
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PSOR |= setPIN;
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PSOR |= setPIN;
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PSOR |= setPIN;
		default:/**If doesn't exist the option*/
		break;
		}
}

void GPIO_clearPIN(GPIO_portNameType portName, uint8 pin){
	uint32 clearPIN = 1;
	clearPIN = 1<<pin;
	switch(portName){
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PCOR |= clearPIN;
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PCOR |= clearPIN;
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PCOR |= clearPIN;
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PCOR |= clearPIN;
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PCOR |= clearPIN;
		default:/**If doesn't exist the option*/
		break;
		}
}

void GPIO_tooglePIN(GPIO_portNameType portName, uint8 pin){
	uint32 togglePIN = 1;
	togglePIN = 1<<pin;
	switch(portName){
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PTOR |= togglePIN;
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PTOR |= togglePIN;
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PTOR |= togglePIN;
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PTOR |= togglePIN;
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PTOR |= togglePIN;
		default:/**If doesn't exist the option*/
		break;
		}
}
void GPIO_dataDirectionPORT(GPIO_portNameType portName ,uint32 direction){
	switch(portName){
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PDDR = direction;
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PDDR = direction;
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PDDR = direction;
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PDDR = direction;
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PDDR = direction;
		default:/**If doesn't exist the option*/
		break;
		}	/**Successful configuration*/
}
void GPIO_dataDirectionPIN(GPIO_portNameType portName, uint8 State, uint8 pin){
	/** Se coloca un 1 o 0 para hacerlo entrada o salida, dependiendo de los valores que se mandan */
	uint32 input  = 0x0 <<pin;
	uint32 output = 0x1 <<pin;

		switch(portName){
		case GPIO_A:{/**Selecciona el puerto A */
			switch(State){
			case GPIO_INPUT:
				GPIOA->PDDR|=input;
				break;
			case GPIO_OUTPUT:
				GPIOA->PDDR|=output;
				break;
			default:
				break;
			}
			break;
		}

		case GPIO_B:/** Selecciona el puerto B*/
		{
			switch(State){
			case GPIO_INPUT:
				GPIOB->PDDR|=input;
				break;
			case GPIO_OUTPUT:
				GPIOB->PDDR|=output;
				break;
			default:
				break;
			}
			break;
		}
		case GPIO_C:/**Selecciona el puerto C */
		{
			switch(State){
			case GPIO_INPUT:
				GPIOC->PDDR|=input;
				break;
			case GPIO_OUTPUT:
				GPIOC->PDDR|=output;
				break;
			default:
				break;
			}
			break;
		}
		case GPIO_D:/** Selecciona el puerto D */
		{
			switch(State){
			case GPIO_INPUT:
				GPIOD->PDDR|=input;
				break;
			case GPIO_OUTPUT:
				GPIOD->PDDR|=output;
				break;
			default:
				break;
			}
			break;
		}
		default:/**Selecciona el puerto 5 */
			switch(State){
			case GPIO_INPUT:
				GPIOE->PDDR|=input;
				break;
			case GPIO_OUTPUT:
				GPIOE->PDDR|=output;
				break;
			default:
				break;
			}
			break;

		}
}
