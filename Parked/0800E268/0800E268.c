#include "ffta.h"

/* 0x0800E268..0x0800E454: 492 bytes. */
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
    u16 count;
    u16 originY;
    Scanline lines[1];
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

void func_0800E268(AnimatedScanlines *object)
{
    Animation *animation = object->animation;
    PositionedAnimation *positioned = (PositionedAnimation *)animation;
    Scanline *line;
    Shape *shape;
    s32 i;
    s16 x;
    s16 y;
    u32 frameCount;
    s32 worldX;
    s32 worldY;
    s16 scanY;
    Frame *frame;
    PositionedFrame *positionedFrame;
    u32 duration;

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
    worldX = (s16)(x + object->x);
    worldY = (s16)(y + object->y);
    line = object->lines;
    scanY = worldY - shape->originY;
    i = 0;
    while (i < (s16)shape->count) {
        if (scanY >= 0) {
            if (scanY > 159)
                break;
            line[scanY].left = worldX + shape->lines[i].left;
            line[scanY].right = worldX + shape->lines[i].right;
        }
        ++i;
        ++scanY;
    }
    if (--object->remaining == 0) {
        if (++object->frame == frameCount) {
            if (!(object->flags & 2)) {
                object->frame = frameCount - 1;
                object->flags |= 0x8000;
            } else {
                object->frame = 0;
            }
        } else {
            if (object->type == 10) {
                positionedFrame = &positioned->frames[object->frame];
                duration = positionedFrame->duration;
            } else {
                frame = &animation->frames[object->frame];
                duration = frame->duration;
            }
            if (duration == 999)
                object->frame = 0;
        }
        if (object->type == 10) {
            positionedFrame = &positioned->frames[object->frame];
            duration = positionedFrame->duration;
        } else {
            frame = &animation->frames[object->frame];
            duration = frame->duration;
        }
        object->remaining = duration;
    }
}
