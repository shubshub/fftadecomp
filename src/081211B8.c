#include "ffta.h"

typedef struct {
    u16 held;
    u16 pressed;
} InputState;

extern InputState data_03000000;

/* Complete [0x081211B8, 0x0812122C): 116 bytes, 56 instructions. */
u32 func_081211B8(void)
{
    u32 code = 199;

    if (data_03000000.held & 0x40)
        code = 200;
    else if (data_03000000.held & 0x20)
        code = 201;
    else if (data_03000000.held & 0x10)
        code = 202;
    else if (data_03000000.held & 0x80)
        code = 203;
    else if (data_03000000.held & 1)
        code = 204;
    else if (data_03000000.held & 2)
        code = 205;
    else if (data_03000000.held & 0x200)
        code = 206;
    else if (data_03000000.held & 0x100)
        code = 207;
    return code;
}
