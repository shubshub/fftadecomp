#include "ffta.h"

typedef struct {
    u32 flags;
    u8 unknown_04[8];
    s16 value;
    s16 limit;
} FlaggedRange;

typedef struct {
    u8 unknown_00[0x44];
    FlaggedRange *primary;
    u8 unknown_48[4];
    FlaggedRange *ranges[2];
} RangeOwner;

extern u32 func_08021C5C(const FlaggedRange *object);

/* 0x08099C64..0x08099C9C: 56 bytes. */
u32 func_08099C64(const RangeOwner *owner)
{
    s32 i;

    if (owner->primary && !func_08021C5C(owner->primary))
        return 0;
    for (i = 0; i < 2; i++) {
        if (owner->ranges[i] && !func_08021C5C(owner->ranges[i]))
            return 0;
    }
    return 1;
}
