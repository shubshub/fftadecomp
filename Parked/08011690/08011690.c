#include "ffta.h"

typedef struct ListNode {
    u8 enabled;
    u8 unknown_01[0x13];
    u16 flags;
    u8 unknown_16[0x26];
    struct ListNode *next;
} ListNode;

typedef struct ListIterator {
    u8 unknown_00[4];
    ListNode *current;
} ListIterator;

/* 08011690..080116DC: 76 bytes, 38 instructions. */
ListNode *func_08011690(ListIterator *iterator)
{
    while (iterator->current) {
        ListNode *node = iterator->current;

        if (node->enabled) {
            u16 flags = node->flags;

            if (!(flags & 1)) {
                u8 available = 1;

                if ((flags & 0x18) && (flags & 0x20))
                    available = 0;
                if (available) {
                    iterator->current = node->next;
                    return node;
                }
            }
        }
        iterator->current = node->next;
    }
    return 0;
}
