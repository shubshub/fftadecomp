#include "ffta.h"

extern u8 data_03002F58;
extern u8 data_03002F68[][256];
extern u32 *data_03002F60[];
extern u32 *func_080016D4(const void *source, s32 x, s32 y, u32 flags,
                         u8 mode, const void *transform, u8 *entries,
                         u32 capacity, u32 *output);

/* 08001ED0..08001F34: 100 bytes, 43 instructions. */
void func_08001ED0(const void *source, s32 x, s32 y, u32 flags,
                   u8 mode, const void *transform)
{
    u8 *current = &data_03002F58;
    u8 *entries = data_03002F68[*current];
    u32 **outputs = data_03002F60;
    u32 *output = outputs[*current];

    outputs[*current] = func_080016D4(source, x, y, flags, mode, transform,
                                     entries, 32, output);
}
