// Include driver headers. - TSD
#include "drivers/video/utils/include/video_utils.h"
#include "drivers/video/framebuffer/include/fbdev.h"
#include "drivers/video/framebuffer/include/simplefb.h"

// Include util headers. - TSD
#include "font.h"

// Character Definition. - TSD
#include "font_bitmap.h"

// Include STD headers. - TSD
#include <stddef.h>

// Defining function to draw Characters to screen. - TSD
int FontDrawBitmapChar(char c, VPoint pos) {
    const VColor (*char_bitmap)[16] = NULL;

    switch (c) {
        case 'A': char_bitmap = bitmap_char_A; break;
        case 'B': char_bitmap = bitmap_char_B; break;
        case 'C': char_bitmap = bitmap_char_C; break;
        case 'D': char_bitmap = bitmap_char_D; break;
        case 'E': char_bitmap = bitmap_char_E; break;
        case 'F': char_bitmap = bitmap_char_F; break;
        case 'G': char_bitmap = bitmap_char_G; break;
        case 'H': char_bitmap = bitmap_char_H; break;
        case 'I': char_bitmap = bitmap_char_I; break;
        case 'J': char_bitmap = bitmap_char_J; break;
        case 'K': char_bitmap = bitmap_char_K; break;
        case 'L': char_bitmap = bitmap_char_L; break;
        case 'M': char_bitmap = bitmap_char_M; break;
        case 'N': char_bitmap = bitmap_char_N; break;
        case 'O': char_bitmap = bitmap_char_O; break;
        case 'P': char_bitmap = bitmap_char_P; break;
        case 'Q': char_bitmap = bitmap_char_Q; break;
        case 'R': char_bitmap = bitmap_char_R; break;
        case 'S': char_bitmap = bitmap_char_S; break;
        case 'T': char_bitmap = bitmap_char_T; break;
        case 'U': char_bitmap = bitmap_char_U; break;
        case 'V': char_bitmap = bitmap_char_V; break;
        case 'W': char_bitmap = bitmap_char_W; break;
        case 'X': char_bitmap = bitmap_char_X; break;
        case 'Y': char_bitmap = bitmap_char_Y; break;
        case 'Z': char_bitmap = bitmap_char_Z; break;

        case 'a': char_bitmap = bitmap_char_a; break;
        case 'b': char_bitmap = bitmap_char_b; break;
        case 'c': char_bitmap = bitmap_char_c; break;
        case 'd': char_bitmap = bitmap_char_d; break;
        case 'e': char_bitmap = bitmap_char_e; break;
        case 'f': char_bitmap = bitmap_char_f; break;
        case 'g': char_bitmap = bitmap_char_g; break;
        case 'h': char_bitmap = bitmap_char_h; break;
        case 'i': char_bitmap = bitmap_char_i; break;
        case 'j': char_bitmap = bitmap_char_j; break;
        case 'k': char_bitmap = bitmap_char_k; break;
        case 'l': char_bitmap = bitmap_char_l; break;
        case 'm': char_bitmap = bitmap_char_m; break;
        case 'n': char_bitmap = bitmap_char_n; break;
        case 'o': char_bitmap = bitmap_char_o; break;
        case 'p': char_bitmap = bitmap_char_p; break;
        case 'q': char_bitmap = bitmap_char_q; break;
        case 'r': char_bitmap = bitmap_char_r; break;
        case 's': char_bitmap = bitmap_char_s; break;
        case 't': char_bitmap = bitmap_char_t; break;
        case 'u': char_bitmap = bitmap_char_u; break;
        case 'v': char_bitmap = bitmap_char_v; break;
        case 'w': char_bitmap = bitmap_char_w; break;
        case 'x': char_bitmap = bitmap_char_x; break;
        case 'y': char_bitmap = bitmap_char_y; break;
        case 'z': char_bitmap = bitmap_char_z; break;

        case '0': char_bitmap = bitmap_char_0; break;
        case '1': char_bitmap = bitmap_char_1; break;
        case '2': char_bitmap = bitmap_char_2; break;
        case '3': char_bitmap = bitmap_char_3; break;
        case '4': char_bitmap = bitmap_char_4; break;
        case '5': char_bitmap = bitmap_char_5; break;
        case '6': char_bitmap = bitmap_char_6; break;
        case '7': char_bitmap = bitmap_char_7; break;
        case '8': char_bitmap = bitmap_char_8; break;
        case '9': char_bitmap = bitmap_char_9; break;
        case '+': char_bitmap = bitmap_char_43; break;
        case '-': char_bitmap = bitmap_char_45; break;
        case '*': char_bitmap = bitmap_char_42; break;
        case '/': char_bitmap = bitmap_char_47; break;
        case '_': char_bitmap = bitmap_char_95; break;
        case '\\': char_bitmap = bitmap_char_92; break;
        case '&': char_bitmap = bitmap_char_38; break;
        case '%': char_bitmap = bitmap_char_37; break;
        case '$': char_bitmap = bitmap_char_36; break;
        case '"': char_bitmap = bitmap_char_34; break;
        case '?': char_bitmap = bitmap_char_63; break;
        case '!': char_bitmap = bitmap_char_33; break;
        case '\'': char_bitmap = bitmap_char_39; break;
        case '#': char_bitmap = bitmap_char_35; break;
        case '~': char_bitmap = bitmap_char_126; break;
        case '.': char_bitmap = bitmap_char_46; break;

        case ',': char_bitmap = bitmap_char_44; break;
        case ':': char_bitmap = bitmap_char_59; break;
        case ';': char_bitmap = bitmap_char_58; break;
        case '`': char_bitmap = bitmap_char_96; break;
        case '=': char_bitmap = bitmap_char_40; break;
        case '(': char_bitmap = bitmap_char_41; break;
        case ')': char_bitmap = bitmap_char_91; break;
        case '[': char_bitmap = bitmap_char_93; break;
        case ']': char_bitmap = bitmap_char_123; break;
        case '{': char_bitmap = bitmap_char_125; break;
        case '}': char_bitmap = bitmap_char_unused0; break;

        case '\x01': char_bitmap = bitmap_char_unused1; break;

        case ' ': return 7;

        default: char_bitmap = bitmap_char_unused3; break;
    }

    if (!char_bitmap) return 0;

    int max_col = 0;

    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 16; col++) {
            VColor px = char_bitmap[row][col];
            uint8_t alpha = (px >> 24) & 0xFF;

            if (alpha == 0) continue;

            VPoint draw_pos = VMKPoint(pos.x + col, pos.y + row);

            if (alpha == 0xFF) {
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

            if (col > max_col) max_col = col;
        }
    }


    return max_col + 1;
}

// Simple text bitmap rendering system. - TSD
void FontDrawBitmapText(const char* msg, VPoint pos) {
    int x = pos.x;
    int spacing = 1;

    for (int i = 0; msg[i] != '\0'; i++) {
        if (msg[i] == '\x01' && msg[i + 1] == ' ') {
            int char_width = FontDrawBitmapChar(msg[i], VMKPoint(x, pos.y));
            x += char_width + spacing - 2;
            i++;
            continue;
        }

        int char_width = FontDrawBitmapChar(msg[i], VMKPoint(x, pos.y));
        x += char_width + spacing;
    }
}
