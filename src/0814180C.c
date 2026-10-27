#include "ffta.h"

/* 0x0814180C..0x08141838: 44 bytes, 16 instructions. */
typedef struct {
    u32 unknown_00;
    u16 count;
} PlayerState;

extern u8 data_020084D8;
extern PlayerState data_0200F2A0;

u16 func_0814180C(void)
{
    u16 result;

    if (!(data_020084D8 & 1))
        return 0;
    result = data_0200F2A0.count;
    if (result)
        result = 1;
    return result;
}
