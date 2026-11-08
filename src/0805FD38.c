#include "ffta.h"

typedef struct {
    u8 low;
    u8 high;
    u16 flag;
} Entry0805FD38;

typedef struct {
    const u8 *text;
} Text0805FD38;

typedef union {
    const Entry0805FD38 *entry;
    const Text0805FD38 *text;
} MenuEntry0805FD38;

typedef struct Context0805FD38 {
    u8 unknown_00[0x1B];
    u8 base;
    u8 unknown_1c[4];
    MenuEntry0805FD38 entries[1];
} Context0805FD38;

extern Context0805FD38 *data_0200F44C;
extern const u8 *const g_table_08526680[];
extern const u8 *const g_table_085567F0[];
extern const u8 *const g_table_0855A64C[];
extern const u8 *const data_08557E98[];

/* Complete [0x0805FD38, 0x0805FEA6): 366 bytes, 135 instructions. */
const u8 *func_0805FD38(u8 *kind, u16 index, u8 *flag)
{
    switch (*kind) {
    case 1:
        return g_table_085567F0[(s16)index + 41];
    case 2: {
        const Entry0805FD38 *entry = data_0200F44C->entries[(s16)index].entry;
        return data_08557E98[entry->low];
    }
    /* The packed u16 identifier : 10 bitfield form (as in src/0805064C.c) was tried here;
       it changes the load order, so the index is rebuilt from the two bytes. */
    case 3: {
        const Entry0805FD38 *entry = data_0200F44C->entries[(s16)index].entry;
        const u8 *const *table = g_table_0855A64C;
        u32 low = entry->low;
        u32 high = entry->high;

        return table[((high & 3) << 8) | low];
    }
    case 7: {
        const Entry0805FD38 *entry = data_0200F44C->entries[(s16)index].entry;
        const u8 *const *table = g_table_0855A64C;
        u32 low = entry->low;
        u32 high = entry->high;

        return table[((high & 3) << 8) | low];
    }
    case 4:
        return data_0200F44C->entries[(s16)index].text->text;
    case 5:
        if ((s16)index < 2) {
            s32 slot = (s16)index - 2;
            const Entry0805FD38 *entry = data_0200F44C->entries[slot + data_0200F44C->base].entry;
            if (entry == 0 || entry->low == 0) {
                *flag = 1;
                return g_table_085567F0[0x40];
            } else {
                u16 id = 0x1F2 + entry->low;
                return g_table_08526680[id];
            }
        } else {
            return g_table_085567F0[0x43];
        }
    case 6: {
        const Entry0805FD38 *entry = data_0200F44C->entries[(s16)index].entry;
        u16 id = 0x1F2 + entry->low;
        if (entry->flag != 0)
            *flag = 1;
        return g_table_08526680[id];
    }
    }
    return 0;
}
