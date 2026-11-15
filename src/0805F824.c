#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    s8 index;
} Cursor;

typedef struct {
    u8 mode;
    s8 count;
    u8 unknown_02[0x3A];
    MenuList list;
    Cursor cursor;
} Menu;

typedef struct {
    u16 held;
    u16 unknown_02;
    u16 pressed;
} InputState;

typedef struct {
    u8 type;
    u8 flags;
    u16 id;
} MenuRecord;

typedef struct {
    u8 unknown_00[0x1B];
    u8 second_count;
    u8 unknown_1C[4];
    MenuRecord *records[1];
} MenuState;

extern InputState data_03000000;
extern MenuState *data_0200F44C;
extern void func_0805F774(Menu *menu, u8 direction);
extern void func_08017AF4(MenuList *list, s8 index, u8 value);
extern void func_08141540(u16 song_id);
extern void func_080023D0(InputState *input);
extern void func_0806144C(u8 enabled);
extern void func_080613D0(void);
extern void func_08017FB0(Cursor *cursor, u8 index);

/* Complete target: [0x0805F824, 0x0805FA4C), 552 bytes, 248 instructions. */
u8 func_0805F824(Menu *menu)
{
    Cursor *cursor = &menu->cursor;
    s8 row = 0;
    u8 changed = 0;
    u16 pressed = data_03000000.pressed;
    u16 held = data_03000000.held;
    s8 oldRow;
    s32 i;

    if (pressed & 0x80)
    {
        if ((held & 0x200) && menu->mode != 1 && menu->mode != 5)
        {
            func_0805F774(menu, 0x80);
            return 1;
        }
        row = cursor->index;
        oldRow = row;
        func_08017AF4(&menu->list, row, 0xFF);
        if (menu->count > 1 && menu->mode != 5)
            func_08141540(0x6D);
        func_080023D0(&data_03000000);
        row++;
        if (row >= menu->count)
        {
            row = 0;
            if (menu->mode == 5)
            {
                for (i = 0; i < 2; i++)
                {
                    MenuRecord *record = data_0200F44C->records[data_0200F44C->second_count - 2 + i];
                    if (record && record->id && (record->flags & 1))
                        row++;
                }
            }
        }
        if (menu->mode == 5 && row != oldRow)
            func_08141540(0x6D);
        changed = 1;
    }
    else if (pressed & 0x40)
    {
        if ((held & 0x200) && menu->mode != 1 && menu->mode != 5)
        {
            func_0805F774(menu, 0x40);
            return 1;
        }
        row = cursor->index;
        oldRow = row;
        func_08017AF4(&menu->list, row, 0xFF);
        if (menu->count > 1 && menu->mode != 5)
            func_08141540(0x6D);
        func_080023D0(&data_03000000);
        row--;
        if (menu->mode == 5)
        {
            for (i = 2; i > 0; i--)
            {
                MenuRecord *record = data_0200F44C->records[data_0200F44C->second_count - 3 + i];
                if (record && record->id && (record->flags & 1))
                    break;
            }
            if (row < i)
                row = menu->count - 1;
        }
        else if (row < 0)
            row = menu->count - 1;
        if (menu->mode == 5 && row != oldRow)
            func_08141540(0x6D);
        changed = 1;
    }
    if (changed)
    {
        if (menu->mode == 5)
        {
            if (row == 2)
                func_0806144C(0);
            else
            {
                MenuRecord *record = data_0200F44C->records[data_0200F44C->second_count - 2 + row];
                if (record && record->id && !(record->flags & 1))
                    func_080613D0();
                else
                    func_0806144C(0);
            }
        }
        func_08017FB0(cursor, row);
        func_08017AF4(&menu->list, row, 0x0B);
    }
    return changed;
}
