#include "ffta.h"

extern u8 data_02008158[];
extern u8 data_0200815C[];

/* Complete target: 0x0801DFDC..0x0801E038, 92 bytes. */
void func_0801DFDC(u8 mode, u8 first, u8 second, u8 third)
{
    u8 *values;

    if (mode == 1 || mode == 3) {
        values = data_02008158;

        if (first)
            values[0] = first;
        if (second)
            values[1] = second;
        if (third)
            values[2] = third;
    }
    if (mode == 2 || mode == 3) {
        values = data_0200815C;

        if (first)
            values[0] = first;
        if (second)
            values[1] = second;
        if (third)
            values[2] = third;
    }
}
