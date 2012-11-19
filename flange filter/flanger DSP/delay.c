#include "Talkthrough.h"
#include <math.h>

void calculate_delay(void)
{
	const double pi = 3.141597;
	unsigned int i;
	float a;
	short b;
	
	for (i=D+1; i<=xlen; i++) //calculates the delay array
	{
		//delay[i]=abs(round(D * cos (2*pi*i / (xlen-D-1))));
		a = 2*pi*i;
		a = ((a<<15) / (xlen-D-1)) >>15;
		b = cos(a);
		b = (D * (b<<15)) >>15;
		delay[i]=abs(round(b));
	}
	//return 0;
}