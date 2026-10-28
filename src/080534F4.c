#include "ffta.h"

/* 0x080534F4 .. 0x08053568: 116 bytes, 51 instructions. */
typedef struct {
    u8 unknown_00[0x15];
    u8 width;
    u8 unknown_16[0x0a];
} Panel080534F4;

typedef struct {
    u8 unknown_00[0x11];
    s8 selected;
} Controls080534F4;

typedef struct {
    u8 unknown_0000[0xd1c];
    Panel080534F4 panel;
    Controls080534F4 controls;
} Context080534F4;

extern Context080534F4 *data_0200F428;
extern void func_08054204(Panel080534F4 *, s8, u8, u8, u8);
extern void func_0802B108(Panel080534F4 *);

void func_080534F4(void)
{
    Panel080534F4 *panel = &data_0200F428->panel;
    Controls080534F4 *controls = &data_0200F428->controls;
    u8 row;
    s8 selected = controls->selected;

    for (row = 0; row < 4; row++) {
        if (row == selected)
            func_08054204(panel, row * 3, 0x0b, 2, panel->width - 2);
        else
            func_08054204(panel, row * 3, 0xff, 2, panel->width - 2);
    }
    func_0802B108(panel);
}
