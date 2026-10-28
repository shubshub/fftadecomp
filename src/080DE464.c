#include "ffta.h"

/* 0x080DE464..0x080DE486: 34 bytes. */
extern void func_0809A570(int index, u32 clear_mask, u32 set_mask);

void func_080DE464(int index, u8 enabled)
{
    if (enabled)
        func_0809A570(index, 0, 0x1000);
    else
        func_0809A570(index, 0x1000, 0);
}
