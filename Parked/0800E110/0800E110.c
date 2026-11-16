#include "ffta.h"

typedef struct {
    u16 start;
    u16 end;
} Range;

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u16 flags;
    Range ranges[160];
    const u8 *data;
    u16 frame;
    u16 unknown_28E;
    u8 unknown_290[1];
} State;

State *func_0800C614(void *object);
void func_08010058(void *object, u16 first, u8 count, u8 start, u8 end);
void func_0800F480(const u8 *data, u32 width, s32 x, s32 y,
                  Range *ranges, u32 mode, const void *extra);
void func_0800F308(const u8 *data, u32 width, s32 x, s32 y,
                  Range *ranges, u32 mode);

typedef struct __attribute__((packed)) {
    u16 width;
    s16 frame_count;
} FrameHeader;

// Complete target: [0x0800E110, 0x0800E1A0), 144 bytes.
void func_0800E110(void *object)
{
    State *state = func_0800C614(object);
    const u8 *data;
    u32 width;
    const u8 *frame_data;

    func_08010058(object, 0, 160, 245, 250);

    data = state->data;
    width = ((const FrameHeader *)data)->width;
    frame_data = data + 4;
    frame_data += state->frame * width * 4;
    if (state->flags & 4) {
        func_0800F480(frame_data, width, state->x, state->y,
                      state->ranges, 1, state->unknown_290);
    } else {
        func_0800F308(frame_data, width, state->x, state->y,
                      state->ranges, 1);
    }
}
