#include "ffta.h"

extern u8 data_02008158[];
extern u8 data_0200815C[];

/* 0801E038..0801E098: 96 bytes, 43 instructions. */
void func_0801E038(u8 mode, u8 *first, u8 *second, u8 *third)
{
    const u8 *values;

    if (mode == 1 || mode == 3) {
        values = data_02008158;

        if (first)
            *first = values[0];
        if (second)
            *second = values[1];
        if (third)
            *third = values[2];
    }
    if (mode == 2 || mode == 3) {
        values = data_0200815C;

        if (first)
            *first = values[0];
        if (second)
            *second = values[1];
        if (third)
            *third = values[2];
    }
}
