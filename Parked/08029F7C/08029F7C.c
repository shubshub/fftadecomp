#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} MenuCursor;

typedef struct {
    u8 unknown_00[0x2C];
    MenuList list;
    MenuCursor cursor;
    u8 scroll[1];
} Menu;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState;

typedef void (*MenuCallback)(void *argument);

typedef struct {
    MenuCallback callback;
    void *argument;
    u16 buttons;
} ButtonAction;

extern InputState data_03000000;
extern u16 func_08017B50(MenuList *list);
extern u8 func_08017A90(MenuList *list, u16 direction);
extern void func_080023D0(InputState *input);
extern void func_08017FB0(MenuCursor *cursor, u8 row);
extern void func_08017FBC(void *scroll, u32 direction);
extern void func_08017AF4(MenuList *list, s32 row, u8 value);
extern void func_08141540(u32 sound);

/* 0x08029F7C..0x0802A1FC: 640 bytes; navigate and dispatch menu input. */
void func_08029F7C(Menu *menu, u8 flags, MenuCallback scroll_callback,
                  void *argument, ButtonAction *actions, u8 action_count)
{
    s8 next = 0;
    s8 previous = 0;
    u32 changed = 0;
    MenuList *list = &menu->list;
    u8 count = func_08017B50(list);
    u8 i;

    if (scroll_callback) {
        if (data_03000000.repeated & 0x80) {
            func_080023D0(&data_03000000);
            next = previous = menu->cursor.row;
            next++;
            if ((s8)next < func_08017B50(list)) {
                changed = 1;
                func_08141540(0x6D);
                func_08017FB0(&menu->cursor, next);
                func_08017FBC(menu->scroll, 0x80);
            } else if (func_08017A90(list, 0x80)) {
                next = menu->cursor.row;
                previous = (s8)menu->cursor.row - 1;
                changed = 1;
                func_08141540(0x6D);
                scroll_callback(argument);
            }
        }
        if (data_03000000.repeated & 0x40) {
            func_080023D0(&data_03000000);
            next = previous = menu->cursor.row;
            next--;
            if ((s8)next >= 0) {
                changed = 1;
                func_08141540(0x6D);
                func_08017FB0(&menu->cursor, next);
                func_08017FBC(menu->scroll, 0x40);
            } else if (func_08017A90(&menu->list, 0x40)) {
                next = menu->cursor.row;
                previous = (s8)menu->cursor.row + 1;
                changed = 1;
                func_08141540(0x6D);
                scroll_callback(argument);
            }
        }
    } else {
        if (data_03000000.repeated & 0x80) {
            func_080023D0(&data_03000000);
            next = previous = menu->cursor.row;
            changed = 1;
            next++;
            if ((s8)next > count - 1) {
                if (!(flags & 1)) {
                    func_08141540(0x6D);
                    next = 0;
                } else {
                    next = count - 1;
                }
            }
            if (next != previous) {
                func_08141540(0x6D);
                func_08017FB0(&menu->cursor, next);
            }
        } else if (data_03000000.repeated & 0x40) {
            func_080023D0(&data_03000000);
            next = previous = menu->cursor.row;
            changed = 1;
            next--;
            if ((s8)next < 0) {
                if (!(flags & 1)) {
                    func_08141540(0x6D);
                    next = count - 1;
                } else {
                    next = 0;
                }
            }
            if (next != previous) {
                func_08141540(0x6D);
                func_08017FB0(&menu->cursor, next);
            }
        }
    }
    if (changed && (flags & 0x80)) {
        func_08017AF4(&menu->list, (s8)previous, 0xFF);
        func_08017AF4(&menu->list, (s8)next, 11);
    }
    for (i = 0; i < action_count; i++) {
        if (data_03000000.pressed & actions[i].buttons)
            actions[i].callback(actions[i].argument);
    }
}
