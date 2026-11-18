#include "ffta.h"

extern u8 data_0200F8A8[];

void func_080A827C(u8 active)
{
    data_0200F8A8[0x10] = active;
}
