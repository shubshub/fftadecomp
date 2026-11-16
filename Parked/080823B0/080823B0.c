#include "ffta.h"

// Complete [0x080823B0, 0x0808286C): 1212 bytes, 487 instructions.
typedef struct {
    u16 id;
    u16 flags;
    u16 selected_id;
    u8 unknown_06[6];
    u16 value;
    u8 unknown_0E[2];
    u16 field_10;
    u16 field_12;
} MenuEntry;

typedef struct {
    u8 unknown_00[0x18];
    MenuEntry *entries;
} EntryTable;

typedef struct {
    u8 unknown_00[0x16];
    u8 visible;
    u8 unknown_17;
    u16 count;
    u16 scroll;
    u32 unknown_1C;
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    s8 row;
    u8 unknown_12[2];
} MenuCursor;

typedef struct {
    u8 unknown_00[0x38];
    u16 value;
    u8 unknown_3A[4];
    u16 action;
    u16 selected_id;
    u16 selected;
    u16 field_44;
    u16 field_46;
    EntryTable *primary;
    u8 unknown_4C[0x2C];
    MenuList list;
    MenuCursor cursor;
    u8 animation[0x1C];
    EntryTable *secondary;
} MenuRecord;

typedef struct {
    u8 unknown_0000[0x42A];
    u8 current;
    u8 delay;
    u8 unknown_042C[0x18D8];
    u8 saved;
    u8 unknown_1D05[0xF83];
    MenuRecord records[0];
} MenuState;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState;

extern InputState data_03000000;
extern MenuState *data_03002818;
extern u16 func_08017B68(MenuList *list, u32 row);
extern u16 func_08017B50(MenuList *list);
extern u8 func_08017A90(MenuList *list, u16 direction);
extern void func_08017E28(void *animation);
extern void func_08080F68(MenuList *list, s32 row, u32 x, u32 y);
extern void func_08082254(u32 index, u8 direction, s8 row, u8 refresh);
extern void func_08141540(u16 song_id);

// The target forms the cursor's address (record + 0x98) and loads row from
// it at +0x11, as the neighbouring func_08081DEC does.
#define RECORD_CURSOR(index) (&data_03002818->records[index].cursor)

static inline s8 cursor_row(MenuCursor *cursor)
{
    return cursor->row;
}

s32 func_080823B0(u32 index)
{
    s8 old;
    u8 next;
    s8 row;

    if (data_03002818->delay != 0) {
        data_03002818->delay--;
        return 6;
    }
    if (data_03000000.pressed == 4) {
        u16 selected = func_08017B68(&data_03002818->records[index].list, RECORD_CURSOR(index)->row);
        u16 value;

        data_03002818->current = data_03002818->saved;
        value = data_03002818->records[index].primary->entries[selected].value;
        data_03002818->records[index].value = value;
        if (value != 0)
            return 10;
        func_08141540(0x6A);
    }
    if (data_03000000.pressed == 8) {
        data_03002818->records[index].action = 8;
    } else if (data_03000000.pressed == 1) {
        EntryTable *table = data_03002818->records[index].secondary;
        s8 row = RECORD_CURSOR(index)->row;
        u16 selected = func_08017B68(&data_03002818->records[index].list, row);

        if (!(table->entries[selected].flags & 1)) {
            data_03002818->records[index].selected_id = table->entries[selected].selected_id;
            data_03002818->records[index].selected = selected;
            data_03002818->records[index].field_44 = table->entries[selected].field_10;
            data_03002818->records[index].field_46 = table->entries[selected].field_12;
            data_03002818->records[index].action = 1;
        } else {
            func_08141540(0x6A);
        }
    } else if (data_03000000.pressed == 2) {
        data_03002818->records[index].action = 2;
    } else if (data_03000000.repeated == 0x80) {
        data_03002818->records[index].action = 0x80;
        old = RECORD_CURSOR(index)->row;
        next = cursor_row(RECORD_CURSOR(index)) + 1;
        if (data_03000000.held & 0x200) {
            u8 visible = data_03002818->records[index].list.visible;
            u16 scroll = data_03002818->records[index].list.scroll;
            u16 count = data_03002818->records[index].list.count;
            u8 position = data_03002818->records[index].cursor.row;

            if (scroll + position < count - 1) {
                if (scroll + visible < count) {
                    if (scroll + visible * 2 < count)
                        data_03002818->records[index].list.scroll = scroll + visible;
                    else
                        data_03002818->records[index].list.scroll =
                            scroll + visible - (scroll + visible * 2 - count);
                    func_08141540(0x6D);
                    func_08017E28(data_03002818->records[index].animation);
                    return 4;
                }
                next = visible > count ? count - 1 : visible - 1;
            }
        }
        row = next;
        if (row < func_08017B50(&data_03002818->records[index].list)) {
            func_08141540(0x6D);
            func_08080F68(&data_03002818->records[index].list, old, 12, 17);
            func_08082254(index, 0x80, row, 0);
        } else if (func_08017A90(&data_03002818->records[index].list, 0x80)) {
            func_08141540(0x6D);
            func_08080F68(&data_03002818->records[index].list, old, 12, 17);
            func_08082254(index, 0x80, row, 1);
            return 7;
        }
    } else if (data_03000000.repeated == 0x40) {
        data_03002818->records[index].action = 0x40;
        old = RECORD_CURSOR(index)->row;
        next = cursor_row(RECORD_CURSOR(index)) - 1;
        if (data_03000000.held & 0x200) {
            u8 visible = data_03002818->records[index].list.visible;
            u16 scroll = data_03002818->records[index].list.scroll;
            u8 position = data_03002818->records[index].cursor.row;

            if (scroll == 0) {
                if (position != 0)
                    next = 0;
            } else {
                if (scroll - visible < 0)
                    data_03002818->records[index].list.scroll = 0;
                else
                    data_03002818->records[index].list.scroll = scroll - visible;
                func_08141540(0x6D);
                func_08017E28(data_03002818->records[index].animation);
                return 4;
            }
        }
        row = next;
        if (row >= 0) {
            func_08141540(0x6D);
            func_08080F68(&data_03002818->records[index].list, old, 12, 17);
            func_08082254(index, 0x40, row, 0);
        } else if (func_08017A90(&data_03002818->records[index].list, 0x40)) {
            func_08141540(0x6D);
            func_08080F68(&data_03002818->records[index].list, old, 12, 17);
            func_08082254(index, 0x40, row, 1);
            return 7;
        }
    } else if (data_03000000.pressed == 0x20) {
        data_03002818->records[index].action = 0x20;
    } else if (data_03000000.pressed == 0x10) {
        data_03002818->records[index].action = 0x10;
    } else if (data_03000000.pressed == 0x100) {
        data_03002818->records[index].action = 0x100;
    } else if (data_03000000.pressed == 0x200) {
        data_03002818->records[index].action = 0x200;
    } else {
        EntryTable *table = data_03002818->records[index].secondary;
        s8 row = RECORD_CURSOR(index)->row;
        u16 selected = func_08017B68(&data_03002818->records[index].list, row);

        if (!(table->entries[selected].flags & 1))
            data_03002818->records[index].selected_id = table->entries[selected].selected_id;
        else
            data_03002818->records[index].selected_id = 0;
    }
    return 6;
}
