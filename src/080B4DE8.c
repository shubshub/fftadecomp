#include "ffta.h"

/* func_080B4DE8: complete target [0x080B4DE8, 0x080B4FF8), 528 bytes,
 * 255 instructions.
 * Fills the selection with the items standing on a list of points: looked up
 * in source->world and kept only when func_080B4C90 accepts them, or looked up
 * in world unfiltered when selected_x is 0xFF.  The item on (selected_x,
 * selected_y) becomes the selection.  When the ability is 0 or
 * func_080CCD50(ability, 0x10) is non-zero, the items whose func_080C8240 flag
 * differs from the source's are moved to the front and the source is swapped
 * to the end.  Ends with func_080B4D70 on the selected tile and each item's
 * func_08099C10 status. */

typedef struct {
    void *unit;
    u8 unknown_04[4];
    s16 x;
    u8 unknown_0A[2];
    s16 y;
    u8 unknown_0E[0x72];
    void *world;
} Item;

typedef struct {
    s8 x;
    s8 y;
    u8 unknown_02[2];
} MapPoint;

typedef struct {
    void *world;
    Item *items[13];
    u8 status[13];
    u8 directions[16];
    s8 selected;
    s8 count;
    u8 reset_selection;
} Selection;

extern Item *func_0809961C(void *world, s8 x, s8 y);
extern u8 func_080B4C90(void *source, void *destination, u16 ability,
                        u16 parameter);
extern u32 func_080CCD50(u16 ability, u8 selector);
extern u8 func_080C8240(void *unit);
extern void func_080B4D70(Selection *selection, s8 x, s8 y);
extern u8 func_08099C10(const Item *item);

/* Moves to the front of the list the items whose unit gives
 * func_080C8240() == flag.  No out-of-line copy exists in the ROM, but the
 * call's argument binding is there: the count is read at 0x080B4EF2, before
 * the func_080C8240 call that computes the flag, and copied into the loop's
 * register at 0x080B4F0C after it. */
static inline void order_by_flag(Item **items, s32 count, u8 flag)
{
    s32 last = count - 1;
    s32 outer;
    s32 inner;

    for (outer = 0; outer < last; outer++) {
        for (inner = outer + 1; inner < count; inner++) {
            if (func_080C8240(items[inner]->unit) == flag) {
                Item *item = items[outer];

                items[outer] = items[inner];
                items[inner] = item;
                break;
            }
        }
    }
}

void func_080B4DE8(void *world, Item *source, Selection *selection,
                   const MapPoint *points, s32 point_count, u16 ability,
                   u16 parameter, u8 selected_x, u8 selected_y)
{
    s32 i;

    selection->count = 0;
    selection->world = world;
    for (i = 0; i < point_count; i++, points++) {
        Item *entry;

        if (selected_x != 0xFF) {
            Item *candidate =
                func_0809961C(source->world, points->x, points->y);

            if (candidate != 0 &&
                func_080B4C90(source->unit, candidate->unit, ability,
                              parameter))
                entry = candidate;
            else
                entry = 0;
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

        order_by_flag(selection->items, selection->count,
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
    func_080B4D70(selection, selected_x, selected_y);
    for (i = 0; i < selection->count; i++)
        selection->status[i] = func_08099C10(selection->items[i]);
}
