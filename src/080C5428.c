#include "ffta.h"

/* 0x080C5428..0x080C5432: 10 bytes, 5 Thumb instructions. */
typedef struct {
    u8 unknown_00[0x18];
    u8 x;
    u8 y;
} PositionedObject;

void func_080C5428(const PositionedObject *object, u8 *x, u8 *y)
{
    *x = object->x;
    *y = object->y;
}
