#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u8 slot;
    u8 unknown_03;
    u16 id;
    u16 unknown_06;
    u16 flags;
    s16 x, y;
    u8 unknown_0e[6];
} MovingEntry;

typedef struct {
    u8 unknown_000[0x436];
    s16 marker_x, marker_y;
    u8 unknown_43a[0x16];
    u8 mode;
    u8 unknown_451;
    u8 changed, remaining;
    u8 unknown_454[4];
    s16 offset_x, offset_y;
    u8 unknown_45c[0x500];
    u8 count;
    u8 unknown_95d[0x29];
    u8 selected, selected_unit;
    u8 unknown_988[0xc];
    s16 scroll_y;
    u8 unknown_996[0x24];
    u8 unit_ids[0x32];
    MovingEntry entries[24];
    u8 palettes[24];
    u16 counter;
    u16 unknown_be6;
    s16 position_x, position_y;
    s16 velocity_x, velocity_y;
    s16 target_x, target_y;
} Context;

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2a[0xde];
} Unit;
typedef struct { u32 unknown_00; u8 *entries; } Display;
typedef struct { u8 unknown_00[5]; u8 mode; } Animation;
typedef struct { u8 unknown_00[12]; Animation *animation; } AnimationSlot;
extern Context *data_03002818;
extern Display data_03000E30;
extern AnimationSlot data_03002730;
extern Unit g_state_02000080[];
extern u8 data_0894EAE0[], data_0894EB6C[];
extern void func_0804C7A0(u8 *, u16);
extern void func_0804C524(u8 *, u16, u32, u8, u8, u32, u8, u32, u8 *, u16, s8);
extern void func_080717CC(Unit *, u32, u8);

/* Complete target [0x08071888, 0x08071DC8): 1344 bytes.
 * Array capacities follow the adjacent fields, not a proven caller bound.
 * The final record argument is sign-extended here; its callee stores a byte.
 */
int func_08071888(int all)
{
    int i, id, x, y, tile;
    Unit *unit;
    if (data_03002818->counter > 29)
        return 1;
    if (all) {
        for (i = 0; i < data_03002818->count; i++) {
            id = data_03002818->unit_ids[i];
            data_03002818->entries[i].slot = i;
            data_03002818->entries[i].id = id;
            y = data_03002818->entries[i].y - data_03002818->scroll_y + 44;
            if (data_03002818->entries[i].flags & 1)
                x = data_03002818->entries[i].x - data_03002818->counter * 8;
            else
                x = data_03002818->entries[i].x + data_03002818->counter * 8;
            if (data_03002818->selected == i) {
                unit = &g_state_02000080[data_03002818->unit_ids[i]];
                if ((unsigned)(y - 1) <= 190 && x > 0 && x <= 219)
                    func_0804C788(data_03000E30.entries, 25, x, y);
                else
                    func_0804C7A0(data_03000E30.entries, 25);
                if (unit->flags & 0x1c) {
                    if ((unsigned)(y - 1) <= 190 && x > 0 && x <= 219)
                        func_0804C788(data_03000E30.entries, 24, x, y);
                    else
                        func_0804C7A0(data_03000E30.entries, 24);
                }
            }
            if ((unsigned)(y - 1) <= 190 && x > -16 && x <= 219) {
                int palette;
                if (id <= 7)
                    tile = id * 20 + 128;
                else
                    tile = (id - 8) * 20 + 664;
                palette = data_03002818->palettes[i] + 3;
                func_0804C524(data_03000E30.entries, i, 0, x, y, 0, 1,
                              (u32)data_0894EAE0, data_0894EB6C, tile, palette);
            } else {
                func_0804C7A0(data_03000E30.entries, i);
            }
        }
        data_03002818->counter++;
    } else {
        if (data_03002818->counter == 0) {
            int selected;
            func_080717CC(&g_state_02000080[data_03002818->selected_unit], 0, 3);
            data_03002730.animation->mode = 3;
            selected = data_03002818->selected;
            func_0804C7A0(data_03000E30.entries, selected);
        }
        if (data_03002818->mode == 8 && data_03002818->remaining != 0) {
            data_03002818->remaining--;
            data_03002818->changed = 1;
            data_03002818->offset_x = -(data_03002818->remaining * 8);
            data_03002818->offset_y = 56;
        }
        if (data_03002818->counter <= 28) {
            data_03002818->position_x += data_03002818->velocity_x;
            data_03002818->position_y += data_03002818->velocity_y;
        } else {
            data_03002818->position_x = data_03002818->target_x;
            data_03002818->position_y = data_03002818->target_y;
            data_03002818->offset_x = 0;
            data_03002818->offset_y = 56;
        }
        x = data_03002818->position_x / 8;
        y = data_03002818->position_y / 8;
        data_03002818->marker_x = x;
        data_03002818->marker_y = y;
        func_0804C788(data_03000E30.entries, 25, x, y);
        for (i = 0; i < data_03002818->count; i++) {
            id = data_03002818->unit_ids[i];
            data_03002818->entries[i].slot = i;
            data_03002818->entries[i].id = id;
            if (data_03002818->selected == i)
                continue;
            y = data_03002818->entries[i].y - data_03002818->scroll_y + 44;
            if (data_03002818->entries[i].flags & 1)
                x = data_03002818->entries[i].x - data_03002818->counter * 8;
            else
                x = data_03002818->entries[i].x + data_03002818->counter * 8;
            if ((unsigned)(y - 1) <= 190 && x > -16 && x <= 219) {
                int palette;
                if (id <= 7)
                    tile = id * 20 + 128;
                else
                    tile = (id - 8) * 20 + 664;
                palette = data_03002818->palettes[i] + 3;
                func_0804C524(data_03000E30.entries, i, 0, x, y, 0, 1,
                              (u32)data_0894EAE0, data_0894EB6C, tile, palette);
            } else {
                func_0804C7A0(data_03000E30.entries, i);
            }
        }
        data_03002818->counter++;
    }
    return 0;
}
