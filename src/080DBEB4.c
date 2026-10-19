/* func_080DBEB4 - 0x080DBEB4, 32 bytes
 *
 * The index span for this address is truncated: config/functions.json and
 * symbols/functions.txt both stop at 0x080DBEBE (10 bytes, 5 instructions),
 * but the function does not end there.  It runs on to 0x080DBED4, where the
 * next indexed function (func_080DBED4) begins.  The real body is:
 *
 *   target  00b5 021c 0906 0029 04d0 106b 0221 4942 0840 02e0
 *           106b 0121 0843 1063 01bc 0047
 *
 * It sets or clears bit 0 of the u32 at +0x30 of the object the first
 * argument points at, according to the u8 second argument:
 *
 *   flag != 0 : field_30 &= ~1
 *   flag == 0 : field_30 |= 1
 *
 * `movs r1, #2` + `rsbs r1, r1, #0` is the mask 0xFFFFFFFE, i.e. ~1 - not
 * ~2 - and `lsls r1, r1, #0x18` with no `lsrs #24` after it is the u8
 * narrowing of the flag, so the argument is an unsigned byte.
 *
 * All 33 call sites in the ROM load the object pointer into r0 and put a
 * plain 0 or 1 into r1, which is what the signature below says.
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[0x30];
    u32 field_30;
} Struct080DBEB4;

void func_080DBEB4(Struct080DBEB4 *state, u8 flag) {
    if (flag) {
        state->field_30 &= ~1;
    } else {
        state->field_30 |= 1;
    }
}
