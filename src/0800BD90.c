/* 0x0800BD90 - 18 bytes - Target: 00b5 011c 4878 0228 01d1 0020 4870 01bc 0047 */
#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 field_01;
} Object0800BD90;

void func_0800BD90(Object0800BD90 *object)
{
    if (object->field_01 == 2)
        object->field_01 = 0;
}
