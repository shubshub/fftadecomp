#include "ffta.h"

typedef struct {
    u8 unknown_00[0x145C];
    u16 values[16];
} ValueState;

extern ValueState *data_0200F448;

/* 0805D174..0805D1A2: 46 bytes. */
u8 func_0805D174(void)
{
    s32 index;

    for (index = 0; index < 16; index++) {
        if (data_0200F448->values[index] != 0)
            return 1;
    }
    return 0;
}
