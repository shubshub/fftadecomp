#include "ffta.h"

/* Complete [0x080823B0, 0x0808286C): 1212 bytes, 487 instructions. */

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
    u8 page_size;
    u8 unknown_17;
    u16 count;
    u16 offset;
    u8 unknown_1C[4];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
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
    u8 settings[0x14];
    u8 unknown_C0[8];
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
extern void func_08017E28(void *control);
extern void func_08080F68(MenuList *list, s8 row, u8 palette, u8 count);
extern void func_08082254(u32 index, u8 direction, s8 row, u8 refresh);
extern void func_08141540(u16 song_id);

s32 func_080823B0(u32 index)
{
    u8 old_row;
    u8 next;

    if (data_03002818->delay != 0) {
        data_03002818->delay--;
        return 6;
    }
    if (data_03000000.pressed == 4) {
        u16 selected = func_08017B68(&data_03002818->records[index].list,
                                     (s8)(&data_03002818->records[index].cursor)->row);
        /* The ROM stores the entry's value (strh at 0x0808242E) and tests
           the same register (cmp r0 at 0x08082430); the assignment inside
           the condition of func_08081DEC reads the entry again
           (ldrh at 0x08081E42). */
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
        s8 row = (&data_03002818->records[index].cursor)->row;
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
        old_row = (&data_03002818->records[index].cursor)->row;
        {
            /* A second, signed read of the row: the ROM loads the byte again
               (ldrb at 0x08082526, after old_row's at 0x08082522) and
               sign-extends it (lsls/asrs #24 at 0x08082528-0x0808252A)
               before the increment and the narrowing into next
               (0x0808252C-0x08082530), as func_080846B0 does. */
            s8 row = (&data_03002818->records[index].cursor)->row;

            next = row + 1;
        }
        if (data_03000000.held & 0x200) {
            u16 page = data_03002818->records[index].list.page_size;
            u16 offset = data_03002818->records[index].list.offset;
            u16 count = data_03002818->records[index].list.count;
            /* The row as a 16-bit value beside the 16-bit offset and count,
               as in func_080846B0's copy of this block.  The ROM reads the
               byte with ldrb at 0x08082558 and adds it to the offset at
               0x0808255A for the compare with count - 1 at 0x0808255E. */
            s16 row = data_03002818->records[index].cursor.row;

            if (offset + row < count - 1) {
                if (offset + page < count) {
                    u16 span = page * 2;

                    if (offset + span < count)
                        data_03002818->records[index].list.offset = offset + page;
                    else
                        data_03002818->records[index].list.offset =
                            offset + page - (offset + span - count);
                    func_08141540(0x6D);
                    func_08017E28(data_03002818->records[index].settings);
                    return 4;
                } else {
                    if (page > count)
                        next = count - 1;
                    else
                        next = page - 1;
                }
            }
        }

        if ((s8)next < func_08017B50(&data_03002818->records[index].list)) {
            func_08141540(0x6D);
            func_08080F68(&data_03002818->records[index].list, old_row, 12, 17);
            func_08082254(index, 0x80, (s8)next, 0);
        } else if (func_08017A90(&data_03002818->records[index].list, 0x80)) {
            func_08141540(0x6D);
            func_08080F68(&data_03002818->records[index].list, old_row, 12, 17);
            func_08082254(index, 0x80, (s8)next, 1);
            return 7;
        }
    } else if (data_03000000.repeated == 0x40) {
        data_03002818->records[index].action = 0x40;
        old_row = (&data_03002818->records[index].cursor)->row;
        {
            /* The same second, signed read as the 0x80 branch: ldrb at
               0x0808265C after old_row's at 0x08082658, lsls/asrs #24 at
               0x0808265E-0x08082660, then the decrement and the narrowing
               into next (0x08082662-0x08082666). */
            s8 row = (&data_03002818->records[index].cursor)->row;

            next = row - 1;
        }
        if (data_03000000.held & 0x200) {
            u16 page = data_03002818->records[index].list.page_size;
            u16 offset = data_03002818->records[index].list.offset;
            u16 cursor = data_03002818->records[index].cursor.row;

            if (offset == 0) {
                if (cursor != 0)
                    next = 0;
            } else {
                if (offset - page >= 0)
                    data_03002818->records[index].list.offset = offset - page;
                else
                    data_03002818->records[index].list.offset = 0;
                func_08141540(0x6D);
                func_08017E28(data_03002818->records[index].settings);
                return 4;
            }
        }

        if ((s8)next >= 0) {
            func_08141540(0x6D);
            func_08080F68(&data_03002818->records[index].list, old_row, 12, 17);
            func_08082254(index, 0x40, (s8)next, 0);
        } else if (func_08017A90(&data_03002818->records[index].list, 0x40)) {
            func_08141540(0x6D);
            func_08080F68(&data_03002818->records[index].list, old_row, 12, 17);
            func_08082254(index, 0x40, (s8)next, 1);
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
        s8 row = (&data_03002818->records[index].cursor)->row;
        u16 selected = func_08017B68(&data_03002818->records[index].list, row);

        if (!(table->entries[selected].flags & 1))
            data_03002818->records[index].selected_id = table->entries[selected].selected_id;
        else
            data_03002818->records[index].selected_id = 0;
    }
    return 6;
}
