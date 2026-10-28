#include "ffta.h"

extern u32 func_081444B8(const void *input);

/* Complete [0x0812B59C, 0x0812B5D4): 56 bytes, 27 instructions. */
void func_0812B59C(u8 *text)
{
    u8 length = func_081444B8(text) >> 1;
    u8 index;
    for (index = 0; index < 9 - length; index++) {
        u8 *character = text + (length + index) * 2;
        character[0] = 0x40;
        character[1] = 0x73;
    }
}
