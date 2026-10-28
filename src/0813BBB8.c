#include "ffta.h"

struct Timer0813BBB8 {
    u8 unknown_00[4];
    u8 frames;
    u8 enabled;
};

struct State0813BBB8 {
    u8 unknown_00[0x2fbc];
    u16 hours;
    u8 minutes;
    u8 seconds;
};

extern struct Timer0813BBB8 data_03000ED0;
extern struct State0813BBB8 g_state_02000000;

/* Target: [0x0813BBB8, 0x0813BC30), 120 bytes, 47 instructions. */
void func_0813BBB8(void)
{
    if (data_03000ED0.enabled != 0) {
        if (data_03000ED0.frames > 58) {
            data_03000ED0.frames = 0;
            if (g_state_02000000.seconds > 58) {
                g_state_02000000.seconds = 0;
                if (g_state_02000000.minutes > 58) {
                    g_state_02000000.minutes = 0;
                    if (g_state_02000000.hours > 998) {
                        g_state_02000000.seconds = 59;
                        g_state_02000000.minutes = 59;
                    } else {
                        g_state_02000000.hours++;
                    }
                } else {
                    g_state_02000000.minutes++;
                }
            } else {
                g_state_02000000.seconds++;
            }
        } else {
            data_03000ED0.frames++;
        }
    }
}
