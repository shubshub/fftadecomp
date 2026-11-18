#include "ffta.h"

typedef struct {
    u8 *scanlines;
    s16 center;
    s16 limit;
    s16 position;
    u16 unknown_0A;
    u16 mode;
} ScanlineContext;

extern void func_08022854(u8 *allocation);

void func_08092180(ScanlineContext *context)
{
    func_08022854(context->scanlines);
    func_08022854((u8 *)context);
}
