#include "polygon_scanline.h"

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u16 flags;
    PolygonSpan ranges[160];
    PolygonPoint vertices[3];
} RenderState;

extern RenderState *func_0800C614(void *object);
extern void func_08010058(void *object, u16 first, u8 count,
                          u8 start, u8 end);

/* 08010220..08010282: 98 bytes, 45 instructions. */
void func_08010220(void *object, const PolygonPoint *source)
{
    PolygonPoint *destination = func_0800C614(object)->vertices;
    RenderState *state;
    s32 remaining;

    for (remaining = 2; remaining >= 0; remaining--) {
        destination->x = source->x;
        destination->y = source->y;
        destination++;
        source++;
    }

    state = func_0800C614(object);
    func_08010058(object, 0, 160, 245, 250);
    func_0800F308(state->vertices, 3, state->x, state->y, state->ranges, 1);
}
