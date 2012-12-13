#include "Talkthrough.h"

#include <stdlib.h>

#include "distortion.h"
#include "wah_wah.h"
#include "flanger.h"
#include "delay.h"
#include "ringMode.h"
#include "tremolo.h"
#include "compressor.h"
#include "noisegate.h"

void InitFilterCoefs(void) 
{
	//******************* Distortion *******************
		
	initDistortion(2.0 /* a */, 2.0 /* b */, 0.15);
	
	//********************* Wah-Wah ********************
	
	initWahWah(0.05 /* damp factor */, 500 /* minf */, 3000 /* maxf */, 4500 /* fw */);
	
	//********************* Flanger *********************
	
	initFlanger(1.0 /* a */, 1e-3 /* delay */);
	
	//********************** Delay *********************
	
	initDelay(0.9999 /* g */, 100e-3 /* delay_time */);
	
	//********************** Ring Mode *********************
	
	initRingMode(200 /* freq */);
	
	//********************** Tremolo *********************
	
	initTremolo( 0.8 /*delta*/, 4 /*ftrem*/);
	
	//********************** Compressor *********************
	
	initCompr(1500 /* threshold */, 0.5 /*ratio*/);
	
	//********************** Noise Gate *********************
	
	initNoise(50 /* threshold */, 0 /*ratio*/);
}



