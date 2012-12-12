#ifndef TREMOLO_H
#define TREMOLO_H

#include "Talkthrough.h"

void initTremolo(float delta,float ftrem);
int applyTremolo(short* x, short sizeDelayLineX);

#endif /* TREMOLO_H */
