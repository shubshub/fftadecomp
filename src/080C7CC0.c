#include "object_list.h"

void func_080C7CC0(ListContext *context, ListCallback callback, void *payload)
{
    ListNode *current = context->head;

    while (current != 0) {
        if (callback(current, payload) == 0)
            break;
        current = current->next;
    }
}
