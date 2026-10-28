#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
} TileRegion08028350;

typedef struct {
    u8 unknown_00[9];
    u8 flags;
} WindowOptions08028350;

typedef struct {
    u8 unknown_00[0x0b];
    s8 pending;
    TileRegion08028350 region;
    u8 unknown_34[0x4c];
    WindowOptions08028350 options;
} WindowState08028350;

u8 func_08017180(TileRegion08028350 *region);
void func_08025DC8(WindowState08028350 *window, u32 update);
void *func_0802D72C(u32 value);
void func_0802B894(void *dialog, u32 value, u32 mode);

u32 func_08028350(WindowState08028350 *window)
{
    WindowOptions08028350 *options = &window->options;
    u8 complete = func_08017180(&window->region);

    if (complete) {
        func_08025DC8(window, 1);
        return 1;
    }
    if ((options->flags & 0x10) && window->pending != 0) {
        func_0802B894(func_0802D72C(1), 0, (u8)window->pending);
        window->pending = 0;
    }
    return 0;
}
