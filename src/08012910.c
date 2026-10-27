#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 pending_offset;
    u16 scale;
    u16 limit;
    u8 unknown_1A[0x2EE];
    const u8 *active;
    u8 fallback[1];
} Context08012910;

extern Context08012910 *data_0200918C;

u8 func_08012910(void)
{
    Context08012910 *context = data_0200918C;

    if (context->pending_offset == 0)
        return 0;

    context->limit += 0x100;
    context->active = context->fallback + context->pending_offset;
    context->pending_offset = 0;
    return 1;
}
