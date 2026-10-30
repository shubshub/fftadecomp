#include "ffta.h"

extern u8 *data_0201F548;

/* 0804E990..0804E9A0: 02 48 01 68 01 20 08 70 70 47 00 00 48 F5 01 02. */
void func_0804E990(void)
{
    *data_0201F548 = 1;
}
