#include "ffta.h"

extern u8 g_state_02007F40[];

/* 0x0801E620..0x0801E630: 16 bytes. */
void func_0801E620(u8 *first, u8 *second)
{
    *first = g_state_02007F40[2];
    *second = g_state_02007F40[3];
}
