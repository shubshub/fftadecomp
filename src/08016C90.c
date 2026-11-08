#include "ffta.h"

typedef struct {
    u8 unknown_00[0x12];
    u8 width;
    u8 height;
    u16 flags;
    u8 unknown_16[6];
    u8 status;
    u8 unknown_1D[2];
    u8 mode;
    s16 current_width;
    s16 current_height;
    s16 target_width;
    s16 target_height;
    s16 width_step;
    s16 height_step;
} State08016C90;

extern void func_08141540(u32 sound);

/* Complete target [0x08016C90, 0x08016D62): 210 bytes. */
void func_08016C90(State08016C90 *state, u8 mode)
{
    u8 frames;

    if (!(state->status & 1))
        func_08141540(0x65);
    state->status |= 4;
    if (mode == 0x10) {
        state->current_width = state->width;
        state->current_height = state->height;
        state->mode = mode;
    } else {
        state->current_width = 0;
        state->current_height = 0;
        state->mode = mode & 0x7F;
        frames = (mode & 0x80) ? 8 : 4;
        if (state->flags & 0x20)
            state->width_step = 4;
        else
            state->width_step = (u8)((u32)state->width / frames);
        if (!state->width_step)
            state->width_step = 1;
        if (state->mode & 1)
            state->width_step += state->width_step & 1;
        if ((state->flags & 0x20) || !(state->mode & 1)) {
            state->height_step = 1;
            state->current_height = state->height;
        } else {
            state->height_step = (u8)((u32)state->height / frames);
            if (!state->height_step)
                state->height_step = 1;
        }
    }
    state->target_width = state->width;
    state->target_height = state->height;
}
