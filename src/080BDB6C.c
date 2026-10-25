#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    s16 value;
} Struct080BDB6C;

s32 func_080BDB6C(const Struct080BDB6C *object)
{
    return object->value;
}
