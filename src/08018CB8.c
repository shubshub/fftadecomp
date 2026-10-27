#include "ffta.h"

/* Complete [0x08018CB8, 0x08018CEC): 52 bytes, 26 instructions. */
u16 func_08018CB8(u8 *destination, s8 width)
{
    if (width == 0)
        return 0;

    destination[0] = '@';
    if (width < 0) {
        destination[1] = '<';
    } else {
        destination[1] = '>';
    }
    destination[2] = width < 0 ? -width : width;
    return 3;
}
