#include "ffta.h"

typedef struct {
    u8 active;
    u8 unknown_01;
    u16 value;
} Entry08050C74;

extern Entry08050C74 g_state_02002B08[64];

/* Complete [0x08050C74, 0x08050CA4): 48 bytes, 22 instructions. */
s32 func_08050C74(Entry08050C74 **output)
{
    Entry08050C74 *entry = g_state_02002B08;
    s32 count = 0;
    s32 remaining;

    for (remaining = 63; remaining >= 0; remaining--, entry++) {
        if (entry->active) {
            if (output)
                output[count] = entry;
            count++;
        }
    }
    return count;
}
