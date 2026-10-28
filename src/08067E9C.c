#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 id;
} Item;

typedef struct {
    u8 unknown_00[0x424];
    Item *items[0];
} MenuOwner;

typedef struct {
    u8 unknown_00[0x20];
} MenuList;

typedef struct {
    MenuOwner *owner;
    u8 unknown_04[4];
    u8 mode;
    u8 unknown_09[0x47];
    MenuList list;
} Menu;

extern u16 func_08017B68(MenuList *list, u32 index);
extern void func_08017B1C(MenuList *list, u32 index, u32 style);

/* Complete target: [0x08067E9C, 0x08067EE4), 72 bytes, 32 instructions. */
void func_08067E9C(Menu *menu, u8 row)
{
    if (menu->mode == 5) {
        u16 index = func_08017B68(&menu->list, (s8)row);

        if (menu->owner->items[index]->id != 0)
            return;
    }
    func_08017B1C(&menu->list, (s8)row, 0xFF);
}
