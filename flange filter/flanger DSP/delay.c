#include "Talkthrough.h"
#include <math.h>

void calculate_delay(void)
{
	const float pi = 3.141597;
	unsigned int i;
	
	//for (i=D+1; i<=xlen; i++)
	for (i=0; i<=xlen; i++) //calculates the delay array
	{
		delay[i] = abs(round(D * cos (2.0*pi* (float) i / (float) (1024-D-1)))); //from 512 to 0
	}
	//return 0;
}


