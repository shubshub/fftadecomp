#include "ffta.h"

extern const u8 data_08393E0F[];
extern s32 func_081426B8(s32 numerator, s32 divisor);

/* Complete [0x08089748, 0x080897C4): 124 bytes, 57 instructions.
 * Target bytes:
 * f0b509040d0c2e1c1204120c111c1b041f0c041c002a01d100210de0954201d8
 * 142109e0880040188000401a311cb8f09fff01300004010c880040180004010c
 * 381c36302080023400220a4d031c48190078c01820800234501c0004020c481c
 * 0004010c042af2d9034978182080f0bc01bc00470f3e390836040000
 *
 * The five-tile sibling of func_080896C0 (src/080896C0.c): the same
 * prologue, ratio and tile loop, with a 0..20 ratio and a fixed base.
 * The output cursor, the tile local, the loop set-up order and the
 * integer-add table index are func_080896C0's text.
 */
void func_08089748(u16 *buffer, u16 first, u16 second, u16 third)
{
    u16 *output = buffer;
    const u8 *tiles;
    u32 tile;
    u16 value;
    u16 index;
    u16 i;

    if (second == 0)
        value = 0;
    else if (first <= second)
        value = 20;
    else
        value = func_081426B8(second * 19, first) + 1;

    index = value * 5;
    *output++ = third + 0x36;
    i = 0;
    tiles = data_08393E0F;
    tile = third + 0x36;
    for (; i < 5; i++, index++) {
        *output++ = *(const u8 *)(index + (u32)tiles) + tile;
    }
    *output = third + 0x436;
}
