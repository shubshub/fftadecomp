#include "ffta.h"

/* Complete [0x08137AD0, 0x08137AEC): 28 bytes, 11 instructions. */
extern void *data_0201C3C8;
extern void func_0800718C(void *owner);

void func_08137AD0(void)
{
    if (data_0201C3C8 != 0) {
        func_0800718C(data_0201C3C8);
        data_0201C3C8 = 0;
    }
}
