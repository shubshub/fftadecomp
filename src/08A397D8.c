#include "ffta.h"

/* 0x08A397D8..0x08A39884: 172 bytes, 78 instructions.  Installed at
 * 0x03006C24 and called through ROM slot 0x08394044.  An OAM list builder
 * front end: it passes its arguments through to func_08A39458 with the
 * current OAM buffer (128 entries) and the buffer's entry count, and stores
 * the new count back (see 08001F34).
 */
extern u8 data_03000028;
extern u8 data_03000030[][1024];
extern s32 data_03000020[];

extern s32 func_08A39458(const void *source, s32 x, s32 y, u8 variant,
                         u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                         const u16 *tiles, u8 priority, s32 palette,
                         s32 tile_count, u8 *entries, s32 capacity,
                         s32 count);

void func_08A397D8(const void *source, s32 x, s32 y, u8 variant,
                   u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                   const u16 *tiles, u8 priority, s32 palette,
                   s32 tile_count)
{
    u8 *entries = data_03000030[data_03000028];
    s32 count = data_03000020[data_03000028];

    data_03000020[data_03000028] = func_08A39458(source, x, y, variant,
        flip_x, flip_y, flag_28, flag_29, tiles, priority, palette,
        tile_count, entries, 128, count);
}
