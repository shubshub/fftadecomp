#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u32 value;
} State080294FC;

extern State080294FC *data_0200F438;

/* 080294FC..08029508: 01 48 00 68 80 69 70 47 38 F4 00 02. */
u32 func_080294FC(void)
{
    return data_0200F438->value;
}
