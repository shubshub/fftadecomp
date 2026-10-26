#include "ffta.h"

typedef struct {
    u8 active;
    u8 unknown_01[3];
} Entry08067EE4;

extern Entry08067EE4 g_state_02002B08[];

/* 0x08067EE4..0x08067F14: 48 bytes, 22 instructions. */
s32 func_08067EE4(Entry08067EE4 **output)
{
    Entry08067EE4 *entry = g_state_02002B08;
    s32 count = 0;
    s32 remaining = 63;
    Entry08067EE4 **next = output;

    do {
        if (entry->active) {
            if (output)
                *next = entry;
            next++;
            count++;
        }
        remaining--;
        entry++;
    } while (remaining >= 0);
    return count;
}
