#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 pressed;
    u16 repeated;
} InputState;

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    u8 unknown_0C[5];
    s8 selection;
    u8 unknown_12[0x16];
} MenuCursor;

typedef struct {
    u16 unknown_00;
    u16 unknown_02;
    s16 x;
    s16 y;
} MenuOption;

typedef struct {
    u8 unknown_00[0x58];
    MenuCursor cursor;
    MenuOption options[2];
} MenuWork;

typedef struct {
    u16 status;
} MenuControl;

extern InputState data_03000000;
extern MenuControl *data_0200F438;
extern void func_08141570(s32 player, u16 sound);
extern void func_08141540(u32 sound);
extern void func_080023D0(InputState *input);

/* Complete [0x08029350, 0x080293DC): 140 bytes, 57 instructions. */
u8 func_08029350(MenuWork *work)
{
    MenuCursor *cursor = &work->cursor;
    InputState *input = &data_03000000;
    u16 pressed = input->pressed;
    u16 repeated = input->repeated;

    if (pressed & 2) {
        func_08141570(1, 0x69);
        data_0200F438->status = 0xFFFF;
        return 1;
    }
    if (pressed & 1) {
        func_08141540(0x64);
        data_0200F438->status = (u8)cursor->selection + 1;
        return 1;
    }
    if (repeated & 0xC0) {
        MenuOption *options = work->options;
        u8 selection = cursor->selection;
        s8 next_selection;

        func_08141540(0x6D);
        func_080023D0(input);
        next_selection = selection ^ 1;
        cursor->selection = next_selection;
        options += next_selection;
        cursor->x = options->x - 6;
        cursor->y = options->y + 3;
    }
    return 0;
}
