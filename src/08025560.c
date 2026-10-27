#include "ffta.h"

typedef struct {
    u8 unknown_00[0x12];
    s16 position;
} PositionState;

extern PositionState *data_0200F438;

/* 08025560..08025584: 36 bytes, 16 instructions. */
s32 func_08025560(void)
{
    s16 position = data_0200F438->position;

    if (position < 0)
        return -1;
    return position > 0x55;
}
