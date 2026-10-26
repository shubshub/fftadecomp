#include "ffta.h"

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
} MenuCursor;

typedef struct {
    u8 unknown_00[8];
    u8 mode;
    u8 unknown_09;
    u8 count;
    u8 unknown_0B[0x5D];
    MenuCursor cursor;
} MenuState;

extern u8 data_03000000[];
extern void func_080023D0(void *input);
extern void func_08050AF4(MenuState *menu, u16 direction);
extern void func_08050BF0(MenuState *menu, u8 row);
extern void func_08141540(u32 sound);
extern void func_08017FB0(MenuCursor *cursor, u8 row);
extern void func_08050B9C(MenuState *menu, u8 row, u32 mode);

/* Complete target: [0x08050844, 0x0805093C), 248 bytes, 107 instructions. */
void func_08050844(MenuState *menu, u16 keys, u16 held)
{
    MenuCursor *cursor = &menu->cursor;
    s8 row = 0;
    u8 changed = 0;

    if (keys & 0x80)
    {
        func_080023D0(data_03000000);
        if (held & 0x200)
        {
            func_08050AF4(menu, 0x80);
            return;
        }
        row = cursor->row;
        func_08050BF0(menu, (u8)row);
        if (menu->count > 1)
            func_08141540(0x6D);
        row++;
        if (row >= menu->count)
            row = 0;
        func_08017FB0(cursor, (u8)row);
        changed = 1;
    }
    else if (keys & 0x40)
    {
        func_080023D0(data_03000000);
        if ((held & 0x200) && menu->mode != 1)
        {
            func_08050AF4(menu, 0x40);
            return;
        }
        row = cursor->row;
        func_08050BF0(menu, (u8)row);
        if (menu->count > 1)
            func_08141540(0x6D);
        row--;
        if (row < 0)
            row = menu->count - 1;
        changed = 1;
    }
    if (changed)
    {
        func_08017FB0(cursor, (u8)row);
        func_08050B9C(menu, (u8)row, 0);
    }
}
