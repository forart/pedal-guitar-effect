#include "Talkthrough.h"
#include <math.h>

#include "distortion.h"
#include "wah_wah.h"
#include "flanger.h"

//--------------------------------------------------------------------------//
// Function:	Process_Data()												//
//																			//
// Description: This function is called from inside the SPORT0 ISR every 	//
//				time a complete audio frame has been received. The new 		//
//				input samples can be found in the variables iChannel0LeftIn,//
//				iChannel0RightIn, iChannel1LeftIn and iChannel1RightIn 		//
//				respectively. The processed	data should be stored in 		//
//				iChannel0LeftOut, iChannel0RightOut, iChannel1LeftOut,		//
//				iChannel1RightOut, iChannel2LeftOut and	iChannel2RightOut	//
//				respectively.												//
//--------------------------------------------------------------------------//
void Process_Data(void)
{
	short tst = 100;

	// FlagAMode ændres ved at trykke på pushbutton	
	switch (FlagAMode) {
		case PASS_THROUGH : 
		
			iChannel0LeftOut = iChannel0LeftIn;
			
			iChannel0RightOut = iChannel0RightIn;
			iChannel0RightOut = iChannel0LeftIn; // left ind ud på begge udgange..
			
			iChannel1LeftOut = iChannel1LeftIn;
			iChannel1RightOut = iChannel1RightIn;
			break;
			
		case FIR_FILTER_ACTIVE :
		
			// Delay-line
			// the input signal is an int so we shift it to get the 16th most significant
			// bit into the delay-line which is short
			x[x_pos] = (short) (iChannel0LeftIn >> 16);			

			//yn = (22937 * (short) (applyWahWah(x, SIZE_DELAY_LINE_X) >> 16)) 
			//	+ (9830 * (short) (applyDistortion(x, SIZE_DELAY_LINE_X) >> 16));
			
			yn = applyFlanger(x, SIZE_DELAY_LINE_X);
						
			if(++x_pos >= SIZE_DELAY_LINE_X)
			{
				x_pos = 0;
			}
			if(++y_pos >= SIZE_DELAY_LINE_Y)
			{
				y_pos = 0;
			}
			
			// Update y delay-line
			y[y_pos] = (short) (yn >> 16);
			
			// Set the output
			iChannel0LeftOut = yn;
			iChannel0RightOut = yn;
			
			
			//=========== Debug ===========
			if(tst == 100)
			{
				if(myCounter < 2000)
				{
					yPlot[myCounter] = yn;
					xPlot[myCounter] = x[x_pos];
					myCounter++;
				}
				tst = 0;
			}
			else
			{
				tst++;
			}
			//========= End debug =========
			break;

			
		case IIR_FILTER_ACTIVE :
	
			
			break;
	
	}	// end switch
	
	
}
