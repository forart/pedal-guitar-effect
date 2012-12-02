#ifndef DISTORTION_H
#define DISTORTION_H

void initDistortion(float a, float b, float threshold);
int applyDistortion(short* x, short sizeDelayLineX);

#endif /* DISTORTION_H */
