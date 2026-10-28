#include "ffta.h"

typedef struct {
    u16 left;
    u16 right;
} ScanlineSpan;

extern u8 data_02009160;
extern void func_0800ED58(s32 centerX, s32 centerY, u16 radius,
                          u16 halfRadius, ScanlineSpan *spans,
                          u8 clip, u8 side);

/* Target: complete [0x0800F860, 0x0800F93A), 218 bytes. */
void func_0800F860(u16 centerX, u16 centerY, u16 radius,
                   u16 height, ScanlineSpan *spans, u8 clip)
{
    u16 first;

    if (radius == 0)
        return;

    first = 0;
    if (clip == 0)
        centerY = height;
    else if (height == 0)
        height = centerY;
    else
        first = centerY - height;

    if (height != 0)
    {
        s32 row = (s16)first;
        s32 right = radius + centerX;
        ScanlineSpan *span = &spans[row];
        s32 left = centerX - radius;
        const u8 *edgeOffset = &data_02009160;
        u32 remaining;

        for (remaining = height; remaining != 0; span++, remaining--)
        {
            if (row >= 0 && (clip == 0 || row < 160))
            {
                span->left = left;
                span->right = *edgeOffset + right;
            }
        }
    }

    if (clip == 0)
        func_0800ED58((s16)centerX, (s16)centerY, radius, radius >> 1,
                      spans + height, clip, 1);
    else
        func_0800ED58((s16)centerX, (s16)centerY, radius, radius >> 1,
                      spans, clip, 1);
}
