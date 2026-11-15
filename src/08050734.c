#include "ffta.h"

/* Target: complete [0x08050734, 0x08050844), 272 bytes. */
typedef struct __attribute__((packed)) {
    u16 identifier : 10;
    u16 unknown_0A : 6;
} Unit;

typedef union {
    const Unit *unit;
    const u8 *record;
    u32 value;
} MenuEntry;

typedef struct {
    u8 unknown_000[0x424];
    MenuEntry entries[64];
} MenuItems;

typedef struct {
    MenuItems *items;
    u8 unknown_04[4];
    u8 kind;
} MenuState;

typedef struct {
    u8 unknown_00[2];
    u8 category;
    u8 unknown_03[13];
} ItemCategory;

extern const ItemCategory g_table_08521214[];
extern void *func_08005B28(u32 byte_count);
extern void func_08005B40(void *object);
extern u32 func_080CE4DC(u16 identifier, u8 selector);
extern void func_080CB9B0(void *object, u32 value);
extern void func_080CB980(void *object, u32 value);
extern void func_0814186C(const void *source, void *destination, u32 control);

u8 *func_08050734(MenuState *menu, void *output, u16 index)
{
    u8 *destination = output;
    void *buffer;
    const Unit *unit;
    const ItemCategory *category;
    u8 icon;
    u16 identifier;

    switch (menu->kind) {
    case 3:
        buffer = func_08005B28(0x80);
        unit = menu->items->entries[index].unit;
        icon = func_080CE4DC(unit->identifier, 2);
        icon += 15;
        if (func_080CE4DC(unit->identifier, 1) == 1)
            icon = 6;
        func_080CB9B0(buffer, icon);
        func_0814186C(buffer, destination, 0x40);
        func_08005B40(buffer);
        destination += 0x80;
        break;
    case 4:
        buffer = func_08005B28(0x80);
        category = &g_table_08521214[*menu->items->entries[index].record];
        if (category->category)
            identifier = 0x18A + category->category;
        else
            identifier = 0;
        func_080CB980(buffer, identifier);
        func_0814186C(buffer, destination, 0x40);
        func_08005B40(buffer);
        destination += 0x80;
        break;
    case 5:
        buffer = func_08005B28(0x80);
        if ((u16)menu->items->entries[index].value <= 0x55)
            identifier = 0x189;
        else
            identifier = 0x18A;
        func_080CB980(buffer, identifier);
        func_0814186C(buffer, destination, 0x40);
        func_08005B40(buffer);
        destination += 0x80;
        break;
    }
    return destination;
}
