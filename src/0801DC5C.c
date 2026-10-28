#include "ffta.h"

typedef struct {
    u8 unknown_00[0x12];
    u16 value;
} SelectionState;

extern SelectionState data_02007F10;
extern u8 data_02008390[];

/* 0801DC5C..0801DC7A: 30 bytes. */
u8 *func_0801DC5C(void)
{
    if (data_02007F10.value == 0xFF)
        return 0;
    return data_02008390;
}
