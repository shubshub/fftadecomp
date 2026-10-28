#include "ffta.h"

typedef struct ListNode {
    u8 unknown_00[8];
    struct ListNode *next;
} ListNode;

typedef struct {
    void *allocator;
    ListNode *head;
} List;

extern void func_080C7DC8(void *allocator, ListNode *node);
extern void func_08007170(void *allocator, void *allocation);

void func_080C79B4(List *list)
{
    void *allocator = list->allocator;
    ListNode *head = list->head;

    if (head) {
        if (head->next)
            func_080C7DC8(allocator, head->next);
        func_08007170(allocator, head);
    }
    list->head = 0;
}
