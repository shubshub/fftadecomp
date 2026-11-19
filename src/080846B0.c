#include "ffta.h"

/* Complete [0x080846B0, 0x08084A98): 1000 bytes, 406 instructions. */

typedef struct {
    u16 id;
    u16 flags;
    u8 unknown_04[8];
    u16 value;
    u8 kind;
    u8 unknown_0F[5];
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
    u8 unknown_00[0x36];
    u8 cancel;
    u8 unknown_37;
    u16 value;
    u8 flag;
    u8 unknown_3B[3];
    u16 action;
    u16 selected_id;
    u8 unknown_42[6];
    EntryTable *primary;
    u8 panel[0x2C];
    MenuList list;
    MenuCursor cursor;
    u8 settings[0x14];
    u8 unknown_C0[8];
    EntryTable *secondary;
} MenuRecord;

typedef struct {
    u8 unknown_0000[0x42B];
    u8 delay;
    u8 unknown_042C[0x285C];
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
extern void func_08017AF4(MenuList *list, s8 row, u8 mode);
extern void func_08017508(u8 *panel, u8 mode);
extern void func_08017D18(void *control, u8 flags);
extern void func_08017E28(void *control);
extern void func_08141540(u16 song_id);
extern void func_080845B4(u32 index, u8 direction, s8 row, u8 refresh);

u8 func_080846B0(u32 index, u16 mask)
{
    u16 pressed;
    u8 old_row;
    u8 next;

    if (data_03002818->delay) {
        data_03002818->delay--;
        return 6;
    }

    pressed = data_03000000.pressed & mask;
    if (pressed == 4) {
        s8 selected = func_08017B68(&data_03002818->records[index].list,
                                    (s8)(&data_03002818->records[index].cursor)->row);

        if ((data_03002818->records[index].value =
             data_03002818->records[index].primary->entries[selected].value) != 0)
            return 10;
        func_08141540(0x6A);
    }

    if (pressed == 1) {
        EntryTable *table = data_03002818->records[index].secondary;
        s8 row = (&data_03002818->records[index].cursor)->row;
        u16 selected = func_08017B68(&data_03002818->records[index].list, row);

        if (table->entries[selected].flags & 1) {
            data_03002818->records[index].action = 1;
            data_03002818->records[index].selected_id = table->entries[selected].kind;
        } else {
            func_08141540(0x6A);
        }
    }

    if (pressed == 2) {
        data_03002818->records[index].action = 2;
        data_03002818->records[index].cancel = 0xFF;
        func_08017508(data_03002818->records[index].panel, 16);
        func_08017D18(&data_03002818->records[index].cursor, 0);
        func_08017D18(data_03002818->records[index].settings, 0);
        data_03002818->records[index].flag = 0;
        return 9;
    }

    if (data_03000000.repeated == 0x80) {
        data_03002818->records[index].action = 0x80;
        old_row = (&data_03002818->records[index].cursor)->row;
        {
            /* A second, signed read of the row: the ROM loads the byte again
               (ldrb at 0x08084852, after old_row's at 0x0808484E) and
               sign-extends it (lsls/asrs #24 at 0x08084854-0x08084856)
               before the increment and the narrowing into next
               (0x08084858-0x0808485C). */
            s8 row = (&data_03002818->records[index].cursor)->row;

            next = row + 1;
        }
        if (data_03000000.held & 0x200) {
            u16 page = data_03002818->records[index].list.page_size;
            u16 offset = data_03002818->records[index].list.offset;
            u16 count = data_03002818->records[index].list.count;
            /* The row as a 16-bit value beside the 16-bit offset and count,
               signed like this function's other row locals.  The ROM reads
               the byte with ldrb at 0x08084882 and adds it to the offset at
               0x08084884 for the compare with count - 1 at 0x08084888. */
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
            func_08017AF4(&data_03002818->records[index].list, old_row, 12);
            func_080845B4(index, 0x80, (s8)next, 0);
        } else if (func_08017A90(&data_03002818->records[index].list, 0x80)) {
            func_08141540(0x6D);
            func_08017AF4(&data_03002818->records[index].list, old_row, 12);
            func_080845B4(index, 0x80, (s8)next, 1);
            return 7;
        }
    } else if (data_03000000.repeated == 0x40) {
        data_03002818->records[index].action = 0x40;
        old_row = (&data_03002818->records[index].cursor)->row;
        next = old_row - 1;
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

        if ((s8)next < 0) {
            if (func_08017A90(&data_03002818->records[index].list, 0x40)) {
                func_08141540(0x6D);
                func_08017AF4(&data_03002818->records[index].list, old_row, 12);
                func_080845B4(index, 0x40, (s8)next, 1);
                return 7;
            }
        } else {
            func_08141540(0x6D);
            func_08017AF4(&data_03002818->records[index].list, old_row, 12);
            func_080845B4(index, 0x40, (s8)next, 0);
        }
    }
    return 6;
}
