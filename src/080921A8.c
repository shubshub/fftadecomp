#include "ffta.h"

typedef struct {
    void *scanlines;
    u16 first;
    u16 second;
    u16 value;
    u16 unknown_0A;
    u16 mode;
} ScanlineContext;

void func_080921A8(ScanlineContext *context)
{
    context->mode = 2;
}
