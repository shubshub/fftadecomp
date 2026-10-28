#include "ffta.h"

/* 0x08038CF0..0x08038D0E: 30 bytes / 13 instructions. */
extern u16 func_08018C24(u8 *destination, const u8 *source);

void func_08038CF0(u8 *destination, const u8 *first, const u8 *second)
{
    destination += func_08018C24(destination, first);
    func_08018C24(destination, second);
}
