#include "ffta.h"

typedef struct {
    u8 x;
    u8 y;
    u8 first0, second0;
    u8 unknown_04[2];
    u8 first1, second1;
    u8 unknown_08[2];
    u8 first2, second2;
    u8 unknown_0C[2];
    u8 first3, second3;
    u8 unknown_10[4];
} LinkRecord;

typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 unknown_02;
    u8 record;
    u8 unknown_04[4];
    u8 unknown_08;
    u8 unknown_09;
    u8 unknown_0A;
    u8 unknown_0B;
} MapEntry;

typedef struct {
    u8 unknown_000[0xB0];
    MapEntry entries[1];
} EntryMap;

typedef struct {
    EntryMap *map;
    u8 unknown_004[0x678];
    LinkRecord *records;
} LinkState;

extern LinkState *g_state_03002810;
extern const u8 data_08391CA4[];
extern u8 func_080363C0(u8 identifier, const u8 *map);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u32 func_08002804(void);
extern u8 func_0803A7EC(u8 *index, const u8 *values);
extern u8 func_0803A838(u8 *index, const u8 *values);
extern u8 func_0803A8C0(u8 *index, const u8 *values);
extern u8 func_0803A920(u8 *index, const u8 *values);

/* Complete owner: 0x0803A958..0x0803AD08, 944 bytes, 472 instructions. */
u8 func_0803A958(u32 entry, s32 depth)
{
    u8 indices[4];
    u8 values[4];
    s32 count = 0;
    u8 record;
    u32 found;
    u8 value;
    u16 clear_indices = 0;
    u16 clear_values;
    u8 index;

    /* The neighbours are collected as func_0803AD08 (src/0803AD08.c) does. */
    func_0814186C(&clear_indices, indices, 0x01000002);
    clear_values = 0;
    func_0814186C(&clear_values, values, 0x01000002);
    record = g_state_03002810->map->entries[entry].record - 1;

    value = g_state_03002810->records[record].second0;
    if (value || g_state_03002810->records[record].first0) {
        found = func_080363C0(value + 1,
                             (const u8 *)g_state_03002810->map);
        if (found) {
            indices[count] = found - 1;
            values[count] = data_08391CA4[(found - 1) * 4];
            count++;
        }
    }
    value = g_state_03002810->records[record].second1;
    if (value || g_state_03002810->records[record].first1) {
        found = func_080363C0(value + 1,
                             (const u8 *)g_state_03002810->map);
        if (found) {
            indices[count] = found - 1;
            values[count] = data_08391CA4[(found - 1) * 4];
            count++;
        }
    }
    value = g_state_03002810->records[record].second2;
    if (value || g_state_03002810->records[record].first2) {
        found = func_080363C0(value + 1,
                             (const u8 *)g_state_03002810->map);
        if (found) {
            indices[count] = found - 1;
            values[count] = data_08391CA4[(found - 1) * 4];
            count++;
        }
    }
    value = g_state_03002810->records[record].second3;
    if (value || g_state_03002810->records[record].first3) {
        found = func_080363C0(value + 1,
                             (const u8 *)g_state_03002810->map);
        if (found) {
            indices[count] = found - 1;
            values[count] = data_08391CA4[(found - 1) * 4];
            count++;
        }
    }

    value = 0;
    if (count != 0) {
        switch (count) {
        case 4:
            /* A zero byte is never 0xFF, but the ROM keeps both 0xFF
               compares (0x0803AB0E, 0x0803AB1A) ahead of the or-test
               (0x0803AB1E). */
            if (g_state_03002810->map->entries[entry].unknown_08 != 0xFF &&
                g_state_03002810->map->entries[entry].unknown_0B != 0xFF) {
                if (!(g_state_03002810->map->entries[entry].unknown_08 |
                      g_state_03002810->map->entries[entry].unknown_0B)) {
                    value = func_0803A7EC(&index, values);
                    if (value) {
                        g_state_03002810->map->entries[entry].unknown_0B = index + 1;
                    } else {
                        value = func_0803A838(&index, values);
                        if (value == 1) {
                            g_state_03002810->map->entries[entry].unknown_08 = index + 1;
                        } else {
                            value = 1;
                            g_state_03002810->map->entries[entry].unknown_08 =
                                (s16)func_08002804() % 21 - 127;
                        }
                    }
                }
            }
            if (depth > 0) {
                depth--;
                func_0803A958(indices[0], depth);
                func_0803A958(indices[1], depth);
                func_0803A958(indices[2], depth);
                func_0803A958(indices[3], depth);
            }
            break;
        case 3:
            /* A zero byte is never 0xFF, but the ROM keeps both compares
               (cmp #0xff at 0x0803ABCE, cmp #0 at 0x0803ABD2). */
            if (g_state_03002810->map->entries[entry].unknown_09 != 0xFF) {
                if (g_state_03002810->map->entries[entry].unknown_09 == 0) {
                    value = func_0803A8C0(&index, values);
                    if (value == 2) {
                        g_state_03002810->map->entries[entry].unknown_09 = index + 1;
                    } else {
                        value = 1;
                        g_state_03002810->map->entries[entry].unknown_09 =
                            (s16)func_08002804() % 21 - 127;
                    }
                }
            }
            if (depth > 0) {
                depth--;
                func_0803A958(indices[0], depth);
                func_0803A958(indices[1], depth);
                func_0803A958(indices[2], depth);
            }
            break;
        case 2:
            /* A zero byte is never 0xFF, but the ROM keeps both compares
               (cmp #0xff at 0x0803AC52, cmp #0 at 0x0803AC56). */
            if (g_state_03002810->map->entries[entry].unknown_0A != 0xFF) {
                if (g_state_03002810->map->entries[entry].unknown_0A == 0) {
                    value = func_0803A920(&index, values);
                    if (value) {
                        g_state_03002810->map->entries[entry].unknown_0A = index + 1;
                    } else {
                        value = 1;
                        g_state_03002810->map->entries[entry].unknown_0A =
                            (s16)func_08002804() % 21 - 127;
                    }
                }
            }
            if (depth > 0) {
                depth--;
                func_0803A958(indices[0], depth);
                func_0803A958(indices[1], depth);
            }
            break;
        case 1:
            if (depth > 0) {
                depth--;
                func_0803A958(indices[0], depth);
            }
            break;
        }
        if (value)
            g_state_03002810->map->entries[entry].flags |= 0x14;
    }
    return value;
}
