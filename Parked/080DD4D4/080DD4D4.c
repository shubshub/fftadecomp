/* 0x080DD4D4 target: 10b5021c9489012020400a49002800d0d18b080403140748834205d102202040191c002800d0118c0804001410bc02bc08470000ff7f0000 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 flags;
    u8 unknown_0e[0x10];
    s16 value_1e;
    s16 value_20;
} Object080DD4D4;

s16 func_080DD4D4(const Object080DD4D4 *object)
{
    s16 value = 0x7FFF;

    if (object->flags & 1)
        value = object->value_1e;
    if (value == 0x7FFF && (object->flags & 2))
        value = object->value_20;
    return value;
}
