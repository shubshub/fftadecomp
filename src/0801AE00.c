#include "ffta.h"

extern u16 data_02007F10;

/* 0x0801AE00 - 16 bytes */
u16 func_0801AE00(void)
{
    return data_02007F10 + 1;
}
