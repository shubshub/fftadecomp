#include "ffta.h"

/* 0x08013B08..0x08013B50: 72 bytes / 36 instructions. */
u16 func_08013B08(u8 width, u8 height, u16 flags)
{
    u8 columns = width;
    u8 rows = height;
    u16 layout = flags & 0x0C20;

    if ((flags & 2) == 0)
        columns -= 2;
    if (flags & 4)
        rows += 2;
    if (layout == 0)
        --rows;
    return columns * rows * 2;
}
