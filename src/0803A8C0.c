#include "ffta.h"

struct Entry0803A8C0 {
    u8 id;
    u8 unknown_01[3];
};

extern const struct Entry0803A8C0 data_08391BD0[6];
extern const struct Entry0803A8C0 data_08391BE8[8];
extern u32 func_0803A7C0(u32, u32, u32);

/* Target: [0x0803A8C0, 0x0803A920), 96 bytes, 41 instructions. */
s32 func_0803A8C0(u8 *index, u32 value)
{
    s32 i;

    for (i = 0; i < 6; i++) {
        if ((u8)func_0803A7C0(data_08391BD0[i].id, value, 3) == 3) {
            *index = i;
            return 2;
        }
    }
    for (i = 0; i < 8; i++) {
        if ((u8)func_0803A7C0(data_08391BE8[i].id, value, 3) == 2) {
            *index = i;
            return 3;
        }
    }
    return 0;
}
