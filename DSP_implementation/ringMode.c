#include "ringMode.h"
#include "Talkthrough.h"
#include <math.h>


void initRingMode(float freq)
{
	float carrier;
	float a1,a2,b0;
	
	// Carrier Wave
	carrier = sin(2 * PI * (freq/FS));
	
	// Coefficients
	a1 = -2.0 * cos(carrier);
	a2 = 1.0;
	b0 = 1.0 * sin(carrier);
	
	a1 /= 4.0;
	a2 /= 4.0;
	b0 /= 4.0;
	
	// Convertion into Q15
	ring_a1 = (short) (a1 * pow(2,15));
	ring_a2 = (short) (a2 * pow(2,15));
	ring_b0 = (short) (b0 * pow(2,15));	
	
}

int applyRingMode(short* x, short sizeDelayLineX)
{
	
	int yn;
	
	cn = - ring_a1 * c1 - ring_a2 * c2 + (int) (ring_b0 << 15);	
	cn = cn << 3;	 
	c2 = c1;
	c1 = (short) (cn >> 16);
	ring_b0 = 0;
	
    yn = 2 * x[x_pos] * c1;         	// Ring Mode sound
  //yn = ring_modulated * c1;		// TwoSin wave
	
	return (int) yn;
}
