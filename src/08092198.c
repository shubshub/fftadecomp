#include "ffta.h"

typedef struct {
    u8 *scanlines;
    s16 center;
    s16 limit;
    s16 position;
    u16 unknown_0A;
    u16 mode;
} ScanlineContext;

void func_08092198(ScanlineContext *context, s16 center, s16 limit)
{
    context->center = center;
    context->limit = limit;
    context->position = 0;
    context->mode = 1;
}
