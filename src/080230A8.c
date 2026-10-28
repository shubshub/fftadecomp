#include "ffta.h"

struct State080230A8 {
    u8 phase;
    u8 unknown_01[0x95];
    u16 counter;
};

extern struct State080230A8 g_state_0200F390;

/* 0x080230A8..0x080230BC: 20 bytes. */
void func_080230A8(void)
{
    g_state_0200F390.counter = 3;
    g_state_0200F390.phase = 0x11;
}
