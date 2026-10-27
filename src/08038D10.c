#include "ffta.h"

extern u16 func_08018C24(u8 *destination, const u8 *text);

/* Complete [0x08038D10, 0x08038D3E): 46 bytes, 20 instructions. */
void func_08038D10(u8 *destination, const u8 *first,
                   const u8 *second, const u8 *third)
{
    destination += func_08018C24(destination, first);
    destination += func_08018C24(destination, second);
    func_08018C24(destination, third);
}
