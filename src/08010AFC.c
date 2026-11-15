#include "ffta.h"

/* Complete [0x08010AFC, 0x08010D2C): 560 bytes, 269 instructions. */
/* Advance a sprite's blink and step timers by one tick.  Returns 0 only when
 * the sprite has just stopped with flag 0x200 set: func_08010DD0, the one
 * caller, unlinks the sprite on 0. */

/* Flag 0x20 is the hidden phase of a blink: func_08011690 skips a sprite that
 * has it set together with 8 or 0x10.  func_080111CC sets blink_on and
 * blink_off with flag 0x10; func_0801121C sets repeats with flag 0x800. */
typedef struct Sprite08010AFC {
    u8 active;
    u8 blink_on;
    u8 blink_off;
    u8 blink_elapsed;
    const u8 *data;
    const u8 *frames;
    u16 frame;
    s16 index;
    s16 elapsed;
    u16 frame_count;
    u16 flags;
    s16 repeats;
} Sprite08010AFC;

/* A frame is a step count followed by its steps.  Frames are not aligned in
 * the frame data: the halfwords are read bytewise.  Flag 0x4000 selects the
 * frames with byte-sized steps. */
typedef struct __attribute__((packed)) {
    u16 count;
    struct __attribute__((packed)) {
        u8 cell;
        u8 duration;
    } steps[0];
} CompactFrame08010AFC;

typedef struct __attribute__((packed)) {
    u16 count;
    struct __attribute__((packed)) {
        u16 cell;
        u16 duration;
    } steps[0];
} WideFrame08010AFC;

/* Declared as in src/0801093C.c, which records why index is s16 here. */
extern u16 func_0801075C(Sprite08010AFC *sprite, s16 index, u16 format);

/* -1 selects the sprite's own frame or step, as in func_0801075C. */
static inline s32 get_duration(Sprite08010AFC *sprite, s16 frame, s16 index)
{
    if (frame == -1)
        frame = sprite->frame;
    if (index == -1)
        index = sprite->index;
    if (sprite->flags & 0x4000) {
        const CompactFrame08010AFC *compact = (const CompactFrame08010AFC *)
            (sprite->frames + ((const u16 *)sprite->frames)[frame]);

        return compact->steps[index].duration;
    } else {
        const WideFrame08010AFC *wide = (const WideFrame08010AFC *)
            (sprite->frames + ((const u32 *)sprite->frames)[frame]);

        return wide->steps[index].duration;
    }
}

u32 func_08010AFC(Sprite08010AFC *sprite)
{
    u32 result = 1;
    u16 length;
    s16 count;
    s16 index;
    s32 duration;
    u32 stop;
    u32 restart;
    s16 previous;

    if (sprite->flags & 8) {
        sprite->flags ^= 0x20;
    } else if (sprite->flags & 0x10) {
        sprite->blink_elapsed++;
        if (sprite->blink_elapsed <= sprite->blink_on)
            sprite->flags &= ~0x20;
        else
            sprite->flags |= 0x20;
        if (sprite->blink_elapsed == sprite->blink_on + sprite->blink_off)
            sprite->blink_elapsed = 0;
    }

    if (sprite->active == 2)
        return result;
    if (sprite->flags & 0x1000)
        return result;
    if (sprite->flags & 6)
        return result;

    length = func_0801075C(sprite, -1, 0);
    count = sprite->frame_count;
    index = sprite->index;
    if (sprite->flags & 0x40)
        index = count - index - 1;
    duration = get_duration(sprite, -1, index);
    sprite->elapsed++;
    if (sprite->elapsed < duration)
        return result;

    stop = 0;
    restart = 0;
    sprite->elapsed = 0;
    previous = sprite->index;
    sprite->index++;
    if (sprite->index == length) {
        if (sprite->flags & 0x400) {
            stop = 1;
        } else if (sprite->flags & 0x800) {
            if (sprite->repeats > 0)
                sprite->repeats--;
            if (sprite->repeats == 0) {
                sprite->flags &= ~0x800;
                stop = 1;
            } else {
                restart = 1;
            }
        } else {
            stop = 1;
        }
    } else if (sprite->index == length - 1) {
        if (get_duration(sprite, -1, count - 1) == 999) {
            if (sprite->flags & 0x400)
                stop = 1;
            else
                restart = 1;
        }
    }

    if (restart) {
        sprite->index = 0;
    } else if (stop == 1) {
        sprite->index = previous;
        sprite->active = 2;
        if (sprite->flags & 0x100)
            sprite->flags |= 1;
        if (sprite->flags & 0x200)
            result = 0;
    }
    return result;
}
