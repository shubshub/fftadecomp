#include "ffta.h"

/* 0x08038D80..0x08038DCC: 76 bytes. */
extern u16 func_08018C24(u8 *, const u8 *);

void func_08038D80(u8 *buffer, const u8 *first, const u8 *second,
                   const u8 *third, const u8 *fourth, const u8 *fifth)
{
    buffer += func_08018C24(buffer, first);
    buffer += func_08018C24(buffer, second);
    buffer += func_08018C24(buffer, third);
    buffer += func_08018C24(buffer, fourth);
    func_08018C24(buffer, fifth);
}
