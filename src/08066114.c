#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u32 value;
} State08066114;

extern State08066114 *data_0200F454;

/* 0x08066114..0x08066120: 01 48 00 68 00 69 70 47 54 F4 00 02. */
u32 func_08066114(void)
{
    return data_0200F454->value;
}
