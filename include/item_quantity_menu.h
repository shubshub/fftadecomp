#ifndef GUARD_ITEM_QUANTITY_MENU_H
#define GUARD_ITEM_QUANTITY_MENU_H

#include "ffta.h"

typedef struct MenuList {
    u8 unknown_00[8];
    u16 *dest;
    u16 *source;
    u8 unknown_10[5];
    u8 rows;
    u8 columns;
    u8 unknown_17;
    u16 count;
    u16 position;
    u16 first_tile;
    u8 stride;
    u8 palette;
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} MenuControls;

typedef struct {
    u8 unknown_00[4];
    MenuList *list;
    u8 unknown_08[8];
    u8 flags;
} MenuCursor;

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 unknown_03;
} MenuEntry;

typedef struct {
    u8 unknown_0000[0xCF4];
    u8 window[0x2C];
    MenuList list;
    MenuControls controls;
    MenuCursor cursor;
    u8 content[0x1BB8 - 0xD68];
    u16 count;
    u8 selected;
    u8 unknown_1BBB[0x2CA4 - 0x1BBB];
    MenuEntry entries[256];
} ItemQuantityMenu;

extern ItemQuantityMenu *data_0200F428;
u16 func_08017B68(MenuList *, u32);
void func_0805C220(MenuList *, u16, u8, u32, u32);
void func_0805C340(MenuList *, u8, u8, u8);

#endif
