#ifndef SIMPLEFB_H
#define SIMPLEFB_H

#include "../../utils/include/video_utils.h"

void SimpleFBInit(void);
void SimpleFBDraw(VPoint p, VColor col);
VRect SimpleFBGetSize(void);
void SimpleFBSwap(void);

#endif

