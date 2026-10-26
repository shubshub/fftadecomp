#include "ffta.h"

/* 0x08147830 - 172 bytes. */
u16 func_08147830(u16 first, u16 second, u8 second_weight, u8 first_weight)
{
    u32 second_red;
    u32 second_green;
    u32 second_blue;
    u32 first_red;
    u32 first_green;
    u32 first_blue;

    second_red = second & 0x1F;
    second_green = (second & 0x3E0) >> 5;
    second_blue = (second & 0x7C00) >> 10;
    first_red = first & 0x1F;
    first_green = (first & 0x3E0) >> 5;
    first_blue = (first & 0x7C00) >> 10;
    second_red = second_red * second_weight / 16;
    second_green = second_green * second_weight / 16;
    second_blue = second_blue * second_weight / 16;
    first_red = first_red * first_weight / 16;
    first_green = first_green * first_weight / 16;
    first_blue = first_blue * first_weight / 16;
    first_red += second_red;
    first_green += second_green;
    first_blue += second_blue;
    if (first_red > 31)
        first_red = 31;
    if (first_green > 31)
        first_green = 31;
    if (first_blue > 31)
        first_blue = 31;
    return first_red | (first_green << 5) | (first_blue << 10);
}
