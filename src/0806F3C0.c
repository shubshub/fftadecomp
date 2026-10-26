#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u8 value;
} Object0806F3C0;

/* 0x0806F3C0..0x0806F3C4: 4 bytes, 2 instructions. */
void func_0806F3C0(Object0806F3C0 *object, u8 value)
{
    object->value = value;
}
