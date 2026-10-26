#include "ffta.h"

/* 0x0809F9D0..0x0809F9D8: 8 bytes. */
typedef struct {
    u8 unknown_00[0x28];
    u32 value;
} ClearState;

void func_0809F9D0(ClearState **state)
{
    (*state)->value = 0;
}
