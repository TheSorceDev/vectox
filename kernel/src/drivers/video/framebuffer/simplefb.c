// Include Driver headers. - TSD
#include "include/simplefb.h"
#include "../utils/include/video_utils.h"

// Include Utils headers. - TSD
#include "../../../string.h"

// Include STD headers. - TSD
#include <limine.h>
#include <stddef.h>
#include <stdint.h>

// Backbuffer width and height. - TSD
// This will be changed soon to be dynamic - TSD
#define MAX_WIDTH  1920
#define MAX_HEIGHT 1080
#define MAX_BPP    4

// Initalizing values for the Backbuffer. - TSD
static uint8_t backbuffer[MAX_WIDTH * MAX_HEIGHT * MAX_BPP];
static struct limine_framebuffer *framebuffer = NULL;
static uint32_t width = 0, height = 0, pitch = 0, bpp = 0;

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// Asigning values to initalized variables. - TSD
void SimpleFBInit(void) {
    framebuffer = framebuffer_request.response->framebuffers[0];
    width  = framebuffer->width;
    height = framebuffer->height;
    pitch  = framebuffer->pitch;
    bpp    = framebuffer->bpp;
}

// Returning the Framebuffer Size- - TSD
VRect SimpleFBGetSize(void) {
    return VMKRect(width, height);
}

// Swaping the Backbuffer with the Framebuffer - TSD
void SimpleFBSwap(void) {
    uint8_t *fb_addr = (uint8_t *)framebuffer->address;
    uint32_t buf_pitch = width * (bpp / 8);

    for (uint32_t y = 0; y < height; y++) {
        memcpy(fb_addr + y * pitch, backbuffer + y * buf_pitch, pitch);
    }
}

void SimpleFBDraw(VPoint p, VColor col) {
    if (p.x >= width || p.y >= height) {
        return;
    }

    uint32_t *buffer = (uint32_t *)backbuffer;
    buffer[p.y * width + p.x] = col;
}