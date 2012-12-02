#ifndef WAH_WAH_H
#define WAH_WAH_H

void initWahWah(float damp, float minf, float maxf, float fw);
int applyWahWah(short* x, short sizeDelayLineX);

#endif /* WAH_WAH_H */


