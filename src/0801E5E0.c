/* func_0801E5E0 - 0x0801E5E0, 48 bytes (44 of code + one 4-byte literal pool)
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  10b5 0904 0024 094a 9084 2623 d05e 0b0c 0914 8842 01d0 d384
 *           0124 fbf7 43fc 002c 01d0 fff7 05fa 10bc 01bc 0047 407f 0002
 *   pool    02007f40
 *
 * Two arguments in, both 16-bit signed at the call sites (every caller
 * sign-extends r0 and r1 with `lsls #16; asrs #16` before the `bl`):
 * writes the first to +0x24 of the state block, and replaces the s16 at +0x26
 * when it differs, remembering that it did.
 *
 * The three trailing parameters are declared because the callers pass them:
 * the wrappers at 0x0801BD0E and 0x0801BD48 narrow r2/r3 and the first stack
 * word with `lsls/lsrs`, which is a `(u16)` and says the callee declares them
 * unsigned.  This body never reads them.
 *
 * Three build notes, all of them load-bearing:
 *
 *   - The state block is a *named global*, not the literal 0x02007F40.  With
 *     `(S *)0x02007F40` agbcc constant-folds the address and rewrites the
 *     `(s16)` load as `ldrh r0,[r2,#0x26]; lsls r0,r0,#16`, cancelling the
 *     common shift against the `(s16)b` side of the compare.  Reaching the
 *     block through a symbol leaves the address opaque, the sign extension
 *     survives as a real `ldrsh`, and the `asrs r1,r1,#16` on the argument
 *     stays.  That is the difference between 46 and 48 matching bytes.
 *
 *   - agbcc's Thumb backend has no `ldrsh` with a displacement, so every
 *     sign-extending halfword load in the ROM goes through an index register
 *     (207 of them, and not one uses the offset form).  Hence the `movs r3,
 *     #0x26` before `ldrsh r0, [r2, r3]` - it is the only shape that load has.
 *
 *   - `a` is a 32-bit parameter: the `strh r0, [r2, #0x24]` stores the incoming
 *     word unmasked.  A 16-bit parameter would draw a `lsls/lsrs` pair first.
 *
 * The address lives in config/data_symbols.json because the object keeps an
 * R_ARM_ABS32 for it; the address itself is the ROM's own pool word.
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[0x24];
    u16 field_24;
    s16 field_26;
} Struct02007F40;

extern Struct02007F40 g_state_02007F40;

void func_08019E84(void);
void func_0801DA10(void);

void func_0801E5E0(u32 a, s16 b, u16 c, u16 d, u16 e) {
    s32 changed = 0;

    g_state_02007F40.field_24 = a;
    if (g_state_02007F40.field_26 != b) {
        g_state_02007F40.field_26 = (u16)b;
        changed = 1;
    }
    func_08019E84();
    if (changed)
        func_0801DA10();
}