#include "ffta.h"

struct State0801AE20 {
    u16 unknown_00[22];
    u16 flags : 16;
};

extern struct State0801AE20 g_state_02007F40;

/* 0x0801AE20..0x0801AE34: 20 bytes. */
void func_0801AE20(void)
{
    g_state_02007F40.flags |= 0x100;
}
