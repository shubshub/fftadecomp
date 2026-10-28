#include "ffta.h"

/* Target: complete [0x08003454, 0x080034B6), 98 bytes, 49 instructions.
 * Each affine matrix spans the fourth halfwords of four OAM entries. */
void func_08003454(void)
{
    u16 *oam = (u16 *)0x07000000;
    s32 matrix = 32;

    while (--matrix >= 0) {
        *oam++ = 0x0200;
        *oam++ = 0;
        *oam++ = 0;
        *oam++ = 0x0100;
        *oam++ = 0x0200;
        *oam++ = 0;
        *oam++ = 0;
        *oam++ = 0;
        *oam++ = 0x0200;
        *oam++ = 0;
        *oam++ = 0;
        *oam++ = 0;
        *oam++ = 0x0200;
        *oam++ = 0;
        *oam++ = 0;
        *oam++ = 0x0100;
    }
}
