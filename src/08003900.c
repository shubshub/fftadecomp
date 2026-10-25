/* 0x08003900 - 24 bytes
 * Target: 0004 000c 024a 1170 0249 0880 7047 0000 d1340003 d2340003
 */
#include "ffta.h"

u16 func_08003900(u16 value, u32 mode)
{
    *(u8 *)0x030034D1 = mode;
    *(u16 *)0x030034D2 = value;
    return value;
}
