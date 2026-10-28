#include "ffta.h"

extern u8 *data_0200F440;

/* 0x0802D714..0x0802D72C: 24 bytes. */
void func_0802D714(void)
{
    data_0200F440[0x391] = 1;
}
