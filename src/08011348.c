#include "ffta.h"

extern u32 func_0801093C(u32 mode, u32 first, u32 second, u16 third,
                         u8 fourth, s16 fifth, s16 sixth, s16 seventh,
                         s16 eighth, s16 ninth, u16 tenth);

/* 08011348..080113B4: 108 bytes, 53 instructions. */
u32 func_08011348(u32 first, u32 second, u16 third, u8 fourth,
                  s16 fifth, s16 sixth, s16 seventh, s16 eighth,
                  s16 ninth, u16 tenth)
{
    return func_0801093C(2, first, second, third, fourth, fifth, sixth,
                         seventh, eighth, ninth, tenth);
}
