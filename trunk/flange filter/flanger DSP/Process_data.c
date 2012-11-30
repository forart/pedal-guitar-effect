#include "Talkthrough.h"
//#include <delay.c>

/*******************************
I decided to put an delay of 512
********************************/

//--------------------------------------------------------------------------//
// Function:	Process_Data()												//
//																			//
// Description: This function calculates de input signal					//
//--------------------------------------------------------------------------//


/* Variables */
int i, out, pos, fs = 4800;


void Process_Data(void)
{
	
	switch (FlagAMode) 
	{
		case PASS_THROUGH : 
        	iChannel0LeftOut = iChannel0LeftIn;
                       
            iChannel0RightOut = iChannel0RightIn;
            iChannel0RightOut = iChannel0LeftIn; // left ind ud på begge udgange..
                       
            iChannel1LeftOut = iChannel1LeftIn;
            iChannel1RightOut = iChannel1RightIn;
        break;
                       
        case FIR_FILTER_ACTIVE :              
	
	
			//The Filter
		
			x[x_pos] = (short) (iChannel0LeftIn >> 16);
	
			// Filtering. I decided to put an delay of 512 elements
			// The delay array was made in delay.c
			for(i = 0; i < 512; i++)
			{
				pos = x_pos+i;
				
				if(pos <= 512)
				{
					if(pos - delay[pos] >= 0) {
						out = x[pos] + x[pos - delay[pos]];
					}
					else {
						out = x[pos] + x[(pos - delay[pos]) - 511];
					}
			
				}
				else
				{
					if(pos -511 - delay[pos] >= 0) {
						out = x[pos-511] + x[pos - 511 - delay[pos-511]];
					}
					else {
						out = x[pos - 511] + x[pos - 511 - delay[pos-511] - 511];
					}
					//out = x[pos - 511] + a*x[pos - 511 - delay[pos-511]];
				}
			
			}
	
			// put the output into Q15 format
			out  = out << 16;//And we multiply the amplitud by 10 to get it louder

			if(x_pos < 511)
				x_pos ++;
			else
				x_pos = 0;
	
	
			/*// Delaying 
			for (i=1; i<=D+1; i++) //makes our 0s signal y being as x. D = 512
			{
				y[i]=x[i];
			}
			for (i=D+1; i<=xlen; i++) //delays the signal adding the delay to the original one
			{
				y[i] = x[i] + a*x[i-delay[i]];
			}*/
	   
			iChannel0RightOut = out;
			iChannel0LeftOut = out;
		break;
                       
        case IIR_FILTER_ACTIVE :
       
                       
        break;
    }
}
