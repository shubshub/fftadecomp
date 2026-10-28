#include "ffta.h"

struct Position08021D0C {
    u8 unknown_00[0x30];
    u16 x;
    u16 y;
};

void func_08021D0C(struct Position08021D0C *object, u16 x, u16 y)
{
    object->x = x;
    object->y = y;
}
