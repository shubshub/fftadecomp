#include "ffta.h"

typedef struct ListNode {
    u8 unknown_00[8];
    struct ListNode *next;
} ListNode;

typedef struct {
    u8 unknown_00[4];
    ListNode *head;
} List;

u32 func_080C7B08(List *list)
{
    ListNode *node = list->head;
    u32 count = 0;

    while (node) {
        node = node->next;
        count++;
    }
    return count;
}
