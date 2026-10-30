#include "ffta.h"

typedef struct {
    u8 unknown_00[0x12];
    u16 value;
} State080294F0;

extern State080294F0 *data_0200F438;

/* 080294F0..080294FC: 01 49 09 68 48 82 70 47 38 F4 00 02. */
void func_080294F0(u16 value)
{
    data_0200F438->value = value;
}
