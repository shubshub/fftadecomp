#include "ffta.h"

/* Target: complete [0x080387F4, 0x08038820), 44 bytes, 18 instructions. */
typedef struct {
    u16 active;
    u8 unknown_02[6];
} StateEntry;

typedef struct {
    u8 unknown_00[0x914];
    StateEntry entries[4];
} State03002810;

extern State03002810 *g_state_03002810;

u32 func_080387F4(void)
{
    u32 count = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_state_03002810->entries[i].active)
            count++;
    }
    return count;
}
