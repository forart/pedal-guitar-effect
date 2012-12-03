#include "Talkthrough.h"

#include <stdlib.h>

#include "distortion.h"
#include "wah_wah.h"
#include "flanger.h"

void InitFilterCoefs(void) 
{
	//******************* Distortion *******************
		
	initDistortion(4.0 /* a */, 4.0 /* b */, 0.30);
	
	//********************* Wah-Wah ********************
	
	initWahWah(0.05 /* damp factor */, 500 /* minf */, 3000 /* maxf */, 2500 /* fw */);
	
	//********************** Delay *********************
	
	initFlanger(1.0 /* a */, 1e-3 /* delay */);
}



