#include "ffta.h"

typedef struct ListNode {
    u8 unknown_00[8];
    struct ListNode *next;
} ListNode;

typedef struct {
    u8 unknown_00[4];
    ListNode *head;
} ListContext;

typedef u32 (*ListCallback)(ListNode *node, void *payload);

void func_080C7CC0(ListContext *context, ListCallback callback, void *payload)
{
    ListNode *current = context->head;

    while (current != 0) {
        if (callback(current, payload) == 0)
            break;
        current = current->next;
    }
}
