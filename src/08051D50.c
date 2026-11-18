#include "ffta.h"

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} MenuCursor;

typedef struct {
    u8 unknown_0000[0xD3C];
    MenuCursor cursor;
    u8 unknown_0D50[0x1D44 - 0xD50];
    u8 selection;
} MenuContext;

extern MenuContext *data_0200F428;
extern void func_08141540(u16 song_id);

void func_08051D50(void *argument)
{
    u8 *state = argument;
    MenuContext *context;
    MenuCursor *cursor;

    func_08141540(0x64);
    context = data_0200F428;
    cursor = &context->cursor;
    switch (cursor->row) {
    case 0:
        *state = 0xC8;
        context->selection = 0xFE;
        break;
    case 1:
        *state = 0xC8;
        context->selection = 0xB4;
        break;
    case 2:
        *state = 0x64;
        break;
    }
}
