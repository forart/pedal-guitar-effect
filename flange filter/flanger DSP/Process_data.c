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
void Process_Data(void)
{
	/* Variables */
	int i, out, fs = 48000;
		
	x[x_pos] = (short) (iChannel0LeftIn >> 16);
	//y[i] = x[x_pos]; //I create an array Y with the same info than X
	
	// Filtering. I decided to put an delay of 512 elements
	// The delay array was made in delay.c
	for(i = 0; i < 512; i++)
	{
		if(x_pos + i < 512)
		{			
			out = x[x_pos + i] + a*x[x_pos + i - delay[x_pos + i]];
			
		}
		else
		{
			out = x[x_pos + i - 511] + a*x[x_pos + i - 511 - delay[x_pos + i - 511]];
		}
			
	}
	
	// put the output into Q15 format
	out  = out << 1;

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
	iChannel0LeftOut = iChannel0RightOut;
}
