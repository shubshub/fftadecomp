#include "ffta.h"

/* 0x081478DC..0x08147958: 124 bytes, 62 reachable instructions. */
u16 func_081478DC(u16 color, u8 amount)
{
    u16 red = color & 0x1F;
    u16 green = (color & 0x3E0) >> 5;
    u16 blue = (color & 0x7C00) >> 10;

    red += ((31 - red) * amount) / 16;
    green += ((31 - green) * amount) / 16;
    blue += ((31 - blue) * amount) / 16;
    if (red > 31)
        red = 31;
    if (green > 31)
        green = 31;
    if (blue > 31)
        blue = 31;
    return red | (green << 5) | (blue << 10);
}
