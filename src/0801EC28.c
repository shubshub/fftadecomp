#include "ffta.h"

extern u8 data_0200F1D0;
extern u32 func_0801E710(s16 first, s16 second, s16 third,
                         u8 fourth, u8 fifth, u8 sixth);

/* 0801EC28..0801EC78: 80 bytes, 36 instructions. */
u8 func_0801EC28(s16 first, s16 second, s16 third,
                 u8 fourth, u8 fifth, u8 sixth)
{
    u8 result;

    data_0200F1D0 = 1;
    result = func_0801E710(first, second, third, fourth, fifth, sixth);
    data_0200F1D0 = 0;
    return result;
}
