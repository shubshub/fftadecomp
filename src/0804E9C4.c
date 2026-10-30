#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u32 value;
} State0804E9C4;

extern State0804E9C4 *data_0201F548;

/* 0x0804E9C4..0x0804E9D0: 12 bytes, including the global-pointer literal. */
void func_0804E9C4(u32 value)
{
    data_0201F548->value = value;
}
