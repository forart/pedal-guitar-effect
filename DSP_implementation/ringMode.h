#ifndef RINGMODE_H
#define RINGMODE_H

#include "Talkthrough.h"

void initRingMode(float freq);
int applyRingMode(short* x, short sizeDelayLineX);

#endif /* RINGMODE_H */

