#include "ffta.h"

extern u8 *data_020159CC;

/* 08121DF8..08121E08: 02 48 00 68 8A 21 09 01 40 18 70 47 CC 59 01 02. */
u8 *func_08121DF8(void)
{
    return data_020159CC + 0x8A0;
}
