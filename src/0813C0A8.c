#include "ffta.h"

/* 0x0813C0A8..0x0813C0C4: 28 bytes, 11 instructions. */
extern void *data_0200F3BC;
extern void func_0800718C(void *owner);

void func_0813C0A8(void)
{
    if (data_0200F3BC) {
        func_0800718C(data_0200F3BC);
        data_0200F3BC = 0;
    }
}
