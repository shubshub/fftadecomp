#include "ffta.h"

/* Complete [0x08147958, 0x081479DA): 130 bytes, 65 instructions. */
u16 func_08147958(u16 color, u8 amount)
{
    s16 red = color & 0x001F;
    s16 green = (color & 0x03E0) >> 5;
    s16 blue = (color & 0x7C00) >> 10;

    red -= red * amount / 16;
    green -= green * amount / 16;
    blue -= blue * amount / 16;
    if (red < 0)
        red = 0;
    if (green < 0)
        green = 0;
    if (blue < 0)
        blue = 0;
    return (u16)red | ((u16)green << 5) | ((u16)blue << 10);
}
