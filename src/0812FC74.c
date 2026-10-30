#include "ffta.h"

/* Complete [0x0812FC74, 0x0812FD42): 206 bytes, 22 instructions.
 * 00b50004000c013826285dd880000249401800688746000090fc12082cfd1208
 * 30fd120834fd120838fd12083cfd12082cfd120830fd120834fd120838fd1208
 * 3cfd12082cfd120830fd120834fd120838fd12083cfd12082cfd120830fd1208
 * 34fd120838fd12083cfd12082cfd120830fd120834fd120838fd12083cfd1208
 * 2cfd120830fd120834fd120838fd12083cfd12082cfd120830fd120834fd1208
 * 38fd12083cfd12082cfd120830fd120834fd120838fd1208032006e0022004e0
 * 042002e0002000e0012002bc0847
 */
u32 func_0812FC74(u16 selector)
{
    switch (selector) {
    case 1:
    case 6:
    case 11:
    case 16:
    case 21:
    case 26:
    case 31:
    case 36:
        return 3;
    case 2:
    case 7:
    case 12:
    case 17:
    case 22:
    case 27:
    case 32:
    case 37:
        return 2;
    case 3:
    case 8:
    case 13:
    case 18:
    case 23:
    case 28:
    case 33:
    case 38:
        return 4;
    case 4:
    case 9:
    case 14:
    case 19:
    case 24:
    case 29:
    case 34:
    case 39:
        return 0;
    default:
        return 1;
    }
}
