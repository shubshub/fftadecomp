#include "ffta.h"

typedef struct {
    void *scanlines;
    u16 first;
    u16 second;
    u16 value;
    u16 unknown_0A;
    u16 mode;
} ScanlineContext;

void func_08092198(ScanlineContext *context, u16 first, u16 second)
{
    context->first = first;
    context->second = second;
    context->value = 0;
    context->mode = 1;
}
