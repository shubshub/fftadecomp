#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u16 value;
} State080294D8;

extern State080294D8 *data_0200F438;

/* 080294D8..080294E4: 01 48 00 68 00 8A 70 47 38 F4 00 02. */
u16 func_080294D8(void)
{
    return data_0200F438->value;
}
