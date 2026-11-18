#include "ffta.h"

typedef struct {
    u8 *scanlines;
    s16 center;
    s16 limit;
    s16 position;
    u16 unknown_0A;
    u16 mode;
} ScanlineContext;

void func_080921B0(ScanlineContext *context, s16 position)
{
    context->position = position;
}
