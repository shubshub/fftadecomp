#include "ffta.h"

struct ResourceTable0800C15C;

extern u32 func_0800AEA0(const struct ResourceTable0800C15C *table);
extern void func_0800ACA8(const struct ResourceTable0800C15C *table, s16 index,
                        u16 *first, u16 *second, u16 *third, u16 *fourth);
extern void func_0800ADD8(const struct ResourceTable0800C15C *table, u16 index,
                        u32 *offset, u16 *first, u16 *second,
                        u16 *third, u16 *fourth);

/* Target: 0x0800C15C..0x0800C1AC, 80 bytes / 35 instructions. */
void func_0800C15C(const struct ResourceTable0800C15C *table,
                   u16 *first, u16 *second)
{
    u16 entry;
    u8 index = func_0800AEA0(table);

    func_0800ACA8(table, index, &entry, 0, 0, 0);
    func_0800ADD8(table, entry & 0x3FFF, 0, first, second, 0, 0);
}
