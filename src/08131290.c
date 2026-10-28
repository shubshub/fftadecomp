#include "ffta.h"

typedef struct {
    u8 unknown_00[0x26];
    u16 flags;
} Object;

extern u8 func_08131220(const Object *object);

/* Complete [0x08131290, 0x081312B0): 32 bytes, 15 instructions. */
u8 func_08131290(const Object *object)
{
    if (!(object->flags & 1))
        return 0;
    return func_08131220(object);
}
