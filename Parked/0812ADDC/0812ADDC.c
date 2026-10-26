#include "ffta.h"

extern const u8 data_083A8306[];
extern void func_08001CF0(const void *, s32, s32, u32, u32, u32, u32,
                          u32, u32, u32, u32);
extern u32 func_08013A5C(u16 glyph);

/* Complete target: [0x0812ADDC, 0x0812AE8C), 176 bytes, 75 instructions.
 * Nine encoded byte pairs occupy state offsets 0x312 through 0x323. */
void func_0812ADDC(u8 *state, s16 x, s16 y)
{
    u8 i = 0;
    u16 advance = 0;
    const u8 *name = state + 0x312;

    for (; i < 9; i++)
    {
        func_08001CF0(data_083A8306, x + advance, y, 0, 0, 0, 0, 0,
                      i * 4, 0, 0);
        if (name[i * 2] == 0x40 && name[i * 2 + 1] == 0x73)
            advance += 6;
        else
            advance += func_08013A5C(((state[i * 2 + 0x312] << 8) |
                                      state[i * 2 + 0x313]) & 0x7FFF);
    }
}
