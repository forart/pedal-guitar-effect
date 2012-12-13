#include "compressor.h"
#include "Talkthrough.h"

int thresholdc, ratio;

void initCompr(int a, int b)
{
	thresholdc=a;
	ratio=b;	
}


int applyComp(short* x)
{	
	int yn;
	
	if((x[x_pos] <= -thresholdc) || ( x[x_pos] >= thresholdc))
		
		yn = thresholdc + (x[x_pos]-thresholdc)*ratio;
	
	else 
		yn = x[x_pos];
		
	
	return (yn<<16);
}
