#include "Talkthrough.h"

//--------------------------------------------------------------------------//
// Function:	Sport0_RX_ISR												//
//																			//
// Description: This ISR is executed after a complete frame of input data 	//
//				has been received. The new samples are stored in 			//
//				iChannel0LeftIn, iChannel0RightIn, iChannel1LeftIn and 		//
//				iChannel1RightIn respectively.  Then the function 			//
//				Process_Data() is called in which user code can be executed.//
//				After that the processed values are copied from the 		//
//				variables iChannel0LeftOut, iChannel0RightOut, 				//
//				iChannel1LeftOut and iChannel1RightOut into the dma 		//
//				transmit buffer.											//
//--------------------------------------------------------------------------//
EX_INTERRUPT_HANDLER(Sport0_RX_ISR)
{
	// confirm interrupt handling
	*pDMA1_IRQ_STATUS = 0x0001;

	// copy input data from dma input buffer into variables
	iChannel0LeftIn = iRxBuffer1[INTERNAL_ADC_L0];
	iChannel0RightIn = iRxBuffer1[INTERNAL_ADC_R0];
	iChannel1LeftIn = iRxBuffer1[INTERNAL_ADC_L1];
	iChannel1RightIn = iRxBuffer1[INTERNAL_ADC_R1];

	// call function that contains user code
	Process_Data();				

	// copy processed data from variables into dma output buffer
	iTxBuffer1[INTERNAL_DAC_L0] = iChannel0LeftOut;
	iTxBuffer1[INTERNAL_DAC_R0] = iChannel0RightOut;
	iTxBuffer1[INTERNAL_DAC_L1] = iChannel1LeftOut;
	iTxBuffer1[INTERNAL_DAC_L2] = iChannel1LeftOut;
	iTxBuffer1[INTERNAL_DAC_R1] = iChannel1RightOut;
	iTxBuffer1[INTERNAL_DAC_R2] = iChannel1RightOut;
}


//--------------------------------------------------------------------------//
// Function:	FlagA_ISR													//
//																			//
// Parameters:	None														//
//																			//
// Return:		None														//
//																			//
// Description:	This ISR is called every time the button connected to PF8	//
//				is pressed.													//
//				The state of flag sLight_Move_Direction is changed, so the	//
//				shift-direction for the LED pattern in Timer0_ISR changes.	//
//--------------------------------------------------------------------------//
EX_INTERRUPT_HANDLER(FlagA_ISR)
{
	short dispLED;
	
	if(*pFIO_FLAG_C == 0x0100)
	{
		// confirm interrupt handling
		FIO_ANOM_0311_FLAG_W(0x0100,pFIO_FLAG_C);//*pFIO_FLAG_C = 0x0100, workaround for anomaly 05000311.
		
		// switch to next mode..
		FlagAMode--;
	}
	
	if(*pFIO_FLAG_C == 0x0200)
	{
		// confirm interrupt handling
		FIO_ANOM_0311_FLAG_W(0x0200,pFIO_FLAG_C);//*pFIO_FLAG_C = 0x0200, workaround for anomaly 05000311.
		
		// switch to next mode..
		FlagAMode++;
	}	
	
	if (FlagAMode == NUMBER_FLAGA_STATES) FlagAMode = PASS_THROUGH;
	else if(FlagAMode == -1) FlagAMode = FLANGER_ACTIVE;
	
	switch(FlagAMode)
	{
		case 0: dispLED = 0x00; break;
		case 1: dispLED = 0x20; break;
		case 2: dispLED = 0x10; break;
		case 3: dispLED = 0x30; break;
		case 4: dispLED = 0x08; break;
		case 5: dispLED = 0x28; break;
		case 6: dispLED = 0x18; break;
		case 7: dispLED = 0x38; break;
		case 8: dispLED = 0x04; break;
		case 9: dispLED = 0x24; break;
		case 10: dispLED = 0x14; break;
		case 11: dispLED = 0x34; break;
		case 12: dispLED = 0x0c; break;
		case 13: dispLED = 0x2c; break;
		case 14: dispLED = 0x1c; break;
		case 15: dispLED = 0x3c; break;
		case 16: dispLED = 0x02; break;
		case 17: dispLED = 0x22; break;
		default: dispLED = 0x0; break;
	}
	
	*pFlashA_PortB_Data = dispLED;
	ssync();

}

