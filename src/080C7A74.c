/* func_080C7A74 - 0x080C7A74, 62 bytes - MATCH
 *
 * Appends a freshly allocated node to the list the context owns and returns
 * that node:
 *
 *   30b5 051c 0c1c 2868 0c21 3ff75bfb 021c 1460
 *   0020 9060 5060 6868 0028 01d1 6a60 09e0
 *   011c 00e0 8968 8868 0028 fbd1 8a60 5160
 *   0020 9060 101c 30bc 02bc 0847
 *
 * A node holds the caller's object at +0x00, the node it sits behind at
 * +0x04 and the node after it at +0x08.  The context holds the allocation
 * block at +0x00 and the first node at +0x04, so an empty list takes the new
 * node as its head and a populated one is walked to its last node, which then
 * points at the new node.
 *
 * func_080C7CC0 walks the same list through the +0x08 link, and func_080C7BF4
 * searches it by comparing the +0x00 field.
 *
 * func_08007138 is the allocator: it takes the block and the node size and
 * hands back the node itself.
 */

#include "ffta.h"

void *func_08007138(void *owner, u32 size);

typedef struct ListNode {
    void *value;             /* +0x00 */
    struct ListNode *prev;   /* +0x04 */
    struct ListNode *next;   /* +0x08 */
} ListNode;

typedef struct {
    void *owner;             /* +0x00 */
    ListNode *head;          /* +0x04 */
} ListContext;

ListNode *func_080C7A74(ListContext *context, void *value)
{
    ListNode *node = func_08007138(context->owner, 12);

    node->value = value;
    node->next = 0;
    node->prev = 0;

    if (context->head == 0) {
        context->head = node;
    } else {
        ListNode *last = context->head;

        while (last->next != 0)
            last = last->next;

        last->next = node;
        node->prev = last;
        node->next = 0;
    }
    return node;
}
