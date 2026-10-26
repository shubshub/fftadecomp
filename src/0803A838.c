#include "ffta.h"

/* 0x0803A838..0x0803A8C0: 136 bytes. */
typedef struct {
    u8 value;
    u8 unknown_01[3];
} PatternEntry;

extern const PatternEntry data_08391BBC[];
extern const PatternEntry data_08391BD0[];
extern const PatternEntry data_08391BE8[];

extern u8 func_0803A7C0(u8 value, const u8 *values, s32 count);

u8 func_0803A838(u8 *index, const u8 *values)
{
    s32 i;

    for (i = 0; i < 5; i++) {
        if (func_0803A7C0(data_08391BBC[i].value, values, 4) == 4) {
            *index = i;
            return 1;
        }
    }
    for (i = 0; i < 6; i++) {
        if (func_0803A7C0(data_08391BD0[i].value, values, 4) == 3) {
            *index = i;
            return 2;
        }
    }
    for (i = 0; i < 8; i++) {
        if (func_0803A7C0(data_08391BE8[i].value, values, 4) == 2) {
            *index = i;
            return 3;
        }
    }
    return 0;
}
