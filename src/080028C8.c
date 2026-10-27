#include "ffta.h"

typedef s32 (*Compare)(const void *first, const void *second);

extern void func_08002524(void *workspace, void *base, s32 size, s32 count,
                          Compare compare);

/* 080028C8..080028E2: 26 bytes, 12 instructions. */
void func_080028C8(void *workspace, void *base, s32 count, s32 size,
                   Compare compare)
{
    func_08002524(workspace, base, size, count, compare);
}
