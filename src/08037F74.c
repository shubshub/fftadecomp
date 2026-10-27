#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
} TextRegion08037F74;

typedef struct MenuList08037F74 {
    u8 unknown_00[0x14];
} MenuList08037F74;

typedef struct MenuCursor08037F74 {
    u8 unknown_00[0x14];
} MenuCursor08037F74;

typedef struct {
    u8 unknown_00[0x2C];
    TextRegion08037F74 region;
    MenuList08037F74 list;
    MenuCursor08037F74 cursor;
} Window08037F74;

typedef void (*ListCallback08037F74)(MenuList08037F74 *list);
typedef void (*CursorCallback08037F74)(MenuCursor08037F74 *cursor);

extern void func_08017C28(MenuList08037F74 *list, TextRegion08037F74 *region,
                         ListCallback08037F74 callback, u8 flags);
extern void func_08017DB4(MenuCursor08037F74 *cursor, TextRegion08037F74 *region,
                         CursorCallback08037F74 callback, u8 mode);

/* Complete [0x08037F74, 0x08037FB0): 60 bytes, 28 instructions. */
void func_08037F74(Window08037F74 *window, ListCallback08037F74 primary,
                   CursorCallback08037F74 secondary, u8 flags, u8 mode)
{
    TextRegion08037F74 *region = &window->region;

    func_08017C28(&window->list, region, primary, flags);
    func_08017DB4(&window->cursor, region, secondary, mode);
}
