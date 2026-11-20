#include "ffta.h"

typedef struct {
    u8 status;
    u8 entries[6];
    u8 count;
    u8 field_08;
    u8 field_09;
    u8 unknown_0a[2];
    const void *resource;
    u8 unknown_10[0x68];
    u8 x;
    u8 y;
} DisplayState;

struct ItemInfo {
    u8 unknown_00[0xC];
    u8 flags;
    u8 unknown_0D[0x13];
};

typedef struct {
    u8 unknown_0000[0x1F6C];
    u16 selection;
} ShopState;

extern ShopState g_state_02000000;
extern const struct ItemInfo g_table_0851D180[];
extern const u8 data_08393B40[6];
extern u8 func_080CC8B4(u16 level);
extern u8 func_080CBD34(u16 id);
extern u16 func_080CC9F0(u8 table, u8 index);
extern u8 func_080CECF4(void);

/* 0806ED30..0806EE98, 360 bytes. */
void func_0806ED30(DisplayState *state, u8 table)
{
    u8 present[6];
    u8 mask;
    u8 rank = func_080CC8B4(g_state_02000000.selection);
    u8 has_special;
    u16 first, length;
    u16 i;

    mask = 0x10;
    if (rank == 1)
        mask = 0x20;
    else if (rank > 1)
        mask = 0x40;

    state->count = 0;
    has_special = 0;
    for (i = 0; i < 6; i++)
        present[i] = 0;

    first = 1;
    length = 361;
    for (i = first; i < length + first; i++) {
        if (g_table_0851D180[i].flags & mask)
            present[func_080CBD34(i)] = 1;
    }

    for (i = 0; i <= func_080CECF4(); i++) {
        u16 item = func_080CC9F0(table, i);
        if (item != 0) {
            if (func_080CBD34(item) == 5)
                has_special = 1;
            present[func_080CBD34(item)] = 1;
        }
    }

    for (i = 0; i < 6; i++) {
        if (present[i] == 1) {
            state->entries[state->count] = data_08393B40[i];
            state->count++;
        }
    }

    if (!has_special) {
        first = 362;
        length = 14;
        for (i = first; i < length + first; i++) {
            if (g_table_0851D180[i].flags & mask) {
                state->entries[state->count] = 5;
                state->count++;
                break;
            }
        }
    }
}
