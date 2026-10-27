#include "ffta.h"

/* 0x08133B84..0x08133BB4: 48 bytes. */
extern u8 func_081339CC(u32, s32, u8);
extern void func_080CD884(void *, u16, u8);

void func_08133B84(void *unit, u32 record_index)
{
    int i;

    for (i = 0; i < 44; ++i) {
        if (func_081339CC(record_index, i, 1))
            func_080CD884(unit, i, 0);
    }
}
