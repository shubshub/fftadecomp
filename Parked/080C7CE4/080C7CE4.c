#include "ffta.h"

typedef struct ListNode ListNode;

struct ListNode {
    u8 unknown_00[8];
    ListNode *next;
};

typedef struct {
    u32 unknown_00;
    ListNode *head;
} NodeList;

typedef u32 (*NodeCallback)(ListNode *node, void *payload);

/* 080C7CE4..080C7D16: 50 bytes. */
void func_080C7CE4(NodeList *list, ListNode *start, NodeCallback callback,
                   void *payload)
{
    ListNode *node = start;

    while (callback(node, payload)) {
        node = node->next;
        if (node == 0)
            node = list->head;
        if (start == node)
            break;
    }
}
