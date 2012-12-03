//--------------------------------------------------------------------------//
//																			//
//	 Name: 	Talkthrough for the ADSP-BF533 EZ-KIT Lite						//
//																			//
//--------------------------------------------------------------------------//
//																			//
//	(C) Copyright 2006 - Analog Devices, Inc.  All rights reserved.			//
//																			//
//	Project Name:	BF533 C Talkthrough TDM									//
//																			//
//	Date Modified:	04/03/03		Rev 1.0							//
//																			//
//	Software:		VisualDSP++4.5											//
//																			//
//	Hardware:		ADSP-BF533 EZ-KIT Board									//
//																			//
//	Connections:	Disconnect RSCLK0 and TSCLK0 (Turn SW9 pin 6 OFF)	    //
//                  Disconnect RFS0 and TFS0 (Turn SW9 pin 5 OFF)		    //
//                  Connect an input source (such as a radio) to the Audio	//
//					input jack and an output source (such as headphones) to //
//					the Audio output jack									//
//																			//
//	Purpose:		This program sets up the SPI port on the ADSP-BF533 to  //
//					configure the AD1836 codec.  The SPI port is disabled 	//
//					after initialization.  The data to/from the codec are 	//
//					transfered over SPORT0 in TDM mode						//
//																			//
//--------------------------------------------------------------------------//

#include "Talkthrough.h"
#include "sysreg.h"
#include "ccblkfn.h"

//--------------------------------------------------------------------------//
// Variables																//
//																			//
// Description:	The variables iChannelxLeftIn and iChannelxRightIn contain 	//
//				the data coming from the codec AD1836.  The (processed)		//
//				playback data are written into the variables 				//
//				iChannelxLeftOut and iChannelxRightOut respectively, which 	//
//				are then sent back to the codec in the SPORT0 ISR.  		//
//				The values in the array iCodec1836TxRegs can be modified to //
//				set up the codec in different configurations according to   //
//				the AD1885 data sheet.										//
//--------------------------------------------------------------------------//
// left input data from ad1836
int iChannel0LeftIn, iChannel1LeftIn;
// right input data from ad1836
int iChannel0RightIn, iChannel1RightIn;
// left ouput data for ad1836	
int iChannel0LeftOut, iChannel1LeftOut;
// right ouput data for ad1836
int iChannel0RightOut, iChannel1RightOut;
// array for registers to configure the ad1836
// names are defined in "Talkthrough.h"
volatile short sCodec1836TxRegs[CODEC_1836_REGS_LENGTH] =
{									
					DAC_CONTROL_1	| 0x000,
					DAC_CONTROL_2	| 0x000,
					DAC_VOLUME_0	| 0x3ff,
					DAC_VOLUME_1	| 0x3ff,
					DAC_VOLUME_2	| 0x3ff,
					DAC_VOLUME_3	| 0x3ff,
					DAC_VOLUME_4	| 0x3ff,
					DAC_VOLUME_5	| 0x3ff,
					ADC_CONTROL_1	| 0x000,
					ADC_CONTROL_2	| 0x180,
					ADC_CONTROL_3	| 0x000
					
};
// SPORT0 DMA transmit buffer
volatile int iTxBuffer1[8];
// SPORT0 DMA receive buffer
volatile int iRxBuffer1[8];

// init FlagAMode - hvad der skal ske ved pushbutton
short FlagAMode = FIR_FILTER_ACTIVE; 

// Filter-relateret
short x[SIZE_DELAY_LINE_X] = {0}; // init delay line
short x_pos = 0;
short y[SIZE_DELAY_LINE_Y] = {0}; // init delay line
short y_pos = 0;
int yn;

// Debug variables
int myCounter=0;
int yPlot[2000] = {0};
short xPlot[2000] = {0};

// distortion parameters
short dist_a;
short dist_b;
int dist_threshold;

// wah-wah parameters
short wah_f1;
int wah_f1Length;
int wah_f1Count = 0;
short wah_minfn;
short wah_maxfn;
short wah_a;
short wah_q1;
short wah_yh;
short wah_yb = 0;
short wah_yb1 = 0;
short wah_yl = 0;
short wah_yl1 = 0;

// flanger parameters
short flanger_a;
short flanger_D;
short flanger_pos = 0;
short flanger_count = 0;
short flanger_delay[512] = {0}; // Defined with the maximum size


//--------------------------------------------------------------------------//
// Function:	main														//
//																			//
// Description:	After calling a few initalization routines, main() just 	//
//				waits in a loop forever.  The code to process the incoming  //
//				data can be placed in the function Process_Data() in the 	//
//				file "Process_Data.c".										//
//--------------------------------------------------------------------------//
void main(void)
{

	InitFilterCoefs();
	
	sysreg_write(reg_SYSCFG, 0x32);		//Initialize System Configuration Register
	Init_EBIU();
	Init_Flash();
	Init1836();
	Init_Sport0();
	Init_DMA();
	Init_Interrupts();
	Init_Flags();
	
	Enable_DMA_Sport0();
	
	
	
	while(1);
}
