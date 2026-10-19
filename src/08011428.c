/* func_08011428 - 0x08011428
 *
 * Target bytes (92 bytes, ROM 0x08011428 .. 0x08011484):
 *
 *   00b5 021c 0023 107f 0128 0dd0 0128 02dc 0028 05d0 11e0 0228 0ad0
 *   0328 0cd0 0ce0 004b 0ae0 [7891 0002] 004b 06e0 [7c91 0002] 004b 02e0
 *   [7491 0002] 034b 916b d06b 0029 04d0 c863 03e0 [0000 8091] 1860 0028
 *   00d0 8163 0020 1070 01bc 0047
 *
 *   literal pool, interleaved (not trailing):
 *     0x0801144C 0x02009178     case 0
 *     0x08011454 0x0200917C     case 1
 *     0x0801145C 0x02009174     case 2
 *     0x08011470 0x02009180     case 3
 *
 * Two things about the index, both worth knowing before re-deriving this:
 *
 *  - symbols/functions.txt records 0x08011428..0x08011434 (12 bytes, 6
 *    instructions).  That span is truncated: the body runs on to the
 *    interwork return at 0x08011484, so the function is 92 bytes.  match.py
 *    sizes from the compiled ELF symbol, so the whole 92 bytes are compared.
 *    The nearest sibling, 0x08011484, is not indexed at all.
 *
 *  - agbcc emits this function's literal pool *between* the switch arms and
 *    between the unlink's two branches rather than at the end of the
 *    function.  match.py's leaf verifier rejects any PC-relative literal read
 *    below the end of the last instruction ("literal read is outside the
 *    function's trailing pool"), so it cannot confirm this function even
 *    though the compile is byte identical.  The rest of the CFG verifies:
 *    37 reachable instructions, no calls, every path to pop {r0}; bx r0.
 *
 * What it does: unlinks a node from one of four doubly linked lists whose
 * heads live at 0x02009174/78/7C/80, picked by the byte at +0x1C, then
 * clears +0x00.
 *
 * The head is only overwritten when the node has no predecessor - that is
 * the `b 0x08011476` in the middle of the unlink, which jumps *past* the
 * `str r0, [r3]`.  Removing a middle or tail node updates the predecessor
 * instead, and the head is untouched.  The successor's back pointer is fixed
 * up either way.  Those are what puts the pool at 0x08011470: the then-arm
 * ends in a branch, so agbcc drains the pending constant before the label.
 */

#include "ffta.h"

typedef struct ListNode ListNode;

struct ListNode {
    u8  field_00;           /* +0x00, cleared on removal */
    u8  unknown_01[0x1B];   /* +0x01 .. +0x1B */
    u8  field_1C;           /* +0x1C, selects the list */
    u8  unknown_1D[0x1B];   /* +0x1D .. +0x37 */
    ListNode *prev;         /* +0x38 */
    ListNode *next;         /* +0x3C */
};

void func_08011428(ListNode *node)
{
    ListNode **head = 0;
    ListNode *prev;
    ListNode *next;

    switch (node->field_1C) {
    case 0:
        head = (ListNode **)0x02009178;
        break;
    case 1:
        head = (ListNode **)0x0200917C;
        break;
    case 2:
        head = (ListNode **)0x02009174;
        break;
    case 3:
        head = (ListNode **)0x02009180;
        break;
    }

    prev = node->prev;
    next = node->next;
    if (prev != 0)
        prev->next = next;
    else
        *head = next;
    if (next != 0)
        next->prev = prev;
    node->field_00 = 0;
}