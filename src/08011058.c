/* func_08011058 - 0x08011058, 0x74 bytes (the index span of 22 is truncated:
 * the `beq` at +0x14 targets the shared epilogue at +0x6E, so the body runs
 * to `bx r0` at +0x72).
 *
 *   push {r4, lr}
 *   lsls r1, r1, #16      (u16) parameter narrowing
 *   adds r3, r0, #0       item
 *   adds r2, r3, #0       &item->value_30
 *   adds r2, #0x30
 *   movs r0, #0
 *   ldrsb r0, [r2, r0]    s8 field at +0x30
 *   lsrs r4, r1, #16      unsigned half of the parameter, for the byte store
 *   asrs r1, r1, #16      signed half, for the comparison
 *   cmp r0, r1
 *   beq  epilogue         unchanged -> nothing to do
 *   strb r4, [r2]         item->value_30 = value
 *   movs r2, #0           slot = 0 (the switch default)
 *   ldrb r0, [r3, #0x1c]  switch on the byte at +0x1C, four cases, each
 *                          loading the address of that list's tail slot
 *   ldr r1, [r3, #0x38]   next
 *   ldr r0, [r3, #0x3c]   prev
 *   ...unlink...
 *   bl   func_080105C4
 *   pop {r4}; pop {r0}; bx r0
 *
 * Literal pool (agbcc flushes it after each basic block here, so the words
 * are interleaved with the code rather than trailing it):
 *   +0x38  0x02009178   case 0
 *   +0x40  0x0200917C   case 1
 *   +0x48  0x02009174   case 2
 *   +0x5C  0x02009180   case 3
 */

#include "ffta.h"

typedef struct Struct08011058 {
    u8 unknown_00[0x1C];
    u8 kind;                 /* +0x1C - picks which list this item belongs to */
    u8 unknown_1D[0x13];
    s8 value_30;             /* +0x30 */
    u8 unknown_31[7];
    struct Struct08011058 *next;  /* +0x38 */
    struct Struct08011058 *prev;  /* +0x3C */
} Struct08011058;

void func_080105C4(Struct08011058 *item);

void func_08011058(Struct08011058 *arg, s16 value)
{
    Struct08011058 *item = arg;
    Struct08011058 *next;
    Struct08011058 *prev;
    u32 *slot;

    if (item->value_30 != value) {
        item->value_30 = value;
        slot = 0;

        switch (item->kind) {
        case 0:
            slot = (u32 *)0x02009178;
            break;
        case 1:
            slot = (u32 *)0x0200917C;
            break;
        case 2:
            slot = (u32 *)0x02009174;
            break;
        case 3:
            slot = (u32 *)0x02009180;
            break;
        }

        next = item->next;
        prev = item->prev;

        if (next != 0)
            next->prev = prev;
        else
            *slot = prev;

        if (prev != 0)
            prev->next = next;

        func_080105C4(item);
    }
}