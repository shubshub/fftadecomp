/* func_080069F4 - 0x080069F4, 136 bytes (index span is truncated at 16 B)
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  f0b5 051c 0906 0f0e 0026 6879 fe28 37d0 fe28 02dc 0028 03d0 1fe0
 *           ff28 1bd0 1ce0 0024 be42 14da a968 a000 4018 0268 002a 0bd0 002a
 *           09db ec70 2006 000e e968 0919 [bl _call_via_r2] 701c 0006 060e 0134
 *           bc42 eadb ff20 e870 14e0 ae70 12e0 6879 441e a968 a000 4218 1068
 *           0028 0ad0 ec70 2006 000e e968 0919 1268 [bl _call_via_r2] 701c 0006
 *           060e 2e71 f0bc 01bc 0047
 *
 * The two call sites are agbcc's indirect-call thunk: `words[]` holds handler
 * addresses that this routine invokes, so `bl _call_via_r2` is a plain
 * function-pointer call and needs no target in the source.
 *
 * Three details decide the shape:
 *   - the selector at +0x05 is a switch on 0 / 0xFE / 0xFF with a default arm;
 *     0xFE falls straight through to the tail store, which is why its branch
 *     goes to the end rather than to a block;
 *   - the loop tests the loaded word twice (`!= 0`, then `>= 0`), which is what
 *     gives the `cmp/beq` + `cmp/blt` pair instead of a single `ble`;
 *   - the loop index is one function-scoped `int`, shared with the default
 *     arm's index, so both use the same callee-saved register.
 */

#include "ffta.h"

typedef void (*Callback)(u8 index, u8 *flag);

/* The list state.  `words` is the same slot func_08006ADC and func_08006AF8
 * write a plain u32 into, so it stays a u32 here; this routine reads a
 * non-negative word as a handler address. */
typedef struct {
    u8  unknown_00[2];
    u8  field_02;
    u8  field_03;
    u8  field_04;
    u8  field_05;
    u8  unknown_06[2];
    u32 *words;
    u8  *flags;
} List;

void func_080069F4(List *t, u8 n) {
    u8 count = 0;
    int i;

    switch (t->field_05) {
    case 0:
        for (i = 0; i < n; i++) {
            s32 cb = t->words[i];
            if (cb != 0) {
                if (cb >= 0) {
                    t->field_03 = i;
                    ((Callback)cb)(i, &t->flags[i]);
                    count++;
                }
            }
        }
        t->field_03 = 0xFF;
        break;
    case 0xFE:
        break;
    case 0xFF:
        t->field_02 = count;
        break;
    default:
        i = t->field_05 - 1;
        if (t->words[i] != 0) {
            t->field_03 = i;
            ((Callback)t->words[i])(i, &t->flags[i]);
            count++;
        }
        break;
    }
    t->field_04 = count;
}