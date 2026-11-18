#include "ffta.h"

/* 0x080A97EC..0x080A9940, 328 code bytes and three literal words:
 * 0x08394560, 0xFFFFF000, 0xFFFFF000. The fixed origin uses the
 * projected X and zero Y. The caller supplies an available entry. */

typedef struct {
    s32 x;
    s32 y;
    s32 origin_x;
    s32 origin_y;
    s32 unknown_10;
    s32 unknown_14;
    s32 unknown_18;
    const void *script;
    s16 unknown_20;
    s16 unknown_22;
    u8 unknown_24[3];
    u8 active;
} Entry080A97EC;

extern const u8 data_08394560[];
extern void func_0801C984(s16 first, s16 second, s16 third,
                         s16 *first_output, s16 *second_output);
extern u32 func_08002804(void);

static inline Entry080A97EC *find_free_entry(Entry080A97EC *entries,
                                             s32 count)
{
    s32 i;

    for (i = 0; i < count; i++, entries++) {
        if (entries->script == 0)
            return entries;
    }
    return 0;
}

Entry080A97EC *func_080A97EC(Entry080A97EC *entries, s32 count,
                             s16 x, s16 y, s16 z, u8 fixed_origin)
{
    s16 screen_x;
    s16 screen_y;
    Entry080A97EC *entry;
    s16 side;

    func_0801C984(x, y, z, &screen_x, &screen_y);
    entry = find_free_entry(entries, count);
    entry->x = screen_x << 8;
    entry->y = screen_y << 8;
    entry->unknown_10 = 0;
    entry->unknown_14 = 100;
    if (fixed_origin)
        entry->unknown_18 = 0x800;
    else
        entry->unknown_18 = (((s16)func_08002804() % 3) << 8) + 0x500;
    entry->script = data_08394560;
    entry->unknown_20 = 0x80;
    entry->unknown_22 = 0x100;
    entries->active = 1;

    if (fixed_origin) {
        entry->origin_x = entry->x;
        entry->origin_y = 0;
    } else {
        side = (s16)func_08002804() % 4;
        switch (side) {
        case 0:
            entry->origin_x = 0x10000;
            entry->origin_y = ((s16)func_08002804() % 0xA1) << 8;
            break;
        case 1:
            entry->origin_x = -0x1000;
            entry->origin_y = ((s16)func_08002804() % 0xA1) << 8;
            break;
        case 2:
            entry->origin_x = ((s16)func_08002804() % 0xF1) << 8;
            entry->origin_y = 0xB000;
            break;
        case 3:
            entry->origin_x = ((s16)func_08002804() % 0xF1) << 8;
            entry->origin_y = -0x1000;
            break;
        }
    }
    return entry;
}
