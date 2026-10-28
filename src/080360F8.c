#include "ffta.h"

/* 0x080360F8..0x0803616C: 116 bytes, 45 instructions. */
typedef struct {
    u8 unknown_00[0x2E58];
    u8 unknown_flags_low : 2;
    u8 phase : 2;
    u8 unknown_flags_high : 4;
    u8 unknown_2E59[0x161];
    u8 page;
    u8 tick;
} MenuState;

extern MenuState g_state_02000000;
extern void func_08035E04(void);
extern void func_080CC198(void);

void func_080360F8(void)
{
    if (g_state_02000000.tick <= 19) {
        g_state_02000000.tick++;
    } else {
        g_state_02000000.tick = 1;
        if (g_state_02000000.page <= 4) {
            g_state_02000000.page++;
        } else {
            g_state_02000000.page = 1;
        }
    }
    func_08035E04();
    if (g_state_02000000.phase > 2) {
        g_state_02000000.phase = 0;
        func_080CC198();
    } else {
        g_state_02000000.phase++;
    }
}
