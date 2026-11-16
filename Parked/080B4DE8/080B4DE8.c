#include "ffta.h"

/* func_080B4DE8: complete target [0x080B4DE8, 0x080B4FF8), 528 bytes,
 * 255 instructions. */

typedef struct {
    void *unit;
    u8 unknown_04[4];
    s16 x;
    u8 unknown_0A[2];
    s16 y;
    u8 unknown_0E[0x72];
    void *world;
} MapEntry;

typedef struct {
    s8 x;
    s8 y;
    u8 unknown_02[2];
} MapPoint;

typedef struct {
    void *world;
    MapEntry *items[13];
    u8 status[13];
    u8 unknown_45[0x10];
    s8 selected;
    s8 count;
    u8 reset_selection;
} Selection;

extern MapEntry *func_0809961C(void *world, s8 x, s8 y);
extern u8 func_080B4C90(void *source, void *destination, u16 ability,
                        u16 parameter);
extern u32 func_080CCD50(u16 ability, u8 selector);
extern u8 func_080C8240(void *unit);
extern void func_080B4D70(Selection *selection, s8 x, s8 y);
extern u8 func_08099C10(const MapEntry *entry);

/* An invented helper: the ROM has no out-of-line counterpart and no other
 * expansion of these loops. */
static inline void order_entries(MapEntry **entries, s32 count, u8 opposite)
{
    s32 last = count - 1;
    s32 outer;
    s32 inner;

    for (outer = 0; outer < last; outer++) {
        for (inner = outer + 1; inner < count; inner++) {
            if (func_080C8240(entries[inner]->unit) == opposite) {
                MapEntry *entry = entries[outer];

                entries[outer] = entries[inner];
                entries[inner] = entry;
                break;
            }
        }
    }
}

void func_080B4DE8(void *world, MapEntry *source, Selection *selection,
                   const MapPoint *points, s32 point_count, u16 ability,
                   u16 parameter, u8 selected_x, u8 selected_y)
{
    s32 i;

    selection->count = 0;
    selection->world = world;
    for (i = 0; i < point_count; i++, points++) {
        MapEntry *entry;

        if (selected_x != 0xFF) {
            MapEntry *candidate =
                func_0809961C(source->world, points->x, points->y);

            entry = (candidate != 0 &&
                     func_080B4C90(source->unit, candidate->unit, ability,
                                   parameter)) ? candidate : 0;
        } else {
            entry = func_0809961C(world, points->x, points->y);
        }
        if (entry != 0) {
            if ((entry->x >> 5) == selected_x && (entry->y >> 5) == selected_y)
                selection->selected = selection->count;
            selection->items[selection->count] = entry;
            selection->count++;
        }
    }
    selection->reset_selection = func_080CCD50(ability, 0x10);
    if (ability == 0 || func_080CCD50(ability, 0x10) != 0) {
        s32 source_index;

        order_entries(selection->items, selection->count,
                      !func_080C8240(source->unit));
        for (source_index = 0; source_index < selection->count;
             source_index++) {
            if (selection->items[source_index] == source) {
                selection->items[source_index] =
                    selection->items[selection->count - 1];
                selection->items[selection->count - 1] = source;
                break;
            }
        }
    }
    func_080B4D70(selection, (s8)selected_x, (s8)selected_y);
    for (i = 0; i < selection->count; i++)
        selection->status[i] = func_08099C10(selection->items[i]);
}
