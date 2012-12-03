#ifndef FLANGER_H
#define FLANGER_H

#include "Talkthrough.h"

#define FLANGER_MAX_NB_SAMPLES	512

void initFlanger(float a,float delay);
int applyFlanger(short* x, short sizeDelayLineX);

#endif /* FLANGER_H */
