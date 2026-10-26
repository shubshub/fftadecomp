#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u16 flags;
    u8 unknown_04[8];
    u16 item;
    u8 value;
    u8 unknown_0f[5];
} Entry080846B0;

typedef struct {
    u8 unknown_00[0x18];
    Entry080846B0 *entries;
} Context080846B0;

typedef struct {
    u8 unknown_00[0x16];
    u8 page_size;
    u8 unknown_17;
    u16 count;
    u16 offset;
    u8 unknown_1c[4];
} Menu080846B0;

typedef struct {
    u8 unknown_00[0x11];
    u8 position;
    u8 unknown_12[2];
} Selection080846B0;

typedef struct {
    u8 unknown_00[0x36];
    u8 discard;
    u8 unknown_37;
    u16 item;
    u8 flags;
    u8 unknown_3b[3];
    u16 action;
    u16 value;
    u8 unknown_42[6];
    Context080846B0 *context;
    u8 panel[0x2c];
    Menu080846B0 menu;
    Selection080846B0 selection;
    u8 secondary[0x1c];
    Context080846B0 *other_context;
} Window080846B0;

typedef struct {
    u8 unknown_000[0x42b];
    u8 delay;
    u8 unknown_42c[0x285c];
    Window080846B0 windows[0];
} State080846B0;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} Keys080846B0;

extern State080846B0 *data_03002818;
extern Keys080846B0 data_03000000;
extern u16 func_08017B68(void *, s8);
extern u16 func_08017B50(void *);
extern u8 func_08017A90(void *, u16);
extern void func_08017AF4(void *, s8, u8);
extern void func_08017508(void *, u16);
extern void func_08017D18(void *, u32);
extern void func_08017E28(void *);
extern void func_080845B4(u32, u16, s8, u8);
extern void func_08141540(u16);

#define selection_at(index) \
    ((Selection080846B0 *)((u8 *)data_03002818 + \
                          (index) * sizeof(Window080846B0) + 0x2d20))

/* Complete [0x080846B0, 0x08084A98): 1000 bytes, 406 instructions. */
u8 func_080846B0(u32 index, u16 mask)
{
    u16 pressed;
    u8 old_position;
    u8 next;
    u8 page;
    u16 offset;
    u16 count;

    if (data_03002818->delay) {
        data_03002818->delay--;
        return 6;
    }

    pressed = data_03000000.pressed & mask;
    if (pressed == 4) {
        s8 selected = func_08017B68(&data_03002818->windows[index].menu,
                                   selection_at(index)->position);
        Entry080846B0 *entries = data_03002818->windows[index].context->entries;
        data_03002818->windows[index].item = entries[selected].item;
        if (entries[selected].item)
            return 10;
        func_08141540(106);
    }

    if (pressed == 1) {
        Context080846B0 *context = data_03002818->windows[index].other_context;
        Selection080846B0 *selection = selection_at(index);
        u16 selected = func_08017B68(&data_03002818->windows[index].menu,
                                    selection->position);
        if (context->entries[selected].flags & 1) {
            data_03002818->windows[index].action = 1;
            data_03002818->windows[index].value = context->entries[selected].value;
        } else {
            func_08141540(106);
        }
    }

    if (pressed == 2) {
        data_03002818->windows[index].action = 2;
        data_03002818->windows[index].discard = 0xff;
        func_08017508(data_03002818->windows[index].panel, 16);
        func_08017D18(&data_03002818->windows[index].selection, 0);
        func_08017D18(data_03002818->windows[index].secondary, 0);
        data_03002818->windows[index].flags = 0;
        return 9;
    }

    if (data_03000000.repeated == 0x80) {
        data_03002818->windows[index].action = 0x80;
        old_position = selection_at(index)->position;
        {
            s32 cursor = (s8)selection_at(index)->position;

            next = cursor + 1;
        }
        if (data_03000000.held & 0x200) {
            page = data_03002818->windows[index].menu.page_size;
            offset = data_03002818->windows[index].menu.offset;
            count = data_03002818->windows[index].menu.count;

            if (offset + (u8)data_03002818->windows[index].selection.position < count - 1) {
                if (offset + page < count) {
                    if (offset + page * 2 < count)
                        data_03002818->windows[index].menu.offset = offset + page;
                    else
                        data_03002818->windows[index].menu.offset =
                            offset + page - (offset + page * 2 - count);
                    func_08141540(109);
                    func_08017E28(data_03002818->windows[index].secondary);
                    return 4;
                } else {
                    if (page > count)
                        next = count - 1;
                    else
                        next = page - 1;
                }
            }
        }

        if ((s8)next < func_08017B50(&data_03002818->windows[index].menu)) {
            func_08141540(109);
            func_08017AF4(&data_03002818->windows[index].menu, (s8)old_position, 12);
            func_080845B4(index, 0x80, (s8)next, 0);
        } else if (func_08017A90(&data_03002818->windows[index].menu, 0x80)) {
            func_08141540(109);
            func_08017AF4(&data_03002818->windows[index].menu, (s8)old_position, 12);
            func_080845B4(index, 0x80, (s8)next, 1);
            return 7;
        }
    } else if (data_03000000.repeated == 0x40) {
        data_03002818->windows[index].action = 0x40;
        old_position = selection_at(index)->position;
        next = old_position - 1;
        if (data_03000000.held & 0x200) {
            u8 position;

            page = data_03002818->windows[index].menu.page_size;
            offset = data_03002818->windows[index].menu.offset;
            position = data_03002818->windows[index].selection.position;

            if (offset == 0) {
                if (position)
                    next = 0;
            } else {
                s32 new_offset = offset - page;

                if (new_offset < 0)
                    new_offset = 0;
                data_03002818->windows[index].menu.offset = new_offset;
                func_08141540(109);
                func_08017E28(data_03002818->windows[index].secondary);
                return 4;
            }
        }

        if ((s8)next < 0) {
            if (func_08017A90(&data_03002818->windows[index].menu, 0x40)) {
                func_08141540(109);
                func_08017AF4(&data_03002818->windows[index].menu, (s8)old_position, 12);
                func_080845B4(index, 0x40, (s8)next, 1);
                return 7;
            }
        } else {
            func_08141540(109);
            func_08017AF4(&data_03002818->windows[index].menu, (s8)old_position, 12);
            func_080845B4(index, 0x40, (s8)next, 0);
        }
    }
    return 6;
}
