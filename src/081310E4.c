#include "ffta.h"

typedef struct {
    u8 unknown_00[0x26];
    u16 flags;
} Object;

/* Complete [0x081310E4, 0x081310FA): 22 bytes, 11 instructions. */
s32 func_081310E4(const Object *object)
{
    if (!(object->flags & 2))
        return 0;
    return 100;
}
