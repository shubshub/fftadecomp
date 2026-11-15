#include "ffta.h"

/* 08011690..080116DC: complete 76-byte target, 38 instructions.
 * 10b5031c586800281cd05a681078002814d0918a0120084000280fd1182008400124
 * 002804d020200840002800d00024002c03d0d06b5860101c04e0d06b58600028e2d1
 * 002010bc02bc0847
 */
typedef struct ListNode {
    u8 active;
    u8 unknown_01[0x13];
    u16 flags;
    u8 unknown_16[0x26];
    struct ListNode *next;
} ListNode;

typedef struct ListIterator {
    u8 unknown_00[4];
    ListNode *current;
} ListIterator;

static inline s32 is_available(ListNode *node)
{
    if ((node->flags & 0x18) && (node->flags & 0x20))
        return 0;
    return 1;
}

ListNode *func_08011690(ListIterator *iterator)
{
    while (iterator->current) {
        ListNode *node = iterator->current;

        if (node->active && !(node->flags & 1) && is_available(node)) {
            iterator->current = node->next;
            return node;
        }
        iterator->current = node->next;
    }
    return 0;
}
