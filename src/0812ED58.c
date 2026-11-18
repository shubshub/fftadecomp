#include "ffta.h"

extern u8 func_080C8280(const void *unit);
extern u8 func_0812ED04(void *unit, u16 value);
extern void func_080CDDAC(void *unit, u8 enabled);
extern void func_080CDD40(void *unit, u8 enabled);

/* Complete target: [0x0812ED58, 0x0812ED98), 64 bytes, 27 instructions.
 * Target bytes: 10b5041c99f790fa0006002815d1201c4121fff7cbff0006002803d0201c01219ff718f8201c4021fff7c0ff0006002803d0201c01219ef7d7ff10bc01bc0047
 */
void func_0812ED58(void *unit)
{
    if (!func_080C8280(unit)) {
        if (func_0812ED04(unit, 0x41))
            func_080CDDAC(unit, 1);
        if (func_0812ED04(unit, 0x40))
            func_080CDD40(unit, 1);
    }
}
