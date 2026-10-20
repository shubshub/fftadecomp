#include "ffta.h"

u8 func_081339A8(u32 recordIndex, s32 bitIndex, u8 second);
void func_080CD884(void *data, u16 index, u8 enabled);

void func_08131C28(u32 selector, void *object)
{
    s32 index;

    for (index = 0; index < 44; index++) {
        if (func_081339A8(selector, index, 1))
            func_080CD884(object, index, 0);
    }
}
