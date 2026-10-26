#include "ffta.h"

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeat;
} MenuInput;

typedef struct {
    u8 unknown_00[0x20];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
} MenuCursor;

typedef struct {
    u8 mode;
    s8 count;
    u8 unknown_02[0x3A];
    MenuList list;
    MenuCursor cursor;
} MenuState;

typedef struct {
    u8 unknown_00;
    u8 flags;
    u16 count;
} MenuItem;

typedef struct {
    u8 unknown_00[0x1B];
    u8 count;
    u8 unknown_1C[4];
    MenuItem *items[64];
} MenuItems;

extern MenuInput data_03000000;
extern MenuItems *data_0200F44C;
extern void func_0805F774(MenuState *menu, u16 direction);
extern void func_08017AF4(MenuList *list, s8 row, u8 color);
extern void func_08141540(u32 sound);
extern void func_080023D0(MenuInput *input);
extern void func_0806144C(u32 mode);
extern void func_080613D0(void);
extern void func_08017FB0(MenuCursor *cursor, u8 row);

/* Complete target: [0x0805F824, 0x0805FA4C), 552 bytes, 248 instructions. */
u8 func_0805F824(MenuState *menu)
{
    MenuCursor *cursor = &menu->cursor;
    s8 row = 0;
    u8 changed = 0;
    u16 repeat = data_03000000.repeat;
    u16 held = data_03000000.held;
    u32 oldRow;
    s32 i;

    if (repeat & 0x80)
    {
        if ((held & 0x200) && menu->mode != 1 && menu->mode != 5)
        {
            func_0805F774(menu, 0x80);
            return 1;
        }
        row = cursor->row;
        oldRow = (u8)row;
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
                    MenuItem *item = data_0200F44C->items[data_0200F44C->count - 2 + i];
                    if (item && item->count && (item->flags & 1))
                        row++;
                }
            }
        }
        if (menu->mode == 5 && (u8)row != oldRow)
            func_08141540(0x6D);
        changed = 1;
    }
    else if (repeat & 0x40)
    {
        if ((held & 0x200) && menu->mode != 1 && menu->mode != 5)
        {
            func_0805F774(menu, 0x40);
            return 1;
        }
        row = cursor->row;
        oldRow = (u8)row;
        func_08017AF4(&menu->list, row, 0xFF);
        if (menu->count > 1 && menu->mode != 5)
            func_08141540(0x6D);
        func_080023D0(&data_03000000);
        row--;
        if (menu->mode == 5)
        {
            for (i = 2; i > 0; i--)
            {
                s32 itemIndex = i - 3;
                MenuItem *item = data_0200F44C->items[itemIndex + data_0200F44C->count];
                if (item && item->count && (item->flags & 1))
                    break;
            }
            if (row < i)
                row = menu->count - 1;
        }
        else if (row < 0)
            row = menu->count - 1;
        if (menu->mode == 5 && (u8)row != oldRow)
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
                s32 itemIndex = row - 2;
                MenuItem *item = data_0200F44C->items[itemIndex + data_0200F44C->count];
                if (item && item->count && !(item->flags & 1))
                    func_080613D0();
                else
                    func_0806144C(0);
            }
        }
        func_08017FB0(cursor, (u8)row);
        func_08017AF4(&menu->list, row, 0x0B);
    }
    return changed;
}
