#include "ffta.h"

struct ListNode;

struct List {
    u8 flags;
    u8 unknown[0x1F];
    struct ListNode *head;
};

struct ListNode {
    u8 flags;
    u8 unknown[0x2B];
    struct List *owner;
    struct ListNode *previous;
    struct ListNode *next;
};

extern void func_081448DC(struct ListNode *node);

void func_081448FC(void *unused, struct List *list)
{
    struct ListNode *node = list->head;

    while (node != 0) {
        u8 flags = node->flags;

        if (flags & 0xC7)
            node->flags = flags | 0x40;
        func_081448DC(node);
        node = node->next;
    }
    list->flags = 0;
}
