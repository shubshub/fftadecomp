#include "ffta.h"

typedef struct {
    u8 unknown_00[0x15];
    u8 palette;
    u8 unknown_16[0x0A];
} MenuWindow;

typedef struct {
    u8 unknown_00[0x11];
    s8 selection;
} MenuCursor;

typedef struct {
    u8 unknown_00[0x14BC];
    MenuWindow window;
    MenuCursor cursor;
} MenuState;

extern MenuState *data_0200F428;
extern void func_08058348(MenuWindow *window, s8 column, u8 color,
                         u32 row, u8 palette);
extern void func_0802B108(MenuWindow *window);

void func_080573E8(void)
{
    MenuWindow *window = &data_0200F428->window;
    MenuCursor *cursor = &data_0200F428->cursor;
    s8 selection = cursor->selection;
    u8 i;

    for (i = 0; i < 3; i++)
    {
        if (i == selection)
            func_08058348(window, i * 5, 0x0B, 0, window->palette);
        else
            func_08058348(window, i * 5, 0xFF, 0, window->palette);
    }
    func_0802B108(window);
}
