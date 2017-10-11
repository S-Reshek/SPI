#include "SPI.h"
#include "MK64F12.h"

/*it enable the clock module of the SPI by modifying the MDIS bits*/
void SPI_enable(SPI_ChannelType channel){
	switch(channel){/** Selecting the channel*/
		case SPI_0: /** SPI 0 is selected*/
			SPI0->MCR &= ~(SPI_MCR_MDIS_MASK);
			break;
		case SPI_1: /** SPI 1 is selected*/
			SPI1->MCR &= ~(SPI_MCR_MDIS_MASK);
			break;
		default: /** SPI 2 is selected*/
			SPI2->MCR &= ~(SPI_MCR_MDIS_MASK);
	}
}


/*It activate the clock gating*/
void SPI_clk(SPI_ChannelType channel){
	switch(channel){/** Selecting the channel*/
		case SPI_0: /** SPI 0 is selected*/
			SIM->SCGC6 |= SPI0_CLOCK_GATING;
			break;
		case SPI_1: /** SPI 1 is selected*/
			SIM->SCGC6 |= SPI2_CLOCK_GATING;
			break;
		case SPI_2: /** SPI 2 is selected*/
			SIM->SCGC3 |= SPI2_CLOCK_GATING;
			break;
	}
}

/*It configure the SPI as a master or slave depending on the value of masterOrslave*/
void SPI_setMaster(SPI_ChannelType channel, SPI_MasterType masterOrSlave){
	switch(channel){/** Selecting the channel*/
		case SPI_0: /** SPI 0 is selected*/
			if(masterOrSlave == SPI_MASTER){
				SPI0->MCR |= SPI_MCR_MSTR_MASK;
			}else if(masterOrSlave == SPI_SLAVE){
				SPI0->MCR &= ~(SPI_MCR_MSTR_MASK);
			}
			break;
		case SPI_1: /** SPI 1 is selected*/
			if(masterOrSlave == SPI_MASTER){
				SPI1->MCR |= SPI_MCR_MSTR_MASK;
			}else if(masterOrSlave == SPI_SLAVE){
				SPI1->MCR &= ~(SPI_MCR_MSTR_MASK);
			}
			break;
		case SPI_2: /** SPI 2 is selected*/
			if(masterOrSlave == SPI_MASTER){
				SPI2->MCR |= SPI_MCR_MSTR_MASK;
			}else if(masterOrSlave == SPI_SLAVE){
				SPI2->MCR &= ~(SPI_MCR_MSTR_MASK);
			}
			break;
	}
}


/*It activate the TX and RX FIFOs of the SPI depending on the value of enableOrdisable*/
void SPI_FIFO(SPI_ChannelType channel, SPI_EnableFIFOType enableOrDisable){
	switch(channel){/** Selecting the channel*/
		case SPI_0: /** SPI 0 is selected*/
			if(enableOrDisable == SPI_DISABLE_FIFO){
				SPI0->MCR |= SPI_MCR_DIS_TXF_MASK;
				SPI0->MCR |= SPI_MCR_DIS_RXF_MASK;
			}else if(enableOrDisable == SPI_ENABLE_FIFO){
				SPI0->MCR &= ~(SPI_MCR_DIS_TXF_MASK);
				SPI0->MCR &= ~(SPI_MCR_DIS_RXF_MASK);
			}
			break;
		case SPI_1: /** SPI 1 is selected*/
			if(enableOrDisable == SPI_DISABLE_FIFO){
				SPI1->MCR |= SPI_MCR_DIS_TXF_MASK;
				SPI1->MCR |= SPI_MCR_DIS_RXF_MASK;
			}else if(enableOrDisable == SPI_ENABLE_FIFO){
				SPI1->MCR &= ~(SPI_MCR_DIS_TXF_MASK);
				SPI1->MCR &= ~(SPI_MCR_DIS_RXF_MASK);
			}
			break;
		case SPI_2: /** SPI 2 is selected*/
			if(enableOrDisable == SPI_DISABLE_FIFO){
				SPI0->MCR |= SPI_MCR_DIS_TXF_MASK;
				SPI0->MCR |= SPI_MCR_DIS_RXF_MASK;
			}else if(enableOrDisable == SPI_ENABLE_FIFO){
				SPI0->MCR &= ~(SPI_MCR_DIS_TXF_MASK);
				SPI0->MCR &= ~(SPI_MCR_DIS_RXF_MASK);
			}
			break;
	}
}



