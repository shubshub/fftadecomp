#include "ffta.h"

/* Target: complete [0x0813DF5C, 0x0813E030), 212 bytes, 106 instructions. */
typedef struct {
    u16 image_index;
    u16 duration;
} Frame0813DF5C;

typedef struct {
    u16 count;
    u16 unknown_02;
    const Frame0813DF5C *frames;
} Track0813DF5C;

typedef struct {
    const u32 *resource;
    const u32 *offsets;
    Track0813DF5C tracks[10];
    u16 count;
    u16 timers[10];
    u16 frame_indices[10];
    u8 finished[10];
    u8 playback_mode;
} Animation0813DF5C;

void func_0813DF5C(Animation0813DF5C *animation, const u32 *resource,
                   const u32 *offsets, s32 elapsed, u8 playback_mode)
{
    const u8 *track;
    s32 time;
    u8 i;

    animation->resource = resource;
    animation->offsets = offsets;
    animation->count = offsets[0] >> 2;
    for (i = 0; i < animation->count; i++) {
        time = elapsed;
        animation->frame_indices[i] = 0;
        animation->timers[i] = 0;
        animation->finished[i] = 0;
        track = (const u8 *)animation->offsets + animation->offsets[i];
        animation->tracks[i].count = *(const u16 *)track;
        animation->tracks[i].frames = (const Frame0813DF5C *)(track + 2);
        for (;;) {
            time -= animation->tracks[i].frames[animation->frame_indices[i]].duration;
            if (time < 0) {
                animation->timers[i] = -time;
                goto next;
            }
            animation->frame_indices[i]++;
            if (animation->frame_indices[i] >= animation->tracks[i].count) {
                animation->frame_indices[i] = animation->tracks[i].count - 1;
                break;
            }
        }
    next:;
    }
    animation->playback_mode = playback_mode;
}
