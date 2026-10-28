#include "ffta.h"

/* 0x0805D13C..0x0805D174: 56 bytes. */
typedef struct {
    u8 unknown_00[0x145C];
    u16 values[16];
} ValueState;

extern ValueState *data_0200F448;

void func_0805D13C(u16 value)
{
    s32 index;

    for (index = 0; index < 16; index++) {
        if (data_0200F448->values[index] != 0 && data_0200F448->values[index] == value) {
            data_0200F448->values[index] = 0;
            break;
        }
    }
}
