#include "ffta.h"

/* Complete [0x08010D2C, 0x08010DCE): 162 bytes, 81 instructions. */
/* Point a sprite at the cell of its current step; flag 0x40 counts the steps
 * from the end of the frame. */

typedef struct Sprite08010D2C {
    u8 active;
    u8 unknown_01[3];
    const u8 *data;
    const u8 *frames;
    u16 frame;
    s16 index;
    u8 unknown_10[2];
    u16 frame_count;
    u16 flags;
    u16 unknown_16;
    const u8 *current;
} Sprite08010D2C;

/* A frame is a step count followed by its steps.  Frames are not aligned in
 * the frame data: the halfwords are read bytewise.  Flag 0x4000 selects the
 * frames with byte-sized steps. */
typedef struct __attribute__((packed)) {
    u16 count;
    struct __attribute__((packed)) {
        u8 cell;
        u8 duration;
    } steps[0];
} CompactFrame08010D2C;

typedef struct __attribute__((packed)) {
    u16 count;
    struct __attribute__((packed)) {
        u16 cell;
        u16 duration;
    } steps[0];
} WideFrame08010D2C;

/* -1 selects the sprite's own frame or step, as in func_0801075C. */
static inline s32 get_cell(Sprite08010D2C *sprite, s16 frame, s16 index)
{
    if (frame == -1)
        frame = sprite->frame;
    if (index == -1)
        index = sprite->index;
    if (sprite->flags & 0x4000) {
        const CompactFrame08010D2C *compact = (const CompactFrame08010D2C *)
            (sprite->frames + ((const u16 *)sprite->frames)[frame]);

        return compact->steps[index].cell;
    } else {
        const WideFrame08010D2C *wide = (const WideFrame08010D2C *)
            (sprite->frames + ((const u32 *)sprite->frames)[frame]);

        return wide->steps[index].cell;
    }
}

void func_08010D2C(Sprite08010D2C *sprite)
{
    const u8 **current = &sprite->current;
    s16 count = sprite->frame_count;
    s16 index = sprite->index;
    s16 cell;

    if (sprite->flags & 0x40)
        index = count - index - 1;
    cell = get_cell(sprite, -1, index);
    if (sprite->flags & 0x2000)
        *current = sprite->data + ((const u16 *)sprite->data)[cell];
    else
        *current = sprite->data + ((const u32 *)sprite->data)[cell];
}
