#include "ffta.h"

struct Window {
    void *surface;
    u8 unknown4[0xC];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 flags;
    u8 style;
};

extern void func_080157A8(void *surface, u8 x, u8 y, u8 width,
                         u8 height, u8 style, u16 value, u8 mode);

void func_08017380(const struct Window *window, u16 value, u8 mode)
{
    u8 x = window->x + 1;
    u8 y = window->y + 1;
    u8 width = window->width - 2;
    s32 original_height = window->height;
    u8 height = (original_height - 2) / 2;

    if (window->flags & 2) {
        x = window->x;
        width = window->width;
    }
    if (window->flags & 4) {
        u32 full_height;

        y = window->y;
        full_height = original_height;
        if (original_height & 1)
            full_height = original_height + 1;
        height = (u8)full_height / 2;
    }
    if ((window->flags & 0xC20) == 0) {
        y++;
        height = window->height - 3;
        height /= 2;
    }
    func_080157A8(window->surface, x, y, width, height,
                  window->style, value, mode);
}
