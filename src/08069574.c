#include "ffta.h"

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} MenuCursor;

typedef struct {
    u8 unknown_0000[0x14E0];
    MenuCursor cursor;
    u8 unknown_14F4[0x446C - 0x14F4];
    u8 selection;
} MenuContext;

extern MenuContext *data_0200F428;
extern void func_08141540(u16 song_id);
extern u8 func_080C9540(u16 bit_index);

void func_08069574(void *argument)
{
    u8 *state = argument;
    MenuContext *menu;
    MenuCursor *cursor;

    func_08141540(0x64);
    if (!func_080C9540(0x31A)) {
        menu = data_0200F428;
        cursor = &menu->cursor;
        switch (cursor->row) {
        case 0:
            *state = 20;
            menu->selection = 22;
            break;
        case 1:
            *state = 20;
            menu->selection = 23;
            break;
        case 2:
            *state = 20;
            menu->selection = 40;
            break;
        }
    } else {
        menu = data_0200F428;
        cursor = &menu->cursor;
        switch (cursor->row) {
        case 0:
            *state = 20;
            menu->selection = 22;
            break;
        case 1:
            *state = 20;
            menu->selection = 23;
            break;
        case 2:
            *state = 20;
            menu->selection = 24;
            break;
        case 3:
            *state = 20;
            menu->selection = 40;
            break;
        }
    }
}
