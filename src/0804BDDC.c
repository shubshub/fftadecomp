#include "ffta.h"

typedef struct {
    u8 unknown_00[0xA0];
    u16 first[256];
    u16 second[256];
} PaletteState0804BDDC;

extern PaletteState0804BDDC *g_state_03002810;
extern u16 data_03003860[];
extern s32 func_081426B8(s32, s32);
extern s16 func_08007A60(u8);

// Complete [0x0804BDDC, 0x0804BEE8): 268 bytes, 127 instructions.
void func_0804BDDC(u8 period, u8 phase)
{
    u16 *first = g_state_03002810->first;
    u16 *second = g_state_03002810->second;
    u16 *out_first = data_03003860;
    u16 *out_second = data_03003860 + 256;
    u16 amount = 32 - (func_08007A60(func_081426B8(64, period) * phase) >> 3);
    u16 i;

    for (i = 0; i < 256; ++i, ++first, ++second) {
        *out_first++ = (*first & 31) * (32 - amount) / 32
            | ((((*first >> 5) & 31) * (32 - amount) / 32) << 5)
            | ((((*first >> 10) & 31) * (32 - amount) / 32) << 10);
        *out_second++ = (*second & 31) * (32 - amount) / 32
            | ((((*second >> 5) & 31) * (32 - amount) / 32) << 5)
            | ((((*second >> 10) & 31) * (32 - amount) / 32) << 10);
    }
}
