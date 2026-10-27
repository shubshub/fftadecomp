#include "ffta.h"

/* 0x08011CC4 - 12 bytes. Set the current state's halfword at offset 0x22. */
typedef struct {
    u8 unknown_00[0x22];
    u16 value;
} State08011CC4;

extern State08011CC4 *data_0200918C;

void func_08011CC4(u16 value)
{
    data_0200918C->value = value;
}
