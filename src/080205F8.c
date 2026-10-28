#include "ffta.h"

/* 0x080205F8..0x08020618: 32 bytes / 13 instructions. */
struct State080205F8 {
    u8 unknown_00[0x184];
    u8 busy;
};

extern struct State080205F8 g_state_02007F40;

u8 func_080205F8(void)
{
    u8 ready = 0;

    if (g_state_02007F40.busy == 0)
        ready = 1;
    return ready;
}
