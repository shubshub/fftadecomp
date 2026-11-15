#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 index;
    u8 unknown_12[2];
} MenuCursor;

typedef struct {
    u8 unknown_00[0x48];
    MenuList list;
    MenuCursor cursor;
    u8 unknown_7c[1];
} Menu;

extern void func_08017FBC(void *object, u8 direction);
extern void func_08017FB0(MenuCursor *cursor, u8 index);
extern void func_080505BC(Menu *menu, s8 row);
extern void func_08017884(MenuList *list, u32 direction, u32 mode);
extern void func_08050B9C(Menu *menu, u8 index, u8 skip_empty);

/* Complete [0x08050A8C, 0x08050AF2): 102 bytes, 46 instructions. */
void func_08050A8C(Menu *menu, u8 direction, s8 index, u8 wrap)
{
    MenuCursor *cursor = &menu->cursor;
    u8 *unknown_7c = menu->unknown_7c;
    MenuList *list = &menu->list;

    func_08017FBC(unknown_7c, direction);
    if (!wrap) {
        func_08017FB0(cursor, index);
    } else {
        func_080505BC(menu, index);
        func_08017884(list, direction, 1);
    }
    func_08050B9C(menu, cursor->index, 0);
}
