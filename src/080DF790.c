#include "ffta.h"

extern void func_08005BA8(void *object, u16 value);

/* 0x080DF790..0x080DF7A0:
 * 00 B5 02 49 26 F7 08 FA 01 BC 00 47 03 01 00 00. */
void func_080DF790(void *object)
{
    func_08005BA8(object, 0x103);
}
