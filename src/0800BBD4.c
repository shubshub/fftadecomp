#include "ffta.h"

/* 0x0800BBD4..0x0800BC08: 52 bytes / 23 instructions. */
typedef struct ListNode {
    u8 unknown_00;
    u8 state;
    u8 unknown_02[0x22];
    struct ListNode *next;
} ListNode;

typedef struct {
    u8 unknown_00[0x24];
    ListNode *head;
} ListRecord;

extern ListRecord g_records_02009000[];

void func_0800BBD4(u8 index)
{
    ListNode *node = g_records_02009000[index].head;

    while (node != 0) {
        ListNode *next = node->next;

        if (node->state == 2)
            node->state = 0;
        node = next;
    }
}
