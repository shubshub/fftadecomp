#include "ffta.h"

// 0x0800E268..0x0800E454: 492 bytes, 239 instructions.

typedef struct {
    u16 left;
    u16 right;
} Scanline;

typedef struct __attribute__((packed)) {
    s16 shape;
    u16 duration;
} Frame;

typedef struct __attribute__((packed)) {
    s16 shape;
    u16 duration;
    s16 x;
    s16 y;
} PositionedFrame;

typedef struct __attribute__((packed)) {
    u16 unknown_00;
    Frame frames[1];
} Animation;

typedef struct __attribute__((packed)) {
    u16 unknown_00;
    PositionedFrame frames[1];
} PositionedAnimation;

typedef struct {
    s16 left;
    s16 right;
} ShapeLine;

typedef struct {
    s16 count;
    s16 originY;
    ShapeLine lines[1];
} Shape;

typedef struct {
    s16 x;
    s16 y;
    u8 type;
    u8 unknown_05;
    u16 flags;
    Scanline lines[160];
    s32 *shapes;
    Animation *animation;
    u16 frame;
    u16 remaining;
    u16 frameCount;
} AnimatedScanlines;

static inline void draw_shape(const Shape *shape, s16 x, s16 y, Scanline *lines)
{
    s32 i;
    s16 scanY = y - shape->originY;

    for (i = 0; i < shape->count; i++, scanY++) {
        if (scanY >= 0) {
            if (scanY >= 160)
                break;
            lines[scanY].left = x + shape->lines[i].left;
            lines[scanY].right = x + shape->lines[i].right;
        }
    }
}

void func_0800E268(AnimatedScanlines *object)
{
    Animation *animation = object->animation;
    PositionedAnimation *positioned = (PositionedAnimation *)animation;
    Shape *shape;
    s16 x;
    s16 y;
    u16 frameCount;
    Frame *frame;
    PositionedFrame *positionedFrame;

    {
        s32 row;
        for (row = 0; row < 160; ++row) {
            object->lines[row].left = 245;
            object->lines[row].right = 250;
        }
    }
    x = 0;
    y = 0;
    frameCount = object->frameCount;
    if (object->type == 10) {
        positionedFrame = &positioned->frames[object->frame];
        shape = (Shape *)((u8 *)object->shapes + object->shapes[positionedFrame->shape]);
        x = positionedFrame->x;
        y = positionedFrame->y;
    } else {
        frame = &animation->frames[object->frame];
        shape = (Shape *)((u8 *)object->shapes + object->shapes[frame->shape]);
    }
    draw_shape(shape, x + object->x, y + object->y, object->lines);
    if (--object->remaining == 0) {
        object->frame++;
        if (object->frame == frameCount) {
            if (object->flags & 2) {
                object->frame = 0;
            } else {
                object->frame = frameCount - 1;
                object->flags |= 0x8000;
            }
        } else if (object->type == 10) {
            positionedFrame = &positioned->frames[object->frame];
            if (positionedFrame->duration == 999)
                object->frame = 0;
        } else {
            frame = &animation->frames[object->frame];
            if (frame->duration == 999)
                object->frame = 0;
        }
        if (object->type == 10) {
            positionedFrame = &positioned->frames[object->frame];
            object->remaining = positionedFrame->duration;
        } else {
            frame = &animation->frames[object->frame];
            object->remaining = frame->duration;
        }
    }
}
