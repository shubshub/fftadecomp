#include "ffta.h"

extern u8 data_03000028;
extern u8 data_03000030[][1024];
extern s32 data_03000020[];

extern s32 func_080016D4(const void *source, s32 x, s32 y, s32 depth,
                        u8 mode, u32 extra, void *buffer,
                        s32 capacity, s32 count);

/* 08001FEC..08002050: 100 bytes, 43 instructions. */
void func_08001FEC(const void *source, s32 x, s32 y, s32 depth,
                   u8 mode, u32 extra)
{
    u8 *current = &data_03000028;
    void *buffer = data_03000030[*current];
    s32 *counts = data_03000020;
    s32 previous = counts[*current];

    counts[*current] = func_080016D4(source, x, y, depth, mode, extra,
                                    buffer, 128, previous);
}
