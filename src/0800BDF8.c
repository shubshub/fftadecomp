/* 0x0800BDF8 - 8 bytes - Target: 0022 c180 8280 7047 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u16 field_04;
    u16 field_06;
} Object0800BDF8;

void func_0800BDF8(Object0800BDF8 *object, u16 value)
{
    object->field_06 = value;
    object->field_04 = 0;
}