/*It selects the clock polarity depending on the value of cpol*/
void SPI_clockPolarity(SPI_ChannelType channel, SPI_PolarityType cpol){
	switch(channel){/** Selecting the channel*/
		case SPI_0: /** SPI 0 is selected*/
			if(cpol == SPI_HIGH_POLARITY){
				SPI0->CTAR[0] |= SPI_CTAR_CPOL_MASK;
			}else if(cpol == SPI_LOW_POLARITY){
				SPI0->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
			}
			break;
		case SPI_1: /** SPI 1 is selected*/
			if(cpol == SPI_HIGH_POLARITY){
				SPI1->CTAR[0] |= SPI_CTAR_CPOL_MASK;
			}else if(cpol == SPI_LOW_POLARITY){
				SPI1->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
			}
			break;
		case SPI_2: /** SPI 2 is selected*/
			if(cpol == SPI_HIGH_POLARITY){
				SPI2->CTAR[0] |= SPI_CTAR_CPOL_MASK;
			}else if(cpol == SPI_LOW_POLARITY){
				SPI2->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
			}
			break;
		}
}



/*It selects the frame size depending on the value of frameSize and the macros that are defined above*/
void SPI_frameSize(SPI_ChannelType channel, uint32 frameSize){
	switch(channel){/** Selecting the channel*/
		case SPI_0: /** SPI 0 is selected*/
			SPI0->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);
			SPI0->CTAR[0] |= frameSize;
			break;
		case SPI_1: /** SPI 1 is selected*/
			SPI1->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);
			SPI1->CTAR[0] |= frameSize;
			break;
		case SPI_2: /** SPI 2 is selected*/
			SPI2->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);
			SPI2->CTAR[0] |= frameSize;
			break;
	}
}


/*It selects the clock phase depending on the value of cpha*/
void SPI_clockPhase(SPI_ChannelType channel, SPI_PhaseType cpha){
	switch(channel){/** Selecting the channel*/
		case SPI_0: /** SPI 0 is selected*/
			if(cpha == SPI_HIGH_PHASE){
				SPI0->CTAR[0] |= SPI_CTAR_CPHA_MASK;
			}else if(cpha == SPI_LOW_PHASE){
				SPI0->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);
			}
			break;
		case SPI_1: /** SPI 1 is selected*/
			if(cpha == SPI_HIGH_PHASE){
				SPI1->CTAR[0] |= SPI_CTAR_CPHA_MASK;
			}else if(cpha == SPI_LOW_PHASE){
				SPI1->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);
			}
			break;
		case SPI_2: /** SPI 2 is selected*/
			if(cpha == SPI_HIGH_PHASE){
				SPI2->CTAR[0] |= SPI_CTAR_CPHA_MASK;
			}else if(cpha == SPI_LOW_PHASE){
				SPI2->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);
			}
			break;
		}
}


/*It selects the baud rate depending on the value of baudRate and the macros that are defined above*/
void SPI_baudRate(SPI_ChannelType channel, uint32 baudRate){
	switch(channel){/** Selecting the channel*/
		case SPI_0: /** SPI 0 is selected*/
			SPI0->CTAR[0] |= SPI_CTAR_BR(baudRate);
			break;
		case SPI_1: /** SPI 1 is selected*/
			SPI1->CTAR[0] |= SPI_CTAR_BR(baudRate);
			break;
		case SPI_2: /** SPI 2 is selected*/
			SPI2->CTAR[0] |= SPI_CTAR_BR(baudRate);
			break;
		}
}


