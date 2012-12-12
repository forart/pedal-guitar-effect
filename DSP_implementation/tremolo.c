#include "tremolo.h"
#include "Talkthrough.h"
#include <math.h>


void initTremolo(float delta,float ftrem)
{
	float modulation;
	float a1t,a2t,b0t;
	
	// Modulating Wave
	modulation = ( delta * sin(2 * PI * (ftrem / FS) ) );
	
	// Coefficients
	a1t = -2.0 * cos(modulation);
	a2t = 1.0;
	b0t = 1.0 * sin(modulation);
	
	a1t /= 4.0;
	a2t /= 4.0;
	b0t /= 4.0;
	
	// Convertion into Q15
	trem_a1 = (short) (a1t * pow(2,15));
	trem_a2 = (short) (a2t * pow(2,15));
	trem_b0 = (short) (b0t * pow(2,15));	
	
}

int applyTremolo(short* x, short sizeDelayLineX)
{
	
	int yn;
	
	tn = - trem_a1 * t1 - trem_a2 * t2 + (int) (trem_b0 << 15);	
	tn = tn << 3;	 
	t2 = t1;
	t1 = (short) (tn >> 16);
	trem_b0 = 0;
	
    yn = x[x_pos] * t1;         	
  
	
	return (int) yn << 3;
}

