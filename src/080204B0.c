#include "ffta.h"

/* 0x080204B0..0x080204D0: 32 bytes / 13 instructions. */
struct LoaderState080204B0 {
    u8 unknown_00[0x16C];
    const u8 *current;
};

extern struct LoaderState080204B0 g_state_02007F40;

u32 func_080204B0(void)
{
    u32 idle = 0;

    if (g_state_02007F40.current == 0)
        idle = 1;
    return idle;
}
