/* 0x0802ACA0 - 52 bytes (the index span ends at 0x0802ACB6, but the body
 * clearly runs on to `bx r0` at 0x0802ACD0; 0x0802ACD2 is the alignment pad
 * and 0x0802ACD4 starts the next function) - MATCH.
 *
 * Fills `count` consecutive u16 slots of `entries` with (first + i) OR'd with
 * (second << 12).  The three parameters are narrowed in the prologue, not in
 * the loop: `lsls/lsrs #16` on r1 and r3 and `lsls/lsrs #24` on r2, so they
 * are declared u16, u8, u16.  r6 holds `entries` because r0 is recycled for
 * the (u8)second mask before the loop and is clobbered by the index scale.
 *
 * There is no literal pool; every constant is immediate.
 *
 * Target bytes:
 *   70b5061c09040d0c1206100e1b041b0c00229a420ad2040350008019a9182143018050
 *   1c0004020c9a42f5d370bc01bc0047
 */

#include "ffta.h"

void func_0802ACA0(u16 *entries, u16 first, u8 second, u16 count)
{
    u16 i;

    for (i = 0; i < count; i++) {
        entries[i] = first + i | (second << 12);
    }
}