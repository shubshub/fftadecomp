#include "ffta.h"

/* Complete target: [0x080CB1F4, 0x080CB210), 28 bytes.
 * Target bytes: 00b500040021044a8018000cfb2800d80121081c02bc08470000ffff
 */
u8 func_080CB1F4(u16 identifier)
{
    u8 result = 0;
    u32 offset = (u16)(identifier - 1);

    if (offset <= 251)
        result = 1;
    return result;
}
