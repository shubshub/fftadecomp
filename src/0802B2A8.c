#include "ffta.h"

/* 0x0802B2A8..0x0802B2E6: 62 bytes / 29 instructions. */
struct Tilemap;

extern void func_0802B2E8(struct Tilemap *tilemap, u8 x, u8 y,
                          u8 width, u8 height);

void func_0802B2A8(struct Tilemap *first, struct Tilemap *second, u8 x, u8 y)
{
    func_0802B2E8(first, x, y, 13, 2);
    func_0802B2E8(second, x, y, 13, 2);
}
