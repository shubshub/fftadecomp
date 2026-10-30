#include "ffta.h"

struct List080823B0 {
    u8 unknown_00[0x16];
    u8 visible;
    u8 unknown_17;
    u16 count;
    u16 scroll;
    u32 unknown_1c;
};

struct Cursor080823B0 {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
};

struct Entry080823B0 {
    u16 unknown_00;
    u16 flags;
    u16 value;
    u8 unknown_06[6];
    u16 action;
    u16 unknown_0e;
    u16 field_10;
    u16 field_12;
};

struct Resource080823B0 {
    u8 unknown_00[0x18];
    struct Entry080823B0 *entries;
};

struct Record080823B0 {
    u8 unknown_00[0x38];
    u16 action;
    u8 unknown_3a[4];
    u16 direction;
    u16 value;
    u16 selected;
    u16 field_44;
    u16 field_46;
    u8 unknown_48[0x30];
    struct List080823B0 list;
    struct Cursor080823B0 cursor;
    u8 animation[0x1c];
    struct Resource080823B0 *resource;
};

struct State080823B0 {
    u8 unknown_0000[0x42a];
    u8 current;
    u8 delay;
    u8 unknown_042c[0x18d8];
    u8 saved;
    u8 unknown_1d05[0xf83];
    struct Record080823B0 records[0];
};

struct Input080823B0 {
    u16 held;
    u16 pressed;
    u16 repeat;
};

extern struct State080823B0 *data_03002818;
extern struct Input080823B0 data_03000000;
extern u16 func_08017B68(struct List080823B0 *list, u32 row);
extern u16 func_08017B50(struct List080823B0 *list);
extern u8 func_08017A90(struct List080823B0 *list, u16 direction);
extern void func_08017E28(void *animation);
extern void func_08080F68(struct List080823B0 *list, s32 row, u32 x, u32 y);
extern void func_08082254(u32 index, u16 direction, s32 row, u32 scroll);
extern void func_08141540(u32 sound);

static inline s8 cursor_row(struct Cursor080823B0 *cursor)
{
    return (s8)cursor->row;
}

/* Complete [0x080823B0, 0x0808286C): 1212 bytes, 487 instructions. */
u32 func_080823B0(u32 index)
{
    u32 keys;
    struct State080823B0 **states = &data_03002818;

    if ((*states)->delay != 0) {
        --(*states)->delay;
        return 6;
    }

    if (data_03000000.pressed == 4) {
        u16 selected = func_08017B68(&(*states)->records[index].list,
                                   cursor_row(&(*states)->records[index].cursor));
        u32 action;
        (*states)->current = (*states)->saved;
        action = (*states)->records[index].resource->entries[selected].action;
        (*states)->records[index].action = action;
        if (action != 0)
            return 10;
        func_08141540(0x6a);
    }

    keys = data_03000000.pressed;
    if (keys == 8)
        goto set_direction;
    if (keys == 1) {
        struct Resource080823B0 *resource = (*states)->records[index].resource;
        u16 selected = func_08017B68(&(*states)->records[index].list,
                                   cursor_row(&(*states)->records[index].cursor));
        if (!(resource->entries[selected].flags & 1)) {
            (*states)->records[index].value = resource->entries[selected].value;
            (*states)->records[index].selected = selected;
            (*states)->records[index].field_44 = resource->entries[selected].field_10;
            (*states)->records[index].field_46 = resource->entries[selected].field_12;
            (*states)->records[index].direction = keys;
        } else {
            func_08141540(0x6a);
        }
        return 6;
    }
    if (keys == 2)
        goto set_direction;
    if (data_03000000.repeat == 0x80) {
        struct State080823B0 *state = *states;
        u8 old;
        u8 next;
        s8 row;

        state = (void *)((u8 *)state + index * sizeof(struct Record080823B0));
        state->records[0].direction = 0x80;
        old = cursor_row(&state->records[0].cursor);
        next = cursor_row(&state->records[0].cursor) + 1;
        if (data_03000000.held & 0x200) {
            u8 visible = state->records[0].list.visible;
            u16 scroll = state->records[0].list.scroll;
            u16 count = state->records[0].list.count;
            if (scroll + (u8)state->records[0].cursor.row < count - 1) {
                if (scroll + visible < count) {
                    if (scroll + visible * 2 < count)
                        state->records[0].list.scroll = scroll + visible;
                    else
                        state->records[0].list.scroll = scroll + visible - (scroll + visible * 2 - count);
                    func_08141540(0x6d);
                    func_08017E28((*states)->records[index].animation);
                    return 4;
                } else {
                    if (visible > count)
                        next = count - 1;
                    else
                        next = visible - 1;
                }
            }
        }
        row = next;
        if (row < func_08017B50(&(*states)->records[index].list)) {
            func_08141540(0x6d);
            func_08080F68(&(*states)->records[index].list, (s8)old, 12, 17);
            func_08082254(index, 0x80, row, 0);
        } else if (func_08017A90(&(*states)->records[index].list, 0x80)) {
            func_08141540(0x6d);
            func_08080F68(&(*states)->records[index].list, (s8)old, 12, 17);
            func_08082254(index, 0x80, row, 1);
            return 7;
        }
    } else if (data_03000000.repeat == 0x40) {
        struct State080823B0 *state = *states;
        u8 old;
        u8 next;
        s8 row;

        state = (void *)((u8 *)state + index * sizeof(struct Record080823B0));
        state->records[0].direction = 0x40;
        old = cursor_row(&state->records[0].cursor);
        next = cursor_row(&state->records[0].cursor) - 1;
        if (data_03000000.held & 0x200) {
            u8 visible = state->records[0].list.visible;
            u16 scroll = state->records[0].list.scroll;
            u8 position = cursor_row(&state->records[0].cursor);
            if (scroll == 0) {
                if (position != 0)
                    next = 0;
            } else {
                s32 target = scroll - visible;
                if (target < 0)
                    target = 0;
                state->records[0].list.scroll = target;
                func_08141540(0x6d);
                func_08017E28((*states)->records[index].animation);
                return 4;
            }
        }
        row = next;
        if (row >= 0) {
            func_08141540(0x6d);
            func_08080F68(&(*states)->records[index].list, (s8)old, 12, 17);
            func_08082254(index, 0x40, row, 0);
        } else if (func_08017A90(&(*states)->records[index].list, 0x40)) {
            func_08141540(0x6d);
            func_08080F68(&(*states)->records[index].list, (s8)old, 12, 17);
            func_08082254(index, 0x40, row, 1);
            return 7;
        }
    } else if (keys == 0x20) {
set_direction:
        (*states)->records[index].direction = keys;
    } else if (keys == 0x10) {
        (*states)->records[index].direction = 0x10;
    } else if (keys == 0x100) {
        (*states)->records[index].direction = 0x100;
    } else if (keys == 0x200) {
        (*states)->records[index].direction = 0x200;
    } else {
        struct Resource080823B0 *resource = (*states)->records[index].resource;
        u16 selected = func_08017B68(&(*states)->records[index].list,
                                   cursor_row(&(*states)->records[index].cursor));
        if (!(resource->entries[selected].flags & 1))
            (*states)->records[index].value = resource->entries[selected].value;
        else
            (*states)->records[index].value = 0;
    }
    return 6;
}
