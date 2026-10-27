#include "ffta.h"

/* 0x08022C2C..0x08022C44: 24 bytes / 10 instructions. */
struct State08022C2C {
    u8 unknown_00;
    u8 busy;
};

extern struct State08022C2C g_state_0200F390;

u8 func_08022C2C(void)
{
    u8 ready = 0;

    if (g_state_0200F390.busy == 0)
        ready = 1;
    return ready;
}
