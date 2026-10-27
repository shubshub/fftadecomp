#include "ffta.h"

extern void func_0804C524(Entry *base, u16 index, u32 selector,
                         u8 width, u8 count, u32 mode, u8 delay,
                         const u8 *graphics, const u8 *layout,
                         u16 attributes, u8 extra);

/* 0804C4D4..0804C524: 80 bytes, 39 instructions. */
void func_0804C4D4(Entry *base, u16 index, u16 selector,
                   u8 width, u8 count, u8 mode, u8 delay,
                   const u8 *graphics, const u8 *layout, u16 attributes)
{
    func_0804C524(base, index, selector, width, count, mode, delay,
                   graphics, layout, attributes, 0);
}
