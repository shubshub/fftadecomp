#include "ffta.h"

extern u16 g_state_02007F40[];

/* 0x0801C984: 102 bytes of Thumb code, two alignment bytes and a data literal. */
void func_0801C984(s16 first, s16 second, s16 third,
                   s16 *firstOutput, s16 *secondOutput)
{
    s16 scaled[3];
    s16 *low = &scaled[0];
    s16 *mid = &scaled[1];
    s16 *high = &scaled[2];
    u16 *origin;
    s32 a, b, difference;
    u16 originX;
    s16 *readback;

    difference = first - third;
    origin = g_state_02007F40;
    *low = (difference >> 1) + origin[0x10];
    *mid = ((first + third) >> 2) - (second >> 1) + origin[0x11];
    *high = first + third;
    readback = scaled;
    b = *mid;
    originX = origin[0x12];
    a = *readback;
    *firstOutput = a - originX;
    *secondOutput = b - origin[0x13];
}
