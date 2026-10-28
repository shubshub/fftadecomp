#include "ffta.h"

/* 08018A24..08018A90: 108 bytes. */
struct PanelOwner {
    u8 unknown_00[0x14];
    void *surface;
};

struct Panel {
    struct PanelOwner *owner;
    u8 unknown_04[5];
    u8 width;
    u8 x;
    s8 y;
    u16 value;
    u8 flags;
    u8 unknown_0F;
    u8 height;
};

extern struct Panel *data_02009190;
extern u8 func_08017180(void *window);
extern void func_080157A8(void *surface, u8 x, u8 y, u8 width,
                         u8 height, u8 style, u16 value, u8 mode);

u8 func_08018A24(void)
{
    u8 status = func_08017180((u8 *)data_02009190 + 0x14);

    if (status != 0) {
        void *surface = data_02009190->owner->surface;
        u8 x = data_02009190->x + 1;
        s32 original_y = data_02009190->y;
        u8 y;

        if (data_02009190->flags & 2)
            y = original_y + 1;
        else
            y = original_y;
        func_080157A8(surface, x, y, data_02009190->width,
                      data_02009190->height, 0x20,
                      data_02009190->value, 0xB);
    }
    return status;
}
