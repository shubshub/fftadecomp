#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 x;
    u8 y;
    u8 width;
} Window;

typedef struct {
    u8 unknown_00[8];
    u8 mode;
    u8 unknown_09[0x1B];
    Window window;
} Menu;

extern const u8 data_08393ADE[];
extern void func_08001F34(const void *graphic, s32 x, s32 y, u32 a4,
                          u32 a5, u32 a6, u32 a7, u32 a8, u32 a9,
                          u32 a10, u32 a11);

/* Complete target: [0x08066A8C, 0x08066AD0), 68 bytes, 31 instructions. */
void func_08066A8C(Menu *menu)
{
    Window *window = &menu->window;

    if ((u8)(menu->mode - 5) <= 1) {
        func_08001F34(data_08393ADE, (window->x + window->width) * 8 - 40,
                      window->y * 8 - 4, 0, 0, 0, 0, 0, 0, 0, 0);
    }
}
