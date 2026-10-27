#include "ffta.h"

extern u16 data_03005E42;
extern u8 data_0200F360;

void func_0814195C(void)
{
    u16 *countdown = &data_03005E42;

    if (*countdown != 0) {
        (*countdown)--;
        if (*countdown == 0)
            data_0200F360 = 1;
    }
}
