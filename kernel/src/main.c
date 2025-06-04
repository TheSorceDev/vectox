// Include Driver headers. - TSD
#include "drivers/video/framebuffer/include/fbdev.h"
#include "drivers/video/framebuffer/include/simplefb.h"
#include "drivers/video/utils/include/video_utils.h"

// Include Font headers. - TSD
#include "logo.h"
#include "vecmap.h"
#include "font.h"

// Include STD headers. - TSD
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static bool shouldShutdown = false; // Keeps track if os should shutdown. - TSD

// System halt function. - TSD
static void hcf(void) {
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

int bitmpwidth = 549;
int bitmpheight = 112;
int bitmpoutwidth = 555;
int bitmpoutheight = 113;

void systemCrash(const char* errorCode, const char* errorLocation) {
    char buffer[128];

    // Draw: "Error Code: [errorCode]" - TSD
    char* ptr = buffer;
    const char* label1 = "Error Code: ";
    while (*label1) *ptr++ = *label1++;
    while (*errorCode) *ptr++ = *errorCode++;
    *ptr = '\0';
    FontDrawBitmapText(buffer, VMKPoint(40, (SimpleFBGetSize().height / 2) - 24));

    // Draw: "Location: [errorLocation]" - TSD
    ptr = buffer;
    const char* label2 = "Location: ";
    while (*label2) *ptr++ = *label2++;
    while (*errorLocation) *ptr++ = *errorLocation++;
    *ptr = '\0';
    FontDrawBitmapText(buffer, VMKPoint(40, (SimpleFBGetSize().height / 2) - 8));

    // Draw static strings - TSD
    FontDrawBitmapText("\x01 ectox will now halt.", VMKPoint(40, (SimpleFBGetSize().height / 2) + 14));
    FontDrawBitmapText("Please report system crashes at https://github.com/TheSorceDev/vectox", VMKPoint(40, SimpleFBGetSize().height - 40));

    VFramebufferShow(); 
    
    hcf();
    shouldShutdown = true;
}

void kmain(void) { // Main Entry - TSD
    VFramebufferInit(); // Initalizing The Framebuffer system. - TSD

    while (!shouldShutdown) { // Main system loop. - TSD
        VFramebufferClear(0x16161A); // Clearing Screens backbuffer. - TSD

        FontDrawBitmapText("\x01 ectox Shell", VMKPoint(20, 20));
        FontDrawBitmapText("\x01   ~/ &", VMKPoint(20, 55));

        VFramebufferShow(); // Swaps backbufferr to screen. - TSD
    }

    VFramebufferRelease(); // Releasing Framebuffer variables. - TSD
}
