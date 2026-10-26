#include "ffta.h"

extern void func_0804C4D4(Entry *base, u16 index, u16 selector,
                        u8 width, u8 count, u8 mode, u8 delay,
                        const u8 *graphics, const u8 *layout, u16 attributes);

/* Complete target: [0x0804C598, 0x0804C5F8), 96 bytes. */
void func_0804C598(Entry *base, u16 index, u16 selector,
                   u8 width, u8 count, u8 mode, u8 delay,
                   const u8 *graphics, const u8 *layout, u16 attributes)
{
    func_0804C4D4(base, index, selector, width, count, mode, delay,
                   graphics, layout, attributes);
    base[index].field_0c = 1;
}
