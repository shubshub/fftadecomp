#include "ffta.h"

extern void func_08005BA8(void *object, u16 value);

/* 0x0802D704..0x0802D714: 16 complete bytes, including the argument literal. */
void func_0802D704(void *object)
{
    func_08005BA8(object, 0x103);
}
