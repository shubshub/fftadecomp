#include "ffta.h"

/* Target: complete [0x081483EC, 0x0814846C), 128 bytes.
 * f0b5041c0d1c2404240c2d042d0c1204160c1b041f0c1f202040f82189002140
 * 4b09f821c90121408a0ac01880180321faf748fb041c221c141c6c43240a0f49
 * 201c0840002800d01f24131c73431b0a181c0840002800d01f237a43120a101c
 * 0840002800d01f2259012143900208430004000cf0bc02bc08470000e0ff0000
 */
u16 func_081483EC(u16 color, u16 red_scale, u16 green_scale, u16 blue_scale)
{
    u32 red = color & 0x1F;
    u32 green = (color & 0x3E0) >> 5;
    u32 blue = (color & 0x7C00) >> 10;
    u32 average = (red + green + blue) / 3;

    red = average * red_scale;
    red >>= 8;
    if (red & 0xFFE0)
        red = 0x1F;

    green = average * green_scale;
    green >>= 8;
    if (green & 0xFFE0)
        green = 0x1F;

    blue = average * blue_scale;
    blue >>= 8;
    if (blue & 0xFFE0)
        blue = 0x1F;

    return red | (green << 5) | (blue << 10);
}
