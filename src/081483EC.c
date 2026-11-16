#include "ffta.h"

/* Complete target [0x081483EC, 0x0814846C): 128 bytes, 60 instructions,
 * including the 0xFFE0 literal pool word. */
u16 func_081483EC(u16 color, u16 red_scale, u16 green_scale, u16 blue_scale)
{
    u32 red = color & 0x1F;
    u32 green = (color & 0x3E0) >> 5;
    u32 blue = (color & 0x7C00) >> 10;
    u32 gray = (red + green + blue) / 3;

    red = gray;
    green = gray;
    blue = gray;

    red *= red_scale;
    red >>= 8;
    if (red & 0xFFE0)
        red = 0x1F;

    green *= green_scale;
    green >>= 8;
    if (green & 0xFFE0)
        green = 0x1F;

    blue *= blue_scale;
    blue >>= 8;
    if (blue & 0xFFE0)
        blue = 0x1F;

    return red | (green << 5) | (blue << 10);
}
