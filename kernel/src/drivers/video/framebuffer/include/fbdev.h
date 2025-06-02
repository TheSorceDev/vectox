#ifndef FBDEV_H
#define FBDEV_H

#include "../../utils/include/video_utils.h"

void VFramebufferInit(void);

void VFramebufferClear(VColor col);
void VFramebufferDrawPx(VPoint pos, VColor col);

void VFramebufferRelease(void);

void VFramebufferShow(void);

#endif