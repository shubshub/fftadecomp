#include "ffta.h"

typedef struct {
    u8 unknown_00[0xF8];
    u8 value;
} Child08096F8C;

typedef struct {
    Child08096F8C *child;
    u8 unknown_04[4];
    s16 x;
    u8 unknown_0A[2];
    s16 y;
    u8 unknown_0E[0x11];
    u8 value;
} Object08096F8C;

extern void func_08099E68(Object08096F8C *object, s8 x, s8 y);

/* 0x08096F8C..0x08096FAE: 34 bytes, 16 instructions. */
void func_08096F8C(Object08096F8C *object)
{
    func_08099E68(object, object->x >> 5, object->y >> 5);
    object->child->value = object->value;
}
