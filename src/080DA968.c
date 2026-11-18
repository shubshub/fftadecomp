#include "ffta.h"

struct Object0800C614;

typedef struct {
    u8 unknown_00[4];
    struct Object0800C614 *object;
} DrawingState;

/* The scanline buffer uses the WINxH byte order. */
typedef struct __attribute__((packed)) {
    volatile u8 right : 8;
    volatile u8 left : 8;
} WindowLine;

extern void *func_08005BFC(void *task);
extern void *func_0800C614(const struct Object0800C614 *object);

void func_080DA968(void *task, u16 x, u16 y, u16 width, u16 height)
{
    DrawingState *state = func_08005BFC(task);
    WindowLine *lines = func_0800C614(state->object);
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;
    s16 row;

    left = x - width;
    if (left < 0)
        left = 0;
    right = width + x;
    if (right >= 240)
        right = 240;
    top = y - height;
    if (top < 0)
        top = 0;
    bottom = y + height;
    if (bottom >= 160)
        bottom = 160;
    for (row = top; row < bottom; row++) {
        lines[row].left = left;
        lines[row].right = right;
    }
}
