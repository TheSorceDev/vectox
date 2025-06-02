// Include Driver headers. - TSD
#include "drivers/video/framebuffer/include/fbdev.h"
#include "drivers/video/utils/include/video_utils.h"

// Include Font headers. - TSD
#include "font.h"

// Include STD headers. - TSD
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// System halt function. - TSD
static void hcf() {
    for (;;) {
#if defined (__x86_64__)
        asm volatile ("hlt");
#elif defined (__aarch64__) || defined (__riscv)
        asm volatile ("wfi");
#elif defined (__loongarch64)
        asm volatile ("idle 0");
#endif
    }
}

static bool shouldShutdown = false; // Keeps track if os should shutdown. - TSD

void kmain(void) { // Main Entry - TSD
    VFramebufferInit(); // Initalizing The Framebuffer system. - TSD

    while (!shouldShutdown) { // Main system loop. - TSD
        VFramebufferClear(0x16161A); // Clearing Screens backbuffer. - TSD

        FontDrawBitmapText("vectox", VMKPoint(20, 20));

        VFramebufferShow(); // Swaps backbufferr to screen. - TSD
    }

    VFramebufferRelease(); // Releasing Framebuffer variables. - TSD
}
