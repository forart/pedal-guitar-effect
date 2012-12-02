#include "wah_wah.h"
#include "Talkthrough.h"

#include <math.h>

void initWahWah(float damp, float minf, float maxf, float fw)
{	
	// float damp:
	// -----------
	// damping factor
	// lower the damping factor the smaller the pass band
	//
	// float minf:
	// -----------
	// Min centre cutoff frequency of variable bandpass filter
	//
	// float maxf:
	// -----------
	// Max centre cutoff frequency of variable bandpass filter
	//
	// float fw:
	// ---------
	// wah frequency, how many Hz per second are cycled through

	float wah_minfnf;
	float wah_maxfnf;
	float wah_af;
	
	// Calculation of the lenght (the period) of f1 which follow a triangle signal
	wah_f1Length = (int) (2 * ceil((float) (maxf - minf) / (fw / FS)));
	
	// Qiscretization of the minimal and maximal frequency
	wah_minfnf = 2.0 * sin((PI * minf) / FS);
	wah_maxfnf = 2.0 * sin((PI * maxf) / FS);
	
	wah_af = 2.0 * (wah_maxfnf - wah_minfnf) / wah_f1Length;
	// Multiplication of wah_a coeff by 2^16 because of its tiny value
	// The result of the multiplication with wah_a must be devided by 2^16
	wah_af = wah_af * pow(2, 16);

	// Convertion into Q15
	wah_minfn = (short) (wah_minfnf * pow(2, 15));
	wah_maxfn = (short) (wah_maxfnf * pow(2, 15));
	wah_a = (short) (wah_af * pow(2, 15));
	wah_q1 = (short) (2 * damp * pow(2, 15));
}

int applyWahWah(short* x, short sizeDelayLineX)
{
	short tmp = 0, tmp1 = 0;
	short f1;

	if(wah_f1Count <= wah_f1Length / 2)
	{
		f1 = (short)( (long int) (wah_a * wah_f1Count) >> 15);
		f1 += wah_minfn;
	}
	else
	{
		f1 = (short)( (long int) (wah_a * (wah_f1Length - wah_f1Count)) >> 15);
		f1 += wah_minfn;
	}

	wah_yh = x[x_pos] - wah_yl1 - (short) ((wah_q1 * wah_yb1) >> 15);
	tmp = wah_yb;
	wah_yb = (short) ((f1 * wah_yh) >> 15) + wah_yb1;
	wah_yb1 = tmp;
	tmp = wah_yl;
	wah_yl = (short) ((f1 * wah_yb) >> 15) + wah_yl1;
	wah_yl1 = tmp;
	
	
	if(wah_f1Count < wah_f1Length)
	{
		wah_f1Count++;
	}
	else
	{
		wah_f1Count = 0;
	}

	return (int) (wah_yh << 15);
			
}
