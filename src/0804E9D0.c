#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u32 value;
} State0804E9D0;

extern State0804E9D0 *data_0201F548;

/* 0x0804E9D0..0x0804E9DC: 01 48 00 68 00 69 70 47 48 F5 01 02. */
u32 func_0804E9D0(void)
{
    return data_0201F548->value;
}
