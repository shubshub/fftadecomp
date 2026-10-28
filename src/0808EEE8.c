#include "ffta.h"

extern u8 func_080CBA14(u8 id);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B80C(u32 index, u16 *destination, u16 tile, u32 height, u16 palette);

/* Complete [0x0808EEE8, 0x0808EF4A): 98 bytes, 46 instructions. */
void func_0808EEE8(s32 x, s32 y, u32 id, u32 mode)
{
    u16 palette = func_080CBA14(id);
    u16 *destination;

    if (mode == 0)
        palette -= 13;

    destination = func_0808B8E4(1, 1, x * 4 + 1, y * 3 + 2);
    func_0808B80C(1, destination, (id - 2) * 8 + 1, 4, palette << 12);
}
