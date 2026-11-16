#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 pressed;
    u16 repeat;
} MenuInput;

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
    u8 settings[0x20];
} Menu;

typedef void (*MenuCallback)(void *argument);

typedef struct {
    MenuCallback callback;
    void *argument;
    u16 buttons;
} ButtonAction;

extern MenuInput data_03000000;
extern void func_080023D0(void *state);
extern u16 func_08017B50(MenuList *list);
extern u8 func_08017A90(MenuList *list, u16 direction);
extern void func_08017AF4(MenuList *list, u32 row, u32 value);
extern void func_08017FB0(MenuCursor *cursor, u8 row);
extern void func_08017FBC(void *settings, u32 direction);
extern void func_08141540(u32 sound);

/*
 * Complete target: [0x08029F7C, 0x0802A1FC), 640 bytes, 283 instructions.
 *
 * Moves a menu cursor on repeated down/up input: with a scroll callback the
 * cursor walks the visible rows and the callback runs when the list itself
 * scrolls at either end; without one the cursor wraps or (flags bit 0)
 * clamps.  With flags bit 0x80 the old row is recoloured with the list's own
 * palette (0xFF) and the new one with palette 11 (func_08017AF4), then every
 * button action whose buttons were pressed is run.
 */
void func_08029F7C(Menu *menu, u8 flags, MenuCallback scroll, void *argument,
                   ButtonAction *actions, u8 action_count)
{
    /* Both are zeroed at entry (0x08029F9C movs r6, #0; 0x08029F9E mov sl, r6)
     * although every path that reads them assigns them first. */
    s8 next = 0;
    s8 previous = 0;
    u32 changed = 0;
    u8 count = func_08017B50(&menu->list);
    u8 i;

    if (scroll) {
        if (data_03000000.repeat & 0x80) {
            func_080023D0(&data_03000000);
            next = previous = menu->cursor.row;
            next++;
            if (next < func_08017B50(&menu->list)) {
                changed = 1;
                func_08141540(0x6D);
                func_08017FB0(&menu->cursor, next);
                func_08017FBC(menu->settings, 0x80);
            } else if (func_08017A90(&menu->list, 0x80)) {
                next = menu->cursor.row;
                previous = next - 1;
                changed = 1;
                func_08141540(0x6D);
                scroll(argument);
            }
        }
        if (data_03000000.repeat & 0x40) {
            func_080023D0(&data_03000000);
            next = previous = menu->cursor.row;
            next--;
            if (next >= 0) {
                changed = 1;
                func_08141540(0x6D);
                func_08017FB0(&menu->cursor, next);
                func_08017FBC(menu->settings, 0x40);
            } else if (func_08017A90(&menu->list, 0x40)) {
                next = menu->cursor.row;
                previous = next + 1;
                changed = 1;
                func_08141540(0x6D);
                scroll(argument);
            }
        }
    } else {
        if (data_03000000.repeat & 0x80) {
            func_080023D0(&data_03000000);
            next = previous = menu->cursor.row;
            changed = 1;
            next++;
            if (next > count - 1) {
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
        } else if (data_03000000.repeat & 0x40) {
            func_080023D0(&data_03000000);
            next = previous = menu->cursor.row;
            changed = 1;
            next--;
            if (next < 0) {
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
        func_08017AF4(&menu->list, previous, 0xFF);
        func_08017AF4(&menu->list, next, 11);
    }
    for (i = 0; i < action_count; i++) {
        if (data_03000000.pressed & actions[i].buttons)
            actions[i].callback(actions[i].argument);
    }
}
