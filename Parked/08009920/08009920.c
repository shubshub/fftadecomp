#include "ffta.h"

/* Target: 0x08009920, 68 bytes including internal alignment and three literal words. */
void func_08009920(u8 mode)
{
    u8 *state = (u8 *)0x03000000;

    switch (mode) {
    case 1:
        state[0x0a] = 15;
        state[0x0b] = 4;
        break;
    case 2:
        state[0x0a] = 25;
        state[0x0b] = 8;
        break;
    default:
        state[0x0a] = 10;
        state[0x0b] = 2;
        break;
    }
}
