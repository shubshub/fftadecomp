#include "ffta.h"

/* Complete [0x0800DA88, 0x0800DAB8): 48 bytes, 21 instructions.
 * Target: f0b5061c1f1c1206150e09040c149f2c0bdcfef7bbfd011c600009182a1c381c
 * 33f1e0fe301cfef7cdfdf0bc01bc0047
 *
 * For a signed index below 160 (there is no lower bound), copies `count`
 * halfwords from `source` into the object's halfword buffer at `index`
 * through the CpuSet wrapper, then sets the object's flag bit with
 * func_0800C64C.
 */
extern u16 *func_0800C614(void *object);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0800C64C(void *object);

void func_0800DA88(void *object, s16 index, u8 count, const u16 *source)
{
    if (index < 160) {
        u16 *values = func_0800C614(object);

        /* CpuCopy16-style control word: (byte size >> 1) & 0x1FFFFF, the
         * shape src/08041FB4.c and src/08085558.c use for this wrapper. */
        func_0814186C(source, values + index,
                      ((count * sizeof(u16)) >> 1) & 0x1FFFFF);
        func_0800C64C(object);
    }
}
