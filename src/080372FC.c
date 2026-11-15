#include "ffta.h"

/* Complete [0x080372FC, 0x08037398): 156 bytes, 61 instructions, four literal
 * words in the first pool and three in the second.
 * 70b586b0051c0e1c1206140e1b061b0e002c25d00e49601e8000401802781206c82040
 * 051218120e0a484068d91c2b061b0e3406240e0094002401940294064c0394064c0494
 * 5224059415f027f91ae0a41c3908300e0003000095084c0f95080b484068d91c2b061b
 * 0e3206120e009201940294074a0392074a049230220592012215f00bf906b070bc01bc
 * 00470000300e0003000095084c0f9508
 */
typedef struct {
    u8 entry;
    u8 unknown_01[3];
} RenderChoice;

typedef struct {
    u32 unknown_00;
    Entry *surface;
} RenderState;

extern const RenderChoice data_08391CA4[];
extern RenderState data_03000E30;
extern const u8 data_08950000[];
extern const u8 data_08950F4C[];
extern void func_0804C598(Entry *base, u16 index, u16 selector,
                          u8 width, u8 count, u8 mode, u8 delay,
                          const u8 *graphics, const u8 *layout,
                          u16 attributes);

void func_080372FC(u32 x, u32 y, u8 choice, u8 slot)
{
    if (choice) {
        u8 base = data_08391CA4[choice - 1].entry - 1;
        u8 tile = base + 26;

        func_0804C598(data_03000E30.surface, slot + 3, tile,
                      (u8)x, (u8)y, 0, 0, data_08950000, data_08950F4C,
                      0x52);
    } else {
        func_0804C598(data_03000E30.surface, slot + 3, 1,
                      (u8)x, (u8)y, 0, 0, data_08950000, data_08950F4C,
                      0x30);
    }
}
