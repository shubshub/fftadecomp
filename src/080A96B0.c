#include "ffta.h"

// Complete 080A96B0..080A97EC: 316 bytes, 140 instructions, including the
// literal words 0x08394560 and 0xFFFFF000.
//
// Picks the first free 0x28-byte entry (word 0x1C clear), projects the
// signed coordinates through 0801C984 and seeds the entry's position,
// velocity and timing words from func_08002804 draws.  The entry, the
// flag byte at +0x27 of the array base and the random edge choice follow
// the immediate offsets; the field names are local views.

typedef struct {
    s32 velocity_x;
    s32 velocity_y;
    s32 x;
    s32 y;
    s32 unknown_10;
    s32 unknown_14;
    s32 unknown_18;
    const void *script;
    s16 unknown_20;
    s16 unknown_22;
    u8 unknown_24[3];
    u8 active;
} Entry080A96B0;

extern const u8 data_08394560[];
extern void func_0801C984(s16 first, s16 second, s16 third,
                         s16 *first_output, s16 *second_output);
extern s16 func_08002804(void);

static inline Entry080A96B0 *find_free_entry(Entry080A96B0 *entries,
                                             s32 count)
{
    s32 i;

    for (i = 0; i < count; i++, entries++) {
        if (entries->script == 0)
            return entries;
    }
    return 0;
}

Entry080A96B0 *func_080A96B0(Entry080A96B0 *entries, s32 count,
                             s16 x, s16 y, s16 z)
{
    s16 screen_x;
    s16 screen_y;
    Entry080A96B0 *entry;
    s16 side;

    func_0801C984(x, y, z, &screen_x, &screen_y);
    entry = find_free_entry(entries, count);
    entry->x = screen_x << 8;
    entry->y = screen_y << 8;
    entry->unknown_10 = 0;
    entry->unknown_14 = 100;
    entry->unknown_18 = ((func_08002804() % 3) << 8) + 0x500;
    entry->script = data_08394560;
    entry->unknown_20 = 0x100;
    entry->unknown_22 = 0x200;
    entries->active = 1;

    side = func_08002804() % 4;
    switch (side) {
    case 0:
        entry->velocity_x = 0x10000;
        entry->velocity_y = (func_08002804() % 0xA1) << 8;
        break;
    case 1:
        entry->velocity_x = -0x1000;
        entry->velocity_y = (func_08002804() % 0xA1) << 8;
        break;
    case 2:
        entry->velocity_x = (func_08002804() % 0xF1) << 8;
        entry->velocity_y = 0xB000;
        break;
    case 3:
        entry->velocity_x = (func_08002804() % 0xF1) << 8;
        entry->velocity_y = -0x1000;
        break;
    }
    return entry;
}
