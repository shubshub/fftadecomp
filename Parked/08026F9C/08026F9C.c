#include "ffta.h"

struct Resource08026F9C {
    u16 name;
    u16 unknown_02;
    u8 cost;
    u8 unknown_05[23];
};

struct ListEntry08026F9C {
    u32 unknown_00;
    u16 id;
    u8 kind;
    u8 unknown_07;
};

struct List08026F9C {
    struct ListEntry08026F9C *entries;
    u8 first;
    u8 last;
    u8 unknown_06;
    u8 width;
    u8 cost_category;
    u8 count;
};

struct Status08026F9C {
    u8 unknown_00[13];
    u8 mode;
    u8 unknown_0e[6];
};

struct Menu08026F9C {
    u8 unknown_00[0x80];
    struct Status08026F9C status;
    s32 *indices;
    u8 *enabled;
};

struct Unit08026F9C {
    u8 unknown_00[0x1c];
    u16 points;
};

struct Battle08026F9C {
    u8 unknown_00[0x18];
    struct Unit08026F9C *unit;
};

extern struct Battle08026F9C *data_0200F438;
extern const struct Resource08026F9C data_0855187C[];
extern const void *g_table_085567F0[];
extern u32 func_080CD560(struct Unit08026F9C *, u32);
extern u32 func_080CCD50(u32, u32);
extern u32 func_080CDB3C(struct Unit08026F9C *);
extern u32 func_080161BC(const void *);

/* Target: [0x08026F9C, 0x080270CC), 304 bytes, 138 instructions. */
void func_08026F9C(struct Menu08026F9C *menu, struct List08026F9C *list)
{
    struct Status08026F9C *status = &menu->status;
    s32 index;
    s32 count;

    list->cost_category = 0;
    index = list->first;
    count = 0;
    for (; index <= list->last; index++) {
        struct ListEntry08026F9C *entry = &list->entries[index];

        if ((entry->kind == 1 || entry->kind == 4) &&
            (u8)func_080CD560(data_0200F438->unit, (u8)index) &&
            func_080CCD50(entry->id, 0x15)) {
            const struct Resource08026F9C *resource = &data_0855187C[entry->id];
            u8 width;

            menu->indices[count] = index;
            if ((u8)func_080CDB3C(data_0200F438->unit) &&
                !func_080CCD50(entry->id, 0x14)) {
                if (resource->cost) {
                    u32 cost = resource->cost;

                    if (list->cost_category < 3)
                        list->cost_category = 3;
                    if (cost > 99)
                        list->cost_category = 4;
                }
                menu->enabled[count] = 0;
            } else {
                if (resource->cost) {
                    u32 cost = resource->cost;

                    if (list->cost_category < 3)
                        list->cost_category = 3;
                    if (cost > 99)
                        list->cost_category = 4;
                    if (data_0200F438->unit->points < cost)
                        menu->enabled[count] = 0;
                }
            }
            count++;
            width = func_080161BC(g_table_085567F0[resource->name]);
            if (width > list->width)
                list->width = width;
        }
    }
    if (list->cost_category)
        status->mode = 9;
    list->count = count;
}
