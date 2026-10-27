#include "ffta.h"

extern u16 func_08018C24(u8 *destination, const u8 *text);

/* Complete [0x08038D40, 0x08038D7E): 62 bytes, 27 instructions. */
void func_08038D40(u8 *destination, const u8 *first, const u8 *second,
                   const u8 *third, const u8 *fourth)
{
    destination += func_08018C24(destination, first);
    destination += func_08018C24(destination, second);
    destination += func_08018C24(destination, third);
    func_08018C24(destination, fourth);
}
