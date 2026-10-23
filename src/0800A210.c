#include "ffta.h"

extern u8 g_state_02000000[];

/* 0x0800A210: 52 bytes, including the 12-byte literal pool. */
void func_0800A210(void *context, const u8 *instruction)
{
    u8 index = g_state_02000000[0x219C]++;

    ((u16 *)(g_state_02000000 + 0x2194))[index] =
        instruction[1] | (instruction[2] << 8);
}
