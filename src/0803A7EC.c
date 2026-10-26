#include "ffta.h"

struct Entry0803A7EC {
    u8 first;
    u8 second;
    u8 unknown_02[2];
};

extern const struct Entry0803A7EC data_08391C08[28];
extern u32 func_0803A7C0(u32, u32, u32);

/* Target: [0x0803A7EC, 0x0803A836), 74 bytes, 33 instructions. */
s32 func_0803A7EC(u8 *index, u32 value)
{
    s32 i;

    for (i = 0; i < 28; i++) {
        if ((u8)func_0803A7C0(data_08391C08[i].first, value, 4) == 2 &&
            (u8)func_0803A7C0(data_08391C08[i].second, value, 4) == 2) {
            *index = i;
            return 1;
        }
    }
    return 0;
}
