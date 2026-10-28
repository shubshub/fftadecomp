#include "ffta.h"

/* 0x0801D8B8..0x0801D8E6: 46 bytes. */
typedef struct {
    u8 unknown_00[0x228];
    u8 enabled;
    u8 mode;
} ModeState;

extern ModeState g_state_02007F40;

u8 func_0801D8B8(void)
{
    if (!g_state_02007F40.enabled) {
        return 0;
    }
    if (g_state_02007F40.mode != 3) {
        return 0;
    }
    return 1;
}
