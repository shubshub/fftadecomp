#include "ffta.h"

typedef struct {
    u16 start;
    u16 end;
} RenderRange08010058;

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u16 flags;
    RenderRange08010058 ranges[160];
} RenderState08010058;

RenderState08010058 *func_0800C614(void *object);
void func_0800C64C(void *object);

void func_08010058(void *object, u16 first, u8 count, u8 start, u8 end)
{
    RenderState08010058 *state = func_0800C614(object);
    s32 row = (s16)first;
    s32 i;

    for (i = 0; i < count; i++, row++) {
        if (row < 0)
            continue;
        if (row >= 160)
            break;
        state->ranges[row].start = start;
        state->ranges[row].end = end;
    }
    func_0800C64C(object);
}
