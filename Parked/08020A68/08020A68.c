#include "ffta.h"

struct Animation08020A68 {
    u8 active;
    u8 kind;
    u16 remaining;
    u8 frame;
    u8 restart_frame;
    u8 changed;
    u8 unknown_07;
    u16 reference;
    u16 unknown_0a;
    u16 progress;
    u16 flags;
    const u8 *frames;
    const u8 *first_base;
    const u8 *second_base;
    const u8 *first_current;
    const u8 *second_current;
    u8 unknown_24[8];
};

struct AnimationState08020A68 {
    u32 unknown_00;
    struct Animation08020A68 animations[4];
};

extern struct AnimationState08020A68 *g_state_0200F1D4;

/* Target: [0x08020A68, 0x08020B9E), 310 bytes, 152 instructions. */
void func_08020A68(void)
{
    const u8 *frames = 0;
    u8 frame_count = 0;
    u8 index;

    for (index = 0; index < 4; index++) {
        struct Animation08020A68 *animation =
            &g_state_0200F1D4->animations[index];
        u32 flags;
        u16 reference;
        u8 kind;

        if (!animation->active)
            continue;
        if (animation->flags & 2)
            continue;
        reference = animation->reference;
        kind = animation->kind;
        if (kind == 0) {
            frames = animation->frames;
            frame_count = frames[2];
        } else if (kind == 1) {
            frames = animation->frames;
            frame_count = frames[2];
        }

        flags = animation->flags;
        if (--animation->remaining == 0) {
            if (flags & 4) {
                if (animation->frame == 0xff) {
                    animation->frame = frame_count - 1;
                } else if (animation->frame == 0) {
                    if (flags & 1) {
                        if (animation->restart_frame == 0xff)
                            animation->frame = frame_count - 1;
                        else
                            animation->frame = animation->restart_frame;
                    } else {
                        animation->active = 0;
                        continue;
                    }
                } else {
                    animation->frame--;
                }
            } else {
                if (++animation->frame == frame_count) {
                    if (flags & 1) {
                        if (animation->restart_frame == 0xff)
                            animation->frame = 0;
                        else
                            animation->frame = animation->restart_frame;
                    } else {
                        animation->active = 0;
                        continue;
                    }
                }
            }

            if (kind == 0) {
                const u8 *frame = frames + animation->frame * 4;
                u8 low = frame[4];
                u32 duration = frame[5] << 8;
                animation->remaining = duration | low;
            } else if (kind == 1) {
                const u8 *frame = frames + animation->frame * 4;
                u8 low = frame[4];
                u32 duration = frame[5] << 8;
                animation->remaining = duration | low;
            }
            animation->progress = 0;
            animation->first_current = animation->first_base;
            switch (kind) {
            case 0:
                {
                    const u8 *frame = frames + animation->frame * 4;
                    u8 low = frame[6];
                    u32 offset = frame[7] << 8;
                    offset |= low;
                    animation->second_current = animation->second_base +
                        (offset << 5);
                }
                break;
            case 1:
                {
                    const u8 *frame = frames + animation->frame * 4;
                    u8 low = frame[6];
                    u32 offset = frame[7] << 8;
                    offset |= low;
                    animation->second_current = animation->second_base +
                        (offset << 1);
                }
                break;
            }
        }
        if (animation->progress != reference)
            animation->changed = 1;
    }
}
