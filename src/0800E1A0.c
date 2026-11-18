#include "polygon_scanline.h"

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u16 flags;
    PolygonSpan ranges[160];
    const u8 *data;
    u16 frame;
    u16 unknown_28E;
    PolygonScale scale;
} State;

typedef struct __attribute__((packed)) {
    u16 width;
    s16 frame_count;
} FrameHeader;

/* Complete target: [0x0800E1A0, 0x0800E268), 200 bytes. */
void func_0800E1A0(State *state)
{
    u16 start = 245;
    u16 end = 250;
    PolygonSpan *range = state->ranges;
    s32 i;
    const u8 *data;
    s16 frame_count;
    u16 width;
    const PolygonPoint *frame_data;

    for (i = 159; i >= 0; i--) {
        range->left = start;
        range->right = end;
        range++;
    }

    data = state->data;
    frame_count = ((const FrameHeader *)data)->frame_count;
    width = ((const FrameHeader *)data)->width;
    frame_data = (const PolygonPoint *)(data + 4);
    frame_data += state->frame * width;
    if (state->flags & 4) {
        func_0800F480(frame_data, width, state->x, state->y,
                      state->ranges, 1, &state->scale);
    } else {
        func_0800F308(frame_data, width, state->x, state->y,
                      state->ranges, 1);
    }

    state->frame++;
    if (state->frame == frame_count) {
        if (state->flags & 2) {
            state->frame = 0;
        } else {
            state->frame--;
            state->flags |= 0x8000;
        }
    }
}
