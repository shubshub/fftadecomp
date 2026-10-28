#include "ffta.h"

struct State0801B888 {
    u16 unknown_00[22];
    u16 flags;
};

extern struct State0801B888 g_state_02007F40;

/* 0x0801B888..0x0801B898: 16 bytes. */
u32 func_0801B888(void)
{
    return g_state_02007F40.flags & 1;
}
