/* 0x0809AA10 - 40 bytes (the index calls it 22: it stops at the `movs r0, #1`
 * at 0x0809AA26, but the `bne` at 0x0809AA24 targets 0x0809AA2A, so the body
 * runs on to the interworking return `pop {r1}; bx r1` at 0x0809AA34; the
 * next prologue is the `push {r4, r5, r6, lr}` at 0x0809AA38).
 *
 * Looks a pointer up in a two-entry list and says whether it is there.
 *
 * The list is the block the argument points at +0x80: its first entry sits
 * +0x40 from that base and every entry is 0x108 bytes, the layout
 * func_0809A9C0 indexes.  The pointer being searched for is the one the
 * argument holds at +0x00.  The answer is 1 when the pointer is the first or
 * the second entry of that list, and 0 when it is neither.
 *
 * There is no literal pool; every constant is immediate.  The 0x108 stride
 * does not fit a Thumb immediate, so it is built as `0x84 << 1`.
 *
 * Target bytes:
 *   00b5011c8031096800680022403184235b00814201d1012004e0c9180132012a
 *   f7dd002002bc0847
 */

#include "ffta.h"

typedef struct {
    u8 *unknown_00;
    u8 unknown_04[0x7C];
    u8 *unknown_80;
} SearchContext;

s32 func_0809AA10(SearchContext *p)
{
    u8 *cur = p->unknown_80;
    u8 *target = p->unknown_00;
    s32 i = 0;

    cur += 0x40;
    for (; i <= 1; i++) {
        if (cur == target)
            return 1;
        cur += 0x108;
    }
    return 0;
}
