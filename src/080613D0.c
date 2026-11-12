#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 *tilemap;
} Graphics080613D0;

extern Graphics080613D0 data_030008B0;

/* Complete [0x080613D0, 0x0806144C): 124 bytes including literals. */
void func_080613D0(void)
{
    u16 *tilemap = data_030008B0.tilemap;
    u16 *row = tilemap + 0x153;

    row[0] = 0xd069;
    row[1] = 0xd06a;
    row[2] = 0xd06b;
    row[3] = 0xd06c;
    row[4] = 0xd06d;
    tilemap[0x173] = 0xd06e;
    tilemap[0x174] = 0xd06f;
    tilemap[0x175] = 0xd070;
    tilemap[0x176] = 0xd071;
    tilemap[0x177] = 0xd072;
}
