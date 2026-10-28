#include "ffta.h"

/* Target: complete [0x08037398, 0x08037428), 144 bytes. */
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

void func_08037398(u32 x, u32 y, u8 variant, u8 slot)
{
    if (variant) {
        variant += 25;
        func_0804C598(data_03000E30.surface, slot + 3, variant,
                      (u8)x, (u8)y, 0, 0, data_08950000, data_08950F4C,
                      0x52);
    } else {
        func_0804C598(data_03000E30.surface, slot + 3, 1,
                      (u8)x, (u8)y, 0, 0, data_08950000, data_08950F4C,
                      0x38);
    }
}
