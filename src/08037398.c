#include "ffta.h"

/* Complete [0x08037398, 0x08037428): 144 bytes, 56 instructions, three literal
 * words in each of two pools.
 * 70b586b0051c0e1c1206140e1b06190e002c1fd02206c82040051218120e0a4840680331
 * 2b061b0e3406240e0094002401940294054c0394054c04945224059415f0def819e00000
 * 300e0003000095084c0f95080b48406803312b061b0e3206120e009201940294074a0392
 * 074a049238220592012215f0c3f806b070bc01bc00470000300e0003000095084c0f9508
 */

typedef struct {
    u32 unknown_00;
    Entry *surface;
} RenderState;

extern RenderState data_03000E30;
extern const u8 data_08950000[];
extern const u8 data_08950F4C[];
extern void func_0804C598(Entry *base, u16 index, u16 selector,
                          u8 width, u8 count, u8 mode, u8 delay,
                          const u8 *graphics, const u8 *layout,
                          u16 attributes);

void func_08037398(u32 x, u32 y, u8 icon, u8 slot)
{
    if (icon) {
        u8 base = icon - 1;
        u8 tile = base + 26;

        func_0804C598(data_03000E30.surface, slot + 3, tile,
                      (u8)x, (u8)y, 0, 0, data_08950000, data_08950F4C,
                      0x52);
    } else {
        func_0804C598(data_03000E30.surface, slot + 3, 1,
                      (u8)x, (u8)y, 0, 0, data_08950000, data_08950F4C,
                      0x38);
    }
}
