#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1A];
    u8 value;
} State08060E24;

extern State08060E24 *data_0200F44C;

/* 0x08060E24..0x08060E30: 12 bytes, including the global-pointer literal. */
void func_08060E24(u8 value)
{
    data_0200F44C->value = value;
}
