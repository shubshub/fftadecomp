#include "ffta.h"

/* Complete [0x0800D9E0, 0x0800DA46): 102 bytes, 47 instructions.
 * Target: f0b5474680b4051c06980906090e0e1c1206140e1b061f0e0006000e8046002001290b
 * d0012902dc002903d00de0022e04d00ae0281cfef7fdfd06e0281cfef7f9fda1000919890140
 * 18790041184246079833f11bff281cfef708fe08bc9846f0bc01bc0047
 *
 * Copies `count` halfwords from `source` into row `row` (modes 1 and 2) or
 * the first row (mode 0) of the object's 160-entry halfword rows at `index`
 * through the CpuSet wrapper, then sets the object's flag bit with
 * func_0800C64C.  The store-one-value counterpart is src/0800D8F8.c.
 */
typedef struct {
    u16 values[160];
} ValueRow;

extern ValueRow *func_0800C614(void *object);
extern void func_0800C64C(void *object);
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_0800D9E0(void *object, u8 mode, u8 row, u8 index, u8 count,
                   const void *source)
{
    ValueRow *values = 0;

    switch (mode) {
    case 0:
        values = func_0800C614(object);
        break;
    case 1:
        values = func_0800C614(object) + row;
        break;
    case 2:
        values = func_0800C614(object) + row;
        break;
    }
    /* CpuCopy16-style control word: (byte size >> 1) & 0x1FFFFF, as in
     * src/0800DA88.c, the copy for the same object's halfword buffer. */
    func_0814186C(source, &values->values[index],
                  ((count * sizeof(u16)) >> 1) & 0x1FFFFF);
    func_0800C64C(object);
}
