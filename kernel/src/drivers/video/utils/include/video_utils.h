#ifndef VIDEO_UTILS_H
#define VIDEO_UTILS_H

#include <stdint.h>

typedef struct {
    int x;
    int y;
} VPoint;
typedef struct {
    int width;
    int height;
} VRect;

#define VMKPoint(x, y) ((VPoint){ (x), (y) })
#define VMKRect(width, height) ((VRect){ (width), (height) })
typedef uint32_t VColor;

#endif