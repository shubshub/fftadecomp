#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    s8 index;
} Cursor;

typedef struct {
    u8 unknown_00;
    s8 count;
    u8 unknown_02[0x3A];
    MenuList list;
    Cursor cursor;
} Menu;

typedef struct {
    u16 held;
    u16 unknown_02;
    u16 pressed;
} InputState;

typedef struct {
    u8 unknown_00[0x16];
    u8 mode;
} ControlState;

extern InputState data_03000000;
extern ControlState *data_0200F44C;

void func_080023D0(void *input);
void func_0805F774(Menu *menu, u16 direction);
u16 func_08017B68(MenuList *list, u32 index);
s16 func_08017BE8(MenuList *list);
void func_08017AF4(MenuList *list, u32 index, u32 value);
u16 func_08017B50(MenuList *list);
u8 func_08017A90(MenuList *list, u16 direction);
void func_0805F708(Menu *menu, u16 direction, s8 index, u32 wrap);
void func_08141540(u32 sound);

/* Complete target: [0x0805FA4C, 0x0805FB9C), 336 bytes. */
u32 func_0805FA4C(Menu *menu)
{
    MenuList *list = &menu->list;
    Cursor *cursor = &menu->cursor;
    u16 pressed = data_03000000.pressed;
    u16 held = data_03000000.held;
    s8 current;
    s8 next;

    if (pressed & 0x80) {
        func_080023D0(&data_03000000);
        if (held & 0x200) {
            func_0805F774(menu, 0x80);
            return 1;
        } else {
            current = cursor->index;

            if (func_08017B68(list, current) < func_08017BE8(list))
                func_08017AF4(list, current, 0xFF);
            next = current + 1;
            if (next < func_08017B50(list)) {
                if (menu->count > 1)
                    func_08141540(0x6D);
                func_0805F708(menu, 0x80, next, 0);
                return 1;
            } else if (func_08017A90(list, 0x80)) {
                func_08141540(0x6D);
                func_0805F708(menu, 0x80, next, 1);
                data_0200F44C->mode = 5;
                return 2;
            }
        }
    } else if (pressed & 0x40) {
        func_080023D0(&data_03000000);
        if (held & 0x200) {
            func_0805F774(menu, 0x40);
            return 1;
        } else {
            current = cursor->index;

            if (func_08017B68(list, current) != 0)
                func_08017AF4(list, current, 0xFF);
            next = current - 1;
            if (next >= 0) {
                if (menu->count > 1)
                    func_08141540(0x6D);
                func_0805F708(menu, 0x40, next, 0);
                return 1;
            } else if (func_08017A90(list, 0x40)) {
                func_08141540(0x6D);
                func_0805F708(menu, 0x40, next, 1);
                data_0200F44C->mode = 5;
                return 2;
            }
        }
    }
    return 0;
}
