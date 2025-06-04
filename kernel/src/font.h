#ifndef FONT_H
#define FONT_H

#include "drivers/video/utils/include/video_utils.h"

void FontDrawBitmapText(const char* msg, VPoint pos);
int FontDrawBitmapChar(const char c, VPoint pos);

#endif