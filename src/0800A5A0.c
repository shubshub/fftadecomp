#include "ffta.h"

void *func_08096D7C(void);
u8 func_0809A77C(void *object);

void func_0800A5A0(u16 *context, const u8 *instruction)
{
    if (func_0809A77C(func_08096D7C()) == 0)
        context[1] += instruction[1] | (instruction[2] << 8);
}
