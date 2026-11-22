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
    s16 position;
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
    u8 *destination;
    u32 value;
    u32 state_value;
} ByteStore;

typedef struct {
    void (*callback)(const ByteStore *store);
    const ByteStore *argument;
    u16 buttons;
    u16 unknown_0A;
} ButtonAction;

typedef struct {
    u8 unknown_0000[0xB54];
    u8 text[0xCD4 - 0xB54];
    u8 phase;
    u8 resume;
    u8 unknown_0CD6[2];
    Table tasks;
    u32 handlers[2];
    u8 handler_flags[2];
    u8 unknown_0CF2[2];
    u8 window[0x2C];
    MenuList list;
    MenuControls controls;
    MenuCursor cursor;
    u8 content[0x10EC - 0xD68];
    u8 dialog[0x1184 - 0x10EC];
    u8 panel[0x1414 - 0x1184];
    u8 message[0x1BB6 - 0x1414];
    u8 unit;
    u8 unknown_1BB7;
    u16 count;
    u8 selected;
    u8 unknown_1BBB[3];
    u8 saved_position;
    u8 saved_row;
    u8 control[0x2C4C - 0x1BC0];
    ButtonAction actions[2];
    u8 unknown_2C64[0xC];
    ByteStore store;
    u8 unknown_2C7C[0x2CA0 - 0x2C7C];
    u8 next;
    u8 unknown_2CA1[3];
    MenuEntry entries[256];
    u8 unknown_30A4[0x338C - 0x30A4];
    u8 unknown_338C;
    u8 unknown_338D[0x33E8 - 0x338D];
    u8 animation[0x3404 - 0x33E8];
} ItemQuantityMenu;

extern ItemQuantityMenu *data_0200F428;
u16 func_08017B68(MenuList *, s8);
void func_0805C220(MenuList *, u16, u8, u32, u32);
void func_0805C340(MenuList *, u8, u8, u8);

#endif
