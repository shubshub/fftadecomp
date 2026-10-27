#include "ffta.h"

/* 0x08038238..0x08038324: 236 bytes, 110 instructions. */
typedef struct {
    u8 unknown_00;
    u8 palette;
    u8 unknown_02[0x32];
    s8 x;
    s8 y;
    u8 unknown_36[0x12];
    s8 width;
    s8 height;
    u8 unknown_4A[2];
} WindowGeometry;

typedef struct {
    u8 unknown_00[8];
    u16 x;
    u16 y;
    u16 frame;
    u8 unknown_0E[2];
    u8 flags;
} CursorState;

extern WindowGeometry data_030009E0[];
extern const u8 data_083919EE[];
extern u16 func_08017FC4(CursorState *state);
extern void func_08001F34(const void *sprite, s32 x, s32 y, u32 attributes,
                         u32 a, u32 b, u32 c, u32 flip_y, u32 d,
                         u32 palette, u32 e);

void func_08038238(s32 window, CursorState *state)
{
    WindowGeometry *geometry = &data_030009E0[window];
    s32 x = (geometry->x + geometry->width - 1) * 8 + state->x;

    if (x > 232) {
        x = 232;
    }
    if (state->flags & 4) {
        func_08001F34(data_083919EE, x,
                     (geometry->y + geometry->height - 1) * 8 + state->y - ((state->frame >> 3) & 1),
                     0, 0, 0, 0, 0, 0, geometry->palette, 0);
    }
    if (state->flags & 8) {
        s32 y = func_08017FC4(state);

        y += (geometry->y + geometry->height - 1) * 8;
        y += (state->frame >> 3) & 1;
        func_08001F34(data_083919EE, x, y, 0, 0, 0, 0, 1, 0, geometry->palette, 0);
    }
    state->frame++;
}
