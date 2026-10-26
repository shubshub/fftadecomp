#include "ffta.h"

extern void func_0809A570(void *object, u32 clear, u32 set);

void func_080DE3BC(void *object, u8 enabled)
{
    if (enabled)
        func_0809A570(object, 0, 0x100);
    else
        func_0809A570(object, 0x100, 0);
}
