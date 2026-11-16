#include "ffta.h"

extern s32 func_081426B8(s32, s32);
extern s16 func_08007A60(u8);

/* Complete [0x08087660, 0x080876F4): 148 bytes, 72 instructions.
 * f0b5474680b4061c8846111c1c1c0906090e2406240e4020bbf01ef860430006
 * 000e80f7edf90004c0142021091a0904090c00271f2084462020451a31881f20
 * 084068434446a21c9046002800da1f3043110a04500d614608406843002800da
 * 1f30401141011943900e624610406843002800da1f304011800201432180781c
 * 0004070c02360f2fd8d908bc9846f0bc01bc0047
 *
 * The 16-colour form of func_08087554 (src/08087554.c): each channel of
 * one palette row is scaled by (32 - amount) / 32. */
void func_08087660(const u16 *source, u16 *destination, u8 period, u8 phase)
{
    u16 amount = 32 - (func_08007A60(func_081426B8(64, period) * phase) >> 3);
    u16 i;

    for (i = 0; i < 16; ++i, ++source) {
        *destination++ = (*source & 31) * (32 - amount) / 32
            | ((((*source >> 5) & 31) * (32 - amount) / 32) << 5)
            | ((((*source >> 10) & 31) * (32 - amount) / 32) << 10);
    }
}
