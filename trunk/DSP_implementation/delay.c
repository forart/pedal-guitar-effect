#include "delay.h"
#include "Talkthrough.h"
#include <math.h>
	
void initDelay(float g, float delay_time)
{

	gain = (short) (g * pow(2, 15));
	delay = (FS * delay_time);
	
	if(delay >= SIZE_DELAY_LINE_X)
	{
		delay = SIZE_DELAY_LINE_X - 1;
	}
	
}	

int applyDelay(short* x, short sizeDelayLineX)
{	
	int yn;
		
	if ( x_pos - delay < 0)
		{
			yn = 32767 * x[x_pos] + gain * x[x_pos - delay + sizeDelayLineX];
		
		}
		else
		{
			yn = 32767 * x[x_pos] + gain * x[x_pos - delay];
		}
	
	return (int) yn << 1;
}
		
