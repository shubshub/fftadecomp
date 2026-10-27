#include "ffta.h"

/* Complete [0x081312B0, 0x081312D0): 32 bytes, 15 instructions. */
typedef struct {
    u8 unknown_00[0x26];
    u16 flags;
} ActionRecord;

extern u32 func_08131220(ActionRecord *record);

u8 func_081312B0(ActionRecord *record)
{
    if (!(record->flags & 2))
        return 0;
    return func_08131220(record);
}
