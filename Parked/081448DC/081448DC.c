#include "ffta.h"

struct ListNode;

struct List {
    u8 unknown[0x20];
    struct ListNode *head;
};

struct ListNode {
    u8 unknown[0x2C];
    struct List *owner;
    struct ListNode *previous;
    struct ListNode *next;
};

void func_081448DC(struct ListNode *node)
{
    struct List *list = node->owner;
    struct ListNode *previous;
    struct ListNode *next;

    if (list == 0)
        return;

    previous = node->previous;
    next = node->next;
    if (previous != 0)
        previous->next = next;
    else
        list->head = next;
    if (next != 0)
        next->previous = previous;
    node->owner = 0;
}
