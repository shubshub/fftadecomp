#include "ffta.h"

extern u32 func_080C95A8(u32 index);
extern void func_080C95C0(u32 index, u32 value);

/* Complete target: [0x080469F8, 0x08046A4C), 84 bytes. */
u8 func_080469F8(u32 *first, u16 *second)
{
    if ((u8)func_080C95A8(12) == 3) {
        *second = 0;
        *first = 0;
    } else if ((u8)func_080C95A8(12) == 2) {
        *second = 0;
    } else if ((u8)func_080C95A8(12) == 1) {
        *first = 0;
    } else {
        return 0;
    }
    func_080C95C0(12, 0);
    return 1;
}
