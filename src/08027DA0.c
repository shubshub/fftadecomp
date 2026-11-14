#include "ffta.h"

// Complete [0x08027DA0, 0x0802800C): 620 bytes, 228 instructions.

typedef struct Layout08027DA0 {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 count;
    u16 flags;
    u8 appearance;
    u8 unknown_09;
    u8 unknown_0A[6];
    u16 cursor;
    u8 scroll;
    u8 unknown_13;
} Layout08027DA0;

typedef struct Menu08027DA0 {
    u8 unknown_00[0x80];
    Layout08027DA0 layout;
    u32 *items;
    u8 *enabled;
    void *text;
} Menu08027DA0;

typedef struct Context08027DA0 {
    u8 unknown_00[4];
    u8 mode;
    u8 unknown_05[9];
    u16 refresh;
    u8 unknown_10[8];
    void *unit;
} Context08027DA0;

typedef void (*BufferCopier08027DA0)(void *, const void *, u32);
typedef void (*BufferInitializer08027DA0)(void *, u32);
typedef void (*BufferFiller08027DA0)(void *, u32, u32);

extern Context08027DA0 *data_0200F438;
extern BufferCopier08027DA0 const data_0836D4BC[];
extern BufferInitializer08027DA0 const g_callbacks_0836D4B8[];
extern BufferFiller08027DA0 const data_0836D4C0[];
extern const Layout08027DA0 data_08391454[];

extern u32 func_08027D10(void);
extern void *func_08005B28(u32 bytes);
extern void func_08005B40(void *object);
extern u8 func_080CDA7C(void *unit);
extern u8 func_080CDB84(void *unit);
extern u8 func_080CDB9C(void *unit);
extern u8 func_080CDCEC(void *unit);
extern u8 func_08025F70(void *unit);
extern u8 func_080C9540(u16 bit_index);
extern u16 func_08013B50(Layout08027DA0 *layout);
extern void func_08027B2C(Menu08027DA0 *menu);
extern void func_08026580(Menu08027DA0 *menu);
extern void func_080261D8(Menu08027DA0 *menu);
extern void func_08027208(Menu08027DA0 *menu);
extern void func_080273DC(Menu08027DA0 *menu);
extern void func_08027528(Menu08027DA0 *menu);
extern void func_0802755C(Menu08027DA0 *menu);
extern void func_08027750(Menu08027DA0 *menu);
extern void func_08027800(Menu08027DA0 *menu);
extern void func_08027918(Menu08027DA0 *menu);

void func_08027DA0(Menu08027DA0 *menu)
{
    Layout08027DA0 *layout = &menu->layout;

    data_0836D4BC[0](layout, &data_08391454[func_08027D10()], sizeof(*layout));
    if (layout->unknown_09 & 8)
        data_0200F438->refresh = 1;

    menu->items = func_08005B28(layout->count * 4);
    g_callbacks_0836D4B8[0](menu->items, layout->count * 4);
    menu->enabled = func_08005B28(layout->count);
    data_0836D4C0[0](menu->enabled, layout->count, 1);

    switch (data_0200F438->mode) {
    case 1:
        func_08027B2C(menu);
        layout->x++;
        break;
    case 4:
        menu->items[0] = 8;
        menu->items[1] = 9;
        menu->items[2] = 10;
        menu->items[3] = 11;
        if (func_080CDA7C(data_0200F438->unit)) {
            menu->items[4] = 0x49;
        } else {
            layout->height = layout->count = layout->count - 1;
            layout->width--;
            layout->x++;
            layout->y += 2;
        }
        if (func_080C9540(4) || func_080CDB84(data_0200F438->unit))
            menu->enabled[0] = 0;
        if (func_080C9540(3) || func_080CDB9C(data_0200F438->unit)) {
            menu->enabled[1] = 0;
            if (menu->items[4] != 0)
                menu->enabled[4] = 0;
        }
        if (func_08025F70(data_0200F438->unit))
            menu->enabled[1] = 0;
        break;
    case 10:
        menu->items[0] = 11;
        if (func_080CDCEC(data_0200F438->unit))
            menu->enabled[0] = 0;
        layout->count = 1;
        layout->height = 1;
        layout->cursor = 0;
        layout->scroll = 0;
        layout->y += 8;
        layout->x++;
        break;
    case 5:
        if (func_080CDA7C(data_0200F438->unit))
            func_08026580(menu);
        else
            func_080261D8(menu);
        break;
    case 6:
    case 7:
    case 8:
        func_08027208(menu);
        break;
    case 11:
        func_08005B40(menu->enabled);
        menu->enabled = 0;
        break;
    case 12:
        func_08005B40(menu->enabled);
        menu->enabled = 0;
        func_080273DC(menu);
        break;
    case 2:
        func_08005B40(menu->enabled);
        menu->enabled = 0;
        func_08027528(menu);
        break;
    case 3:
        func_0802755C(menu);
        break;
    case 13:
        func_08027750(menu);
        break;
    case 14:
        func_08027800(menu);
        break;
    case 15:
        func_08027918(menu);
        break;
    }

    menu->text = func_08005B28(func_08013B50(layout));
}
