

#include "DataTypeDefinitions.h"
#include "MK64F12.h"
#include "PIT.h"

uint8 intrFlag_PIT0 = FALSE;
uint8 intrFlag_PIT1 = FALSE;
uint8 intrFlag_PIT2 = FALSE;

void PIT_delay(PIT_Timer_t pitTimer,float systemClock ,float period){
	float cycles = ((period*systemClock)-1); /** Calculo de la cantidad de ciclos necesaria para el tiempo requerido */

	switch(pitTimer){
	case PIT_0:
		PIT->CHANNEL[0].LDVAL = cycles; /** Se carga la cantidad de ciclos */
		PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TIE_MASK; //Enable timer 0  interrupts
		PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK; //Starts timer 0
		break;
	case PIT_1:
		PIT->CHANNEL[1].LDVAL = cycles;
		PIT->CHANNEL[1].TCTRL = PIT_TCTRL_TIE_MASK; //Enable timer 0  interrupts
		PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK; //Starts timer 0
		break;
	case PIT_2:
		PIT->CHANNEL[2].LDVAL = cycles/2;
		PIT->CHANNEL[2].TCTRL = PIT_TCTRL_TIE_MASK; //Enable timer 0  interrupts
		PIT->CHANNEL[2].TCTRL |= PIT_TCTRL_TEN_MASK; //Starts timer 0
		break;
	default:
		break;
	}
}


void PIT_clockGating(){
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK; /** Activacion del system clock gating del PIT */
	PIT->MCR = 0x0; /** Activar PIT */
}


uint8 PIT_getIntrStatus(uint8 PIT_n){
	/** Retorna el valor de la bandera de interrupcion*/
	switch(PIT_n){
		case PIT_0:
			return intrFlag_PIT0;
			break;
		case PIT_1:
			return intrFlag_PIT1;
			break;
		case PIT_2:
			return intrFlag_PIT2;
			break;
		default:
			return 0;
	}

}

void PIT_clear(uint8 PIT_n){
	/** Limpia la bandera de interrupcion */

	switch(PIT_n){
			case PIT_0:
				intrFlag_PIT0 = FALSE;
				break;
			case PIT_1:
				intrFlag_PIT1 = FALSE;
				break;
			case PIT_2:
				intrFlag_PIT2 = FALSE;
				break;
			default:
				break;
		}
}

void PIT_stop(uint8 PIT_n){
	/** Limpia la bandera de interrupcion */

	switch(PIT_n){
			case PIT_0:
				PIT->MCR = 0x11;
				break;
			case PIT_1:
				PIT->MCR = 0x11;
				break;
			case PIT_2:
				PIT->MCR = 0x11;
				break;
			default:
				break;
		}
}

void PIT0_IRQHandler(){
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;/** Timeout has occured*/
	PIT->CHANNEL[0].TCTRL = 0; //read control register for clear PIT flag, this is silicon bug
	PIT->CHANNEL[0].TCTRL &= ~(PIT_TCTRL_TIE_MASK);//disables PIT timer interrupt
	PIT->CHANNEL[0].TCTRL &= ~(PIT_TCTRL_TEN_MASK);//disables timer0
	intrFlag_PIT0 = TRUE;
}

void PIT1_IRQHandler(){
	PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK; /** Timeout has occured*/
	PIT->CHANNEL[1].TCTRL = 0; //read control register for clear PIT flag, this is silicon bug
	PIT->CHANNEL[1].TCTRL &= ~(PIT_TCTRL_TIE_MASK);//disables PIT timer interrupt
	PIT->CHANNEL[1].TCTRL &= ~(PIT_TCTRL_TEN_MASK);//disables timer0
	intrFlag_PIT1 = TRUE;
}

void PIT2_IRQHandler(){
	PIT->CHANNEL[2].TFLG |= PIT_TFLG_TIF_MASK;/** Timeout has occured*/
	PIT->CHANNEL[2].TCTRL = 0; //read control register for clear PIT flag, this is silicon bug
	PIT->CHANNEL[2].TCTRL &= ~(PIT_TCTRL_TIE_MASK);//enables PIT timer interrupt
	PIT->CHANNEL[2].TCTRL &= ~(PIT_TCTRL_TEN_MASK);//enables timer0
	intrFlag_PIT2 = TRUE;
}

