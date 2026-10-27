#include "ffta.h"

extern u8 data_0200216A[][2];
extern u16 func_08018CB8(u8 *destination, s8 width);
extern u16 func_08018ABC(u8 *destination, u32 value);

/* Complete [0x08019398, 0x080193CC): 52 bytes, 22 instructions. */
u32 func_08019398(u8 *destination, u8 index)
{
    u8 *cursor = destination;
    u8 *entry = data_0200216A[index];

    if (entry[0] < 10)
        cursor += func_08018CB8(cursor, 8);
    func_08018ABC(cursor, entry[0]);

    return 0;
}
