#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u8 *entries;
    u8 width;
} MapState;

extern MapState data_02007F10;

/* Complete target [0x0801CC7C, 0x0801CD06): 138 bytes, 66 instructions,
 * including the literal word data_02007F10 at 0x0801CCF0. */
u8 func_0801CC7C(u8 column, u8 row)
{
    u8 width;
    u8 depth;
    u8 x;
    u8 z;
    u8 *entries;

    func_0801CD4C(&width, &depth, &x, &z);
    if (column < x)
        return 0;
    if (row < z)
        return 0;
    if (column >= x + width)
        return 0;
    if (row >= z + depth)
        return 0;

    entries = data_02007F10.entries + row * data_02007F10.width * 2 + column * 2;
    return entries[0] != 0;
}
