#include "vecmap.h"

#include "drivers/video/utils/include/video_utils.h"
#include "drivers/video/framebuffer/include/fbdev.h"
#include "drivers/video/framebuffer/include/simplefb.h"

#include <stdint.h>
#include <string.h>

static uint32_t parse_color(const char* hex) {
    uint32_t value = 0;
    for (int i = 0; i < 8; ++i) {
        char c = hex[i];
        value <<= 4;
        if (c >= '0' && c <= '9') value |= c - '0';
        else if (c >= 'A' && c <= 'F') value |= c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') value |= c - 'a' + 10;
    }
    return value;
}

void DrawVecmapCompressed(const char* bitmap, int width, int height, VPoint pos) {
    int px_index = 0;
    const char* ptr = bitmap;

    while (*ptr && px_index < width * height) {
        uint32_t count = 1;

        if (*ptr == '~') {
            ptr++;
            char count_hex[3] = {ptr[0], ptr[1], 0};
            count = (uint8_t)strtoul(count_hex, NULL, 16);
            ptr += 2;
        }

        char color_hex[9] = {0};
        strncpy(color_hex, ptr, 8);
        uint32_t px = parse_color(color_hex);
        ptr += 8;

        for (uint32_t i = 0; i < count; ++i) {
            int row = px_index / width;
            int col = px_index % width;

            uint8_t alpha = (px >> 24) & 0xFF;
            VPoint draw_pos = VMKPoint(pos.x + col, pos.y + row);

            if (alpha == 0x00) {
                // fully transparent, skip
            } else if (alpha == 0xFF) {
                VFramebufferDrawPx(draw_pos, px);
            } else {
                VColor bg = SimpleFBGetPixel(draw_pos);

                uint8_t bg_r = (bg >> 16) & 0xFF;
                uint8_t bg_g = (bg >> 8) & 0xFF;
                uint8_t bg_b = bg & 0xFF;

                uint8_t fg_r = (px >> 16) & 0xFF;
                uint8_t fg_g = (px >> 8) & 0xFF;
                uint8_t fg_b = px & 0xFF;

                uint8_t out_r = (fg_r * alpha + bg_r * (255 - alpha)) / 255;
                uint8_t out_g = (fg_g * alpha + bg_g * (255 - alpha)) / 255;
                uint8_t out_b = (fg_b * alpha + bg_b * (255 - alpha)) / 255;

                VColor result = 0xFF000000 | (out_r << 16) | (out_g << 8) | out_b;
                VFramebufferDrawPx(draw_pos, result);
            }

            px_index++;
        }
    }
}