/*It selects if MSB or LSM bits is first transmitted*/
void SPI_mSBFirst(SPI_ChannelType channel, SPI_LSMorMSBType msb){
	switch(channel){/** Selecting the channel*/
		case SPI_0: /** SPI 0 is selected*/
			if(msb == SPI_LSM){
				SPI0->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
			}else if(msb == SPI_MSB){
				SPI0->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
			}
			break;
		case SPI_1: /** SPI 1 is selected*/
			if(msb == SPI_LSM){
				SPI1->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
			}else if(msb == SPI_MSB){
				SPI1->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
			}
			break;
		case SPI_2: /** SPI 2 is selected*/
			if(msb == SPI_LSM){
				SPI2->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
			}else if(msb == SPI_MSB){
				SPI2->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
			}
			break;
		}
}


/*It stars the SPI transmission by modifying the value of HALT bit*/
void SPI_startTranference(SPI_ChannelType channel){
	switch(channel){/** Selecting the channel*/
			case SPI_0: /** SPI 0 is selected*/
				SPI0->MCR &= ~(SPI_MCR_HALT_MASK);
				break;
			case SPI_1: /** SPI 1 is selected*/
				SPI1->MCR &= ~(SPI_MCR_HALT_MASK);
				break;
			default: /** SPI 2 is selected*/
				SPI2->MCR &= ~(SPI_MCR_HALT_MASK);
		}
}


/*It stops the SPI transmission by modifying the value of HALT bit*/
void SPI_stopTranference(SPI_ChannelType channel){
	switch(channel){/** Selecting the channel*/
			case SPI_0: /** SPI 0 is selected*/
				SIM->SCGC6 |= SPI_MCR_HALT_MASK;
				break;
			case SPI_1: /** SPI 1 is selected*/
				SIM->SCGC6 |= SPI_MCR_HALT_MASK;
				break;
			case SPI_2: /** SPI 2 is selected*/
				SIM->SCGC3 |= SPI_MCR_HALT_MASK;
				break;
		}
}


/*It transmits the information contained in data*/
void SPI_sendOneByte(uint8 Data){
	SPI0->PUSHR = (Data);
	while(0 == (SPI0->SR & SPI_SR_TCF_MASK));
	SPI0->SR |= SPI_SR_TCF_MASK;
}


/*It configures the SPI for transmission, this function as arguments receives a pointer to a constant structure where are all
 * the configuration parameters*/
void SPI_init(const SPI_ConfigType* SPI_Config){
SPI_clk(SPI_Config-> SPI_Channel);
GPIO_clockGating(SPI_Config -> GPIOForSPI.GPIO_portName);
GPIO_pinControlRegister(SPI_Config->GPIOForSPI.GPIO_portName, SPI_Config -> GPIOForSPI.SPI_clk, &(SPI_Config->pinControlRegisterPORTD));
GPIO_pinControlRegister(SPI_Config->GPIOForSPI.GPIO_portName, SPI_Config -> GPIOForSPI.SPI_Sout, &(SPI_Config->pinControlRegisterPORTD));
SPI_setMaster(SPI_Config-> SPI_Channel, SPI_Config -> SPI_Master);
SPI_setMaster(SPI_Config->SPI_Channel, SPI_Config ->SPI_Master);
SPI_FIFO(SPI_Config -> SPI_Channel, SPI_Config -> SPI_EnableFIFO);
SPI_enable(SPI_Config->SPI_Channel);
SPI_clockPolarity(SPI_Config -> SPI_Channel, SPI_Config -> SPI_Polarity);
SPI_frameSize(SPI_Config -> SPI_Channel, SPI_Config -> frameSize);
SPI_clockPhase(SPI_Config -> SPI_Channel, SPI_Config-> SPI_Phase);
SPI_baudRate(SPI_Config -> SPI_Channel, SPI_Config-> baudrate);
SPI_mSBFirst(SPI_Config -> SPI_Channel, SPI_MSB);

}
