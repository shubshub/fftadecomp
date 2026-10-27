#include "ffta.h"

typedef struct {
    u8 unknown_00[0x178];
    u16 scanlines[160];
} RenderState0800DBE8;

RenderState0800DBE8 *func_0800C614(void *object);
void func_0800C64C(void *object);

void func_0800DBE8(void *object, s16 first, u8 count, const u16 *source)
{
    RenderState0800DBE8 *state;
    s32 row;
    s32 i;

    if (first >= 160)
        return;
    state = func_0800C614(object);
    row = first;
    for (i = 0; i < count; i++, row++) {
        if (row < 0)
            continue;
        if (row >= 160)
            break;
        state->scanlines[row] = source[i];
    }
    func_0800C64C(object);
}
