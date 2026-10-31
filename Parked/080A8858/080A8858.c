#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u32 unknown_10;
} Entry080A8858;

/* Complete [0x080A8858, 0x080A88DE): 134 bytes, 48 instructions.
 * Target bytes:
 * 00b5021c0906080e072839d880000249401800688746000074880a0894880a08
 * ba880a08d8880a08a2880a08aa880a08b2880a08c2880a08ca880a0810698021
 * c9010840002819d11ae0106980218901f7e7106980214901f3e710698021c900
 * efe7106980218900ebe7106980214900e7e7106980210840002801d0012000e0
 * 002002bc0847
 */
u8 func_080A8858(const Entry080A8858 *entry, u8 selector)
{
    switch (selector) {
    case 0:
        if (entry->unknown_10 & 0x4000)
            return 1;
        break;
    case 1:
        if (entry->unknown_10 & 0x200)
            return 1;
        break;
    case 3:
        if (entry->unknown_10 & 0x2000)
            return 1;
        break;
    case 4:
        if (entry->unknown_10 & 0x1000)
            return 1;
        break;
    case 5:
        if (entry->unknown_10 & 0x400)
            return 1;
        break;
    case 6:
        if (entry->unknown_10 & 0x100)
            return 1;
        break;
    case 7:
        if (entry->unknown_10 & 0x80)
            return 1;
        break;
    }
    return 0;
}
