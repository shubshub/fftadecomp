#include "ffta.h"

typedef struct {
    u32 flags;
    u8 unknown_04[8];
    s16 value;
    s16 limit;
} FlaggedRange;

u32 func_08021C5C(const FlaggedRange *object)
{
    if (object->value < object->limit && !(object->flags & 0x100))
        return 0;

    return 1;
}
