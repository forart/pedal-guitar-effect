#include "flanger.h"
#include "Talkthrough.h"
#include <math.h>

void initFlanger(float a,float delay)
{
	// 10ms is the maximum value that give 512 samples at fs = 48kHz
	
	unsigned short i;
	float resCos;	
	
	if(a < 0.999969482421875) // Maximum value for Q15
	{
		flanger_a = (short) (a * pow(2, 15));
	}
	else
	{
		flanger_a = 32767; // Maximum value in Q15
	}
	
	flanger_D = ceil(delay * FS);
	
	for(i = 0; i < (SIZE_DELAY_LINE_X - flanger_D - 1) >> 1; i++) // >> 1 is used to divide by 2
	{
		resCos = cos(2.0 * PI * (float) (i + flanger_D) / (float) (SIZE_DELAY_LINE_X - flanger_D - 1));
		flanger_delay[i] = (short) abs(resCos * (float) flanger_D);
	}
}


int applyFlanger(short* x, short sizeDelayLineX)
{
	int yn;
	static int count = 0;
	
	if(x_pos - flanger_delay[flanger_pos] < 0)
	{
		yn = 32767 * x[x_pos] +  flanger_a * x[x_pos - flanger_delay[flanger_pos] + sizeDelayLineX];
	}
	else
	{
		yn = 32767 * x[x_pos] +  flanger_a * x[x_pos - flanger_delay[flanger_pos]];
	}
	
	if(++count == 100)
	{
		count = 0;
		if(++flanger_pos >= (SIZE_DELAY_LINE_X - flanger_D - 1) >> 1) // >> 1 is used to divide by 2
		{
			flanger_pos = 0;
		}
	}
	
	// put the output into Q31 format
	return (int) yn << 1;
}
