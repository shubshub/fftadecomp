#include "ffta.h"

typedef struct {
    u8 unknown_00[0x13];
    u8 field_13;
    u8 field_14;
    u8 field_15;
} MenuList08017DB4;

typedef struct MenuCursor08017DB4 MenuCursor08017DB4;
typedef void (*CursorCallback08017DB4)(MenuCursor08017DB4 *cursor);

struct MenuCursor08017DB4 {
    CursorCallback08017DB4 callback;
    MenuList08017DB4 *list;
    u16 x;
    u16 y;
    u16 field_0C;
    u16 field_0E;
    u8 flags;
    u8 field_11;
    u8 field_12;
};

typedef void (*BufferInitializer08017DB4)(void *destination, u32 size);
extern BufferInitializer08017DB4 const g_callbacks_0836D4B8[];
extern u8 func_08017B44(const MenuList08017DB4 *list);
extern void func_08017E28(MenuCursor08017DB4 *cursor);

/* Complete [0x08017DB4, 0x08017E26): 114 bytes, 52 instructions. */
void func_08017DB4(MenuCursor08017DB4 *cursor, MenuList08017DB4 *list,
                   CursorCallback08017DB4 callback, u8 flags)
{
    if (callback == 0) {
        g_callbacks_0836D4B8[0](cursor, sizeof(MenuCursor08017DB4));
        return;
    }

    cursor->callback = callback;
    cursor->list = list;
    cursor->flags = flags ? flags : 0x11;
    cursor->field_12 = 0;
    cursor->field_0E = 0;
    cursor->x = (func_08017B44(list) + list->field_13) << 3;
    if (cursor->flags & 0x20)
        cursor->x -= 8;
    cursor->y = (list->field_14 << 3) - 4;
    cursor->field_11 = 0;
    cursor->field_0C = 0;
    cursor->field_0E = 0;
    func_08017E28(cursor);
}
