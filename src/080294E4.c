#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u32 value;
} State080294E4;

extern State080294E4 *data_0200F438;

/* 080294E4..080294F0: 01 49 09 68 88 61 70 47 38 F4 00 02. */
void func_080294E4(u32 value)
{
    data_0200F438->value = value;
}
