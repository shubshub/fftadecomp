#include "ffta.h"

typedef struct {
    u16 id;
    u16 kind;
    u16 quantity;
    u16 unknown_06;
} MenuEntry;

typedef struct {
    u8 unknown_000[0x913];
    u8 count;
    MenuEntry entries[16];
} MenuState;

extern MenuState *g_state_03002810;

/* Complete target: 0x08038858..0x080388C8, 112 bytes. */
s32 func_08038858(u16 id, u8 kind, u16 quantity)
{
    s32 i;

    g_state_03002810->count = 0;
    for (i = 0; i < 16; i++)
    {
        if (!g_state_03002810->entries[i].id)
        {
            g_state_03002810->entries[i].id = id;
            g_state_03002810->entries[i].kind = kind;
            g_state_03002810->entries[i].quantity = quantity;
            g_state_03002810->count++;
            return i;
        }
    }
    return -1;
}
