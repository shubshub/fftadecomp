#include "ffta.h"

typedef struct Entry0804D814 {
    u8 active;
    u8 unknown_01;
    u16 value;
} Entry0804D814;

extern Entry0804D814 g_state_02002B08[64];

/* Complete [0x0804D814, 0x0804D83E): 42 bytes, 18 instructions. */
u32 func_0804D814(void)
{
    Entry0804D814 *entry = g_state_02002B08;
    s32 index;

    for (index = 0; index < 64; index++, entry++) {
        if (entry->active != 0 && entry->value == 0)
            return 1;
    }
    return 0;
}
