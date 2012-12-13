#include "distortion.h"
#include "Talkthrough.h"

#include <math.h>

void initDistortion(float a, float b, float threshold)
{
	// float a:
	// --------
	// float b:
	// --------
	// Coefficents of the polynomial function y = a*x + b*x²
	//
	// float threshold:
	// ----------------
	// Threshold above which one the signal is equal to the
	// value of the threshold
	
	
	// Convertion into Q15
	dist_a = (short) ((4.0 / 16.0) * pow(2, 15));
	dist_b = (short) ((4.0 / 16.0) * pow(2, 15));
	
	// Convertion into Q31
	dist_threshold = (int) (threshold * pow(2, 31));
}

int applyDistortion(short* x, short sizeDelayLineX)
{
	int yn;
	
	if(x[x_pos] >= 0)
	{
		yn = dist_a * x[x_pos] - dist_b * (short) ((x[x_pos] * x[x_pos]) >> 15);
		// Puting yLn into (31.1) format and multiplying by 2^4
		yn = yn << 5;
		
		if(yn > dist_threshold)
		{
			yn = dist_threshold;
		}
	}
	else
	{
		yn = dist_a * x[x_pos] + dist_b * (short) ((x[x_pos] * x[x_pos]) >> 15);
		// Puting yLn into (31.1) format and multiplying by 16 (2^4)
		yn = yn << 5;
		
		if(yn < -dist_threshold)
		{
			yn = -dist_threshold;
		}
	}
	
	return yn;
}
