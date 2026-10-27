#include "ffta.h"

typedef struct {
    u8 unknown_00[0xC];
    u16 scroll;
    u8 unknown_0E[0xC];
    u8 selected;
} MenuCursor;

typedef struct {
    u8 x;
    u8 y;
    u8 unknown_02[18];
} MapPosition;

typedef struct {
    u32 unknown_00;
    MenuCursor *cursor;
    u8 unknown_08[0x674];
    MapPosition *positions;
} MenuContext;

typedef struct {
    u32 unknown_00;
    void *surface;
} RenderState;

extern MenuContext *g_state_03002810;
extern RenderState data_03000E30;
extern const u8 data_08950D98[];
extern const u8 data_08951550[];
extern void func_0804C4D4(void *, u32, u32, u32, u8, u32, u32,
                         const u8 *, const u8 *, u16);

/* Complete target: 0x08036CA8..0x08036D44, 156 bytes. */
void func_08036CA8(void)
{
    MenuCursor *cursor = g_state_03002810->cursor;
    u8 selected = cursor->selected - 1;
    MapPosition *position = &g_state_03002810->positions[selected];
    s32 pixel_x = position->x * 8;
    s32 x = pixel_x + 8;
    s32 y = position->y * 8 - cursor->scroll + 7;

    if (x < 12)
        x = 12;
    else if (pixel_x + 32 > 250)
        x = 226;

    if (y < 10)
        y = 10;
    else if (y > 136)
        y = 136;

    func_0804C4D4(data_03000E30.surface, 3, 0, (u8)x, (u8)y, 0, 1,
                  data_08950D98, data_08951550, 0x126);
}
