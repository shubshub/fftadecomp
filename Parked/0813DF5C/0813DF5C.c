#include "ffta.h"

struct Frame0813DF5C {
    u16 value;
    u16 duration;
};

struct Track0813DF5C {
    u16 frame_count;
    struct Frame0813DF5C *frames;
};

struct Animation0813DF5C {
    void *resource;
    u32 *offsets;
    struct Track0813DF5C tracks[10];
    u16 track_count;
    u16 remaining[10];
    u16 frame_indices[10];
    u8 track_flags[10];
    u8 mode;
};

/* Target: [0x0813DF5C, 0x0813E030), 212 bytes, 106 instructions. */
void func_0813DF5C(struct Animation0813DF5C *animation, void *resource,
                   u32 *offsets, s32 elapsed, u8 mode)
{
    u8 i;

    animation->resource = resource;
    animation->offsets = offsets;
    animation->track_count = offsets[0] >> 2;
    for (i = 0; i < animation->track_count; i++) {
        s32 remaining = elapsed;
        u8 *track;

        animation->frame_indices[i] = 0;
        animation->remaining[i] = 0;
        animation->track_flags[i] = 0;
        track = (u8 *)animation->offsets + animation->offsets[i];
        animation->tracks[i].frame_count = *(u16 *)track;
        animation->tracks[i].frames = (struct Frame0813DF5C *)(track + 2);
        for (;;) {
            remaining -= animation->tracks[i].frames[animation->frame_indices[i]].duration;
            if (remaining < 0) {
                animation->remaining[i] = -remaining;
                break;
            }
            animation->frame_indices[i]++;
            if (animation->frame_indices[i] >= animation->tracks[i].frame_count) {
                animation->frame_indices[i] = animation->tracks[i].frame_count - 1;
                break;
            }
        }
    }
    animation->mode = mode;
}
