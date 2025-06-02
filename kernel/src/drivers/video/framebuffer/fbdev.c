// Include util headers. - TSD
#include "include/fbdev.h"
#include "include/simplefb.h"

// Include STD headers. - TSD
#include <limine.h>

// Framebuffer initalize function. - TSD
void VFramebufferInit(void) {
    SimpleFBInit();
}

// Draws pixel on screen on given position with given color. - TSD
void VFramebufferDrawPx(VPoint pos, VColor col) {
    SimpleFBDraw(pos, col);
}

// Clears the screen with color. - TSD
void VFramebufferClear(VColor col) {
    VRect size = SimpleFBGetSize();
    for (uint32_t y = 0; y < size.height; y++) {
        for (uint32_t x = 0; x < size.width; x++) {
            SimpleFBDraw(VMKPoint(x, y), col);
        }
    }
}

// Swaps backbuffer to Framebuffer to make rendered things visible to the screen. - TSD
void VFramebufferShow(void) {
    SimpleFBSwap();
}

// Releases Framebuffer. - TSD
void VFramebufferRelease(void) {
    
}