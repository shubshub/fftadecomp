#include "ffta.h"

extern u8 func_080CDA7C(const void *object);
extern s32 func_080C7EA4(const void *object, u32 selector);
extern u32 func_08002804(void);

/* Complete [0x081303AC, 0x081303FA): 78 bytes, 35 instructions.
 * 30b5041c9df764fb0006201c142197f773fd0004000c00040014002800da0730
 * 4003050cd2f618fa2c042414053c000400140b2112f0b6fa24182404250c002c
 * 00dc01252804001430bc02bc0847
 *
 * Returns the object's selector-0x14 value divided by 8, offset by
 * (s16)random % 11 - 5 and clamped to at least 1, the formula of the
 * matched neighbour src/081303FC.c (selector 0x16 plus func_0812F704,
 * divided by 16).  func_0809ED38 subtracts the result from the unit's
 * hp as damage.
 */
s16 func_081303AC(const void *object)
{
    u16 base;
    s16 value;
    u32 random;

    /* Both arms read selector 0x14, and the ROM keeps the test's
     * instructions: the u8 narrowing of func_080CDA7C's result (lsls #24
     * at 0x081303B4), which the ROM's seven other calls of it follow with
     * a compare and a branch, and the arm's u16 truncation of base (lsls
     * and lsrs #16 at 0x081303BE) apart from its s16 extension at
     * 0x081303C2.  The compiler merged the arms after register allocation
     * and dropped the compare and branch but not the narrowing.  Without
     * the test the function is 72 bytes, exactly those three instructions
     * short. */
    if (func_080CDA7C(object))
        base = func_080C7EA4(object, 0x14);
    else
        base = func_080C7EA4(object, 0x14);
    value = (s16)base / 8;
    random = func_08002804();
    value += (s16)random % 11 - 5;
    if (value <= 0)
        value = 1;
    return value;
}
