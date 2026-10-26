#include "ffta.h"

extern u32 func_080BC584(void *context, u16 parameter);

/* Complete [0x080BCA40, 0x080BCA52): 18 bytes, 8 instructions. */
u8 func_080BCA40(void *context, u16 parameter)
{
    return func_080BC584(context, parameter);
}
