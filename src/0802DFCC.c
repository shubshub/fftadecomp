#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
} Entry0802DFCC;

typedef struct {
    u8 unknown_00[0x2A4];
    Entry0802DFCC entries[16];
    u8 index;
} State0802DFCC;

Entry0802DFCC *func_0802DFCC(void)
{
    State0802DFCC **state = (State0802DFCC **)0x0200F444;
    Entry0802DFCC *entry = &(*state)->entries[(*state)->index++];

    (*state)->index &= 0x0F;
    return entry;
}
