#include "ffta.h"

typedef struct
{
    const void *image;
    u8 unknown_04;
    u8 transformed;
    u16 unknown_06;
    s16 x;
    s16 y;
    u8 unknown_0C[8];
    s16 scale_x;
    s16 scale_y;
    u8 visible;
} ImageState;

extern void func_080018A0(const void *image, s32 x, s32 y, u32 variant,
                          u32 flip_x, u32 flip_y, u32 flag_28, u32 flag_29,
                          u32 value, s16 scale_x, s16 scale_y, u16 angle,
                          u32 mode);
extern void func_08001F34(const void *image, s32 x, s32 y, u8 variant,
                          u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                          u32 value, u8 mode, const void *transform);

/* Complete target: 0x08136944..0x081369B0, 108 bytes. */
void func_08136944(const ImageState *state)
{
    if (state->visible)
    {
        if (state->transformed)
            func_080018A0(state->image, state->x, state->y, 0, 0, 0, 0,
                          2, 0, state->scale_x, state->scale_y, 0, 1);
        else
            func_08001F34(state->image, state->x, state->y, 0, 0, 0, 0,
                          0, 0, 2, 0);
    }
}
