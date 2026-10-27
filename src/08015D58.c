#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
} TextRegion08015D58;

typedef struct {
    u8 unknown_00[0x14];
} MenuList08015D58;

typedef struct {
    u8 unknown_00;
} MenuCursor08015D58;

typedef struct {
    u8 unknown_00[0x14];
    u16 flags;
    u8 unknown_16[0x16];
    TextRegion08015D58 region;
    MenuList08015D58 list;
    MenuCursor08015D58 cursor;
} Window08015D58;

typedef void (*CursorCallback08015D58)(MenuCursor08015D58 *cursor);

void func_08017C28(MenuList08015D58 *list, TextRegion08015D58 *region,
                   u32 value, u8 flags);
void func_08017DB4(MenuCursor08015D58 *cursor, TextRegion08015D58 *region,
                   CursorCallback08015D58 callback, u32 mode);

void func_08015D58(Window08015D58 *window, u32 value,
                   CursorCallback08015D58 callback)
{
    TextRegion08015D58 *region = &window->region;
    u8 flags = 3;

    if (window->flags & 0x100)
        flags = 7;
    if ((window->flags & 0xc0) == 0x80)
        flags |= 8;
    func_08017C28(&window->list, region, value, flags);

    {
        u32 borderless = window->flags & 2;
        u32 mode = 0;

        if (borderless)
            mode = 0x31;
        func_08017DB4(&window->cursor, region, callback, mode);
    }
}
