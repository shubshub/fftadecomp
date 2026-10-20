#include "0801CDA4.h"

void func_0801CDA4(u16 *out0, u16 *out1, u16 *out2)
{
    u8 width, height, left, top;
    u8 upper, lower;
    s32 center;

    read_map_dimensions(&width, &height, &left, &top);
    read_map_edges(&upper, &lower);
    center = (width * 32 + 16) >> 1;
    *out1 = (upper - lower) * 8;
    *out2 = (height * 32 + 16) >> 1;
    *out0 = center + 16 + left * 32;
    *out1 += lower * 16;
    *out2 += 16;
    *out2 += top * 32;
}
