#include "ffta.h"

/* Complete [0x081310CC, 0x081310E2): 22 bytes, 11 instructions. */
typedef struct {
    u8 unknown_00[0x26];
    u16 flags;
} FlagRecord;

u32 func_081310CC(const FlagRecord *record)
{
    if (!(record->flags & 1))
        return 0;
    return 100;
}
