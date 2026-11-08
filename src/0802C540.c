#include "ffta.h"

extern u32 func_08142AB0(u32, u32);
extern u32 func_08142B28(u32, u32);

/* Target 0802C540..0802C5C8: 136 bytes including literal pools. */
void func_0802C540(u16 *buffer, u16 value, u16 offset, u8 special_zero)
{
    u32 digit;
    u16 *output = buffer + offset;

    if (value > 999)
        value = 999;

    if (value == 0 && special_zero != 0) {
        output[0] = 0;
        output[1] = 0;
        output[2] = 0xE0D6;
    } else {
        digit = (u16)func_08142AB0(value, 100);
        if (digit != 0)
            digit += 0xD01E;
        output[0] = digit;

        digit = (u16)func_08142AB0(value, 10);
        digit = (u16)func_08142B28(digit, 10);
        if (value > 99 || digit != 0)
            digit += 0xD01E;
        output[1] = digit;
        output[2] = func_08142B28(value, 10) + 0xD01E;
    }
}
