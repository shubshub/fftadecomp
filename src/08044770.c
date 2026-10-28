#include "ffta.h"

struct MenuEntry08044770 {
    u16 active : 1;
    u16 pending : 1;
    u16 changed : 1;
    u16 mode : 3;
    u16 type : 4;
    u16 unknown_0a : 3;
    u16 option : 1;
    u16 unknown_0e : 2;
    u8 unknown_02[0x32];
};

struct MenuContext08044770 {
    u8 unknown_000[0x7b8];
    struct MenuEntry08044770 entries[8];
};

extern struct MenuContext08044770 *g_state_03002810;

/* Target: [0x08044770, 0x080447B4), 68 bytes, 30 instructions. */
void func_08044770(void)
{
    int i;

    for (i = 0; i <= 4; i++) {
        if (g_state_03002810->entries[i + 1].active)
            g_state_03002810->entries[i + 1].option = 0;
    }
}
