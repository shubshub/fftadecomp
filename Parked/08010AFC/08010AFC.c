#include "ffta.h"

typedef struct {
    u8 status;
    u8 blink_on;
    u8 blink_off;
    u8 blink_tick;
    u32 unknown_04;
    const u8 *data;
    s16 animation;
    s16 frame;
    s16 tick;
    s16 reverse_length;
    u16 flags;
    s16 repeats;
} Animation;

typedef struct __attribute__((packed)) {
    u16 value;
} FrameDuration;

u16 func_0801075C(Animation *animation, s32 frame, u32 mode);

static inline u16 frame_duration(Animation *animation, s16 sequence, s16 frame)
{
    const u8 *data;
    const u8 *frames;

    if (sequence == -1) {
        sequence = animation->animation;
    }
    if (frame == -1) {
        frame = animation->frame;
    }
    if (animation->flags & 0x4000) {
        data = animation->data;
        frames = data + ((const u16 *)data)[(s16)sequence];
        frames += 3;
        return frames[(s16)frame * 2];
    } else {
        data = animation->data;
        frames = data + ((const u32 *)data)[(s16)sequence];
        return ((const FrameDuration *)(frames + (s16)frame * 4 + 4))->value;
    }
}

/* Complete target: [0x08010AFC, 0x08010D2C), 560 bytes. */
u32 func_08010AFC(Animation *animation)
{
    u32 result = 1;
    u16 length;
    s16 reverse_length;
    s16 frame;
    u16 duration;
    u32 stop;
    u32 restart;
    s16 previous_frame;

    if (animation->flags & 8) {
        animation->flags ^= 0x20;
    } else if (animation->flags & 0x10) {
        animation->blink_tick++;
        if (animation->blink_tick <= animation->blink_on) {
            animation->flags &= 0xFFDF;
        } else {
            animation->flags |= 0x20;
        }
        if (animation->blink_tick == animation->blink_on + animation->blink_off) {
            animation->blink_tick = 0;
        }
    }

    if (animation->status == 2) {
        return result;
    }
    if (animation->flags & 0x1000) {
        return result;
    }
    if (animation->flags & 6) {
        return result;
    }

    length = func_0801075C(animation, -1, 0);
    reverse_length = animation->reverse_length;
    frame = animation->frame;
    if (animation->flags & 0x40) {
        frame = reverse_length - (s16)frame - 1;
    }
    duration = frame_duration(animation, -1, frame);
    animation->tick++;
    if (animation->tick < duration) {
        return result;
    }

    stop = 0;
    restart = 0;
    animation->tick = 0;
    previous_frame = animation->frame;
    animation->frame++;
    if (animation->frame == length) {
        if (animation->flags & 0x400) {
            stop = 1;
        } else if (animation->flags & 0x800) {
            if (animation->repeats > 0) {
                animation->repeats--;
            }
            if (animation->repeats == 0) {
                animation->flags &= 0xF7FF;
                stop = 1;
            } else {
                restart = 1;
            }
        } else {
            stop = 1;
        }
    } else if (animation->frame == length - 1) {
        frame = reverse_length - 1;
        duration = frame_duration(animation, -1, frame);
        if (duration == 999) {
            if (animation->flags & 0x400) {
                stop = 1;
            } else {
                restart = 1;
            }
        }
    }

    if (restart) {
        animation->frame = 0;
    } else if (stop == 1) {
        animation->frame = previous_frame;
        animation->status = 2;
        if (animation->flags & 0x100) {
            animation->flags |= 1;
        }
        if (animation->flags & 0x200) {
            result = 0;
        }
    }
    return result;
}
