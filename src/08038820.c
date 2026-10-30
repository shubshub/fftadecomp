#include "ffta.h"

typedef struct {
    u16 active;
    u8 unknown_02[6];
} StateEntry;

typedef struct {
    u8 unknown_00[0x913];
    u8 count;
    StateEntry entries[16];
} State03002810;

extern State03002810 *g_state_03002810;

/* Target: complete [0x08038820, 0x08038858), 56 bytes, 21 instructions. */
void func_08038820(void)
{
    s32 i;

    g_state_03002810->count = 0;
    for (i = 0; i < 16; i++)
        g_state_03002810->entries[i].active = 0;
}
