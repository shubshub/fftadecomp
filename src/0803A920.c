#include "ffta.h"

typedef struct {
    u8 value;
    u8 unknown_01[3];
} Pattern0803A920;

extern const Pattern0803A920 data_08391BE8[8];
extern u8 func_0803A7C0(u8 value, const u8 *values, s32 length);

/* Complete [0x0803A920, 0x0803A958): 56 bytes, 24 instructions. */
u8 func_0803A920(u8 *index, const u8 *values)
{
    s32 i;

    for (i = 0; i < 8; i++) {
        if (func_0803A7C0(data_08391BE8[i].value, values, 2) == 2) {
            *index = i;
            return 3;
        }
    }
    return 0;
}
