#include "ffta.h"

typedef struct {
    u8 unknown_00[0x30];
    u32 flags;
} Struct080DD71C;

u32 func_080DD71C(const Struct080DD71C *object)
{
    return object->flags;
}
