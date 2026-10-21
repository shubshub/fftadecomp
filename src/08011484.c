/* func_08011484 - 0x08011484, 120 bytes (ROM 0x08011484 .. 0x080114FC)
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *
 *   push {lr}
 *   adds r1, r0, #0        ; the node
 *   cmp r1, #0
 *   beq  return            ; a null node is left alone
 *   ldrb r0, [r1]          ; the state byte at +0x00
 *   cmp r0, #2
 *   bne  L_unlinked
 *   movs r0, #1            ; "is linked" as a 0/1 value
 *   b    L_test
 * L_unlinked:
 *   movs r0, #0
 * L_test:
 *   cmp r0, #0
 *   beq  return
 *   adds r2, r1, #0        ; the node, for the unlink
 *   movs r3, #0            ; the list head, 0 until the switch picks one
 *   ldrb r0, [r2, #0x1C]   ; the list selector
 *   ... the switch: four arms, each loading one list head ...
 *   ldr r1, [r2, #0x38]    ; prev
 *   ldr r0, [r2, #0x3C]    ; next
 *   cmp r1, #0
 *   beq  L_head
 *   str r0, [r1, #0x3C]    ; prev->next = next
 *   b    L_join
 * L_head:
 *   str r0, [r3]           ; *head = next
 * L_join:
 *   cmp r0, #0
 *   beq  L_done
 *   str r1, [r0, #0x38]    ; next->prev = prev
 * L_done:
 *   movs r0, #0
 *   strb r0, [r2]          ; the state byte is cleared
 *   b    L_epilogue
 * return:
 *   adds r0, r1, #0        ; a node that was not removed is returned as is
 * L_epilogue:
 *   pop {r1}
 *   bx r1
 *
 * Literal pool, interleaved with the switch arms (agbcc drains the pending
 * constant at the end of each arm):
 *   0x080114C0  0x02009178   case 0
 *   0x080114C8  0x0200917C   case 1
 *   0x080114D0  0x02009174   case 2
 *   0x080114E4  0x02009180   case 3
 *
 * What it does: unlinks the node from one of the four doubly linked lists
 * whose heads live at 0x02009174/78/7C/80 - the list is picked by the byte
 * at +0x1C - but only when the state byte at +0x00 is 2, and the state byte
 * is cleared afterwards.  A node that was not removed is returned unchanged
 * and a null node returns null, so the caller can tell whether the node is
 * still in its list.
 *
 * The state test at the top is the shape of an inlined predicate that returns
 * 1 or 0: agbcc materialises the two return values instead of branching on
 * the comparison, and the caller then tests the result.
 */

#include "ffta.h"

typedef struct ListNode ListNode;

struct ListNode {
    u8  field_00;           /* +0x00, the state byte: 2 while linked */
    u8  unknown_01[0x1B];   /* +0x01 .. +0x1B */
    u8  field_1C;           /* +0x1C, selects the list */
    u8  unknown_1D[0x1B];   /* +0x1D .. +0x37 */
    ListNode *prev;         /* +0x38 */
    ListNode *next;         /* +0x3C */
};

static inline u8 listnode_is_linked(const ListNode *node)
{
    if (node->field_00 == 2)
        return 1;
    return 0;
}

ListNode *func_08011484(ListNode *arg)
{
    ListNode *node = arg;

    if (node != 0 && listnode_is_linked(node)) {
        ListNode *item = node;
        ListNode **head = 0;
        ListNode *prev;
        ListNode *next;

        switch (item->field_1C) {
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
        prev = item->prev;
        next = item->next;
        if (prev != 0)
            prev->next = next;
        else
            *head = next;
        if (next != 0)
            next->prev = prev;
        item->field_00 = 0;
        return 0;
    }
    return node;
}
