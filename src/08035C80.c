#include "ffta.h"

/* 0x08035C80..0x08035CAA: 42 bytes / 18 instructions. */
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_08035BD4(u16 *destination, u16 digits, u32 value, u16 flags);
extern void func_0808A604(u8 index, u8 command);

void func_08035C80(u32 value)
{
    u16 *destination = func_0808B8E4(2, 1, 1, 1);

    func_08035BD4(destination, 8, value, 0xD000);
    func_0808A604(2, 2);
}
