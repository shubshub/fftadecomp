#include "ffta.h"

extern u16 (*data_0200F37C)(u16 index);
extern void func_080033C8(u32 delay);

/* 0x0813BC30: 76 bytes; retry each nonzero callback result twice. */
void func_0813BC30(void)
{
    int i;

    for (i = 0; i < 16; i++) {
        u16 index = i;

        if (data_0200F37C(index)) {
            func_080033C8(10);
            if (data_0200F37C(index)) {
                func_080033C8(10);
                data_0200F37C(index);
            }
        }
    }
}
