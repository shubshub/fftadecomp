#include "ffta.h"

void func_080C14D8(u8 *first, u8 *second)
{
    u8 *state = (u8 *)0x020101F8;

    *first = state[0x54B2];
    *second = state[0x54B3];
}
