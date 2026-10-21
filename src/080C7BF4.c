/* func_080C7BF4 - 0x080C7BF4, 30 bytes - MATCH
 *
 * Linear search over the list the context owns.  The list head sits at
 * +0x04; every node keeps its key at +0x00, its value at +0x04 and the next
 * node at +0x08.  The node whose key matches is returned, and a list that
 * runs out gives 0.
 */

#include "ffta.h"

typedef struct ListNode {
    u32 key;
    u32 value;
    struct ListNode *next;
} ListNode;

typedef struct {
    u8 unknown_00[4];
    ListNode *head;
} ListContext;

ListNode *func_080C7BF4(ListContext *context, u32 key)
{
    ListNode *node = context->head;

    while (node != 0) {
        if (key == node->key)
            return node;
        node = node->next;
    }

    return 0;
}
