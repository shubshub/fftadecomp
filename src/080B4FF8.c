#include "ffta.h"

/* func_080B4FF8: complete target [0x080B4FF8, 0x080B50EE), 246 bytes,
 * 121 instructions, including the literal pool.
 * Pulses colours 2..15 of one palette: each channel climbs to 31, then
 * falls until it is back at 15.  The three directions of a colour are kept
 * in the low bits of one byte per colour. */
struct PalettePulse {
    u8 unknown_00[0x45];
    u8 directions[16];
};

extern u16 data_03003A60[];

void func_080B4FF8(struct PalettePulse *pulse, s32 palette)
{
    u16 *colors = &data_03003A60[palette * 16 + 2];
    s32 i;

    for (i = 2; i < 16; i++, colors++) {
        u16 red = *colors & 0x1F;
        u16 green = (*colors & 0x3E0) >> 5;
        u16 blue = (*colors & 0x7C00) >> 10;

        if (pulse->directions[i] & 1) {
            red++;
            if (red > 31) {
                red = 30;
                pulse->directions[i] &= ~1;
            }
        } else if (red <= 15) {
            red++;
            pulse->directions[i] |= 1;
        } else {
            red--;
        }

        if (pulse->directions[i] & 2) {
            green++;
            if (green > 31) {
                green = 30;
                pulse->directions[i] &= ~2;
            }
        } else if (green <= 15) {
            green++;
            pulse->directions[i] |= 2;
        } else {
            green--;
        }

        if (pulse->directions[i] & 4) {
            blue++;
            if (blue > 31) {
                blue = 30;
                pulse->directions[i] &= ~4;
            }
        } else if (blue <= 15) {
            blue++;
            pulse->directions[i] |= 4;
        } else {
            blue--;
        }

        *colors = red | (green << 5) | (blue << 10);
    }
}
