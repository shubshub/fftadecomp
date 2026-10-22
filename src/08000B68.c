#include "ffta.h"

typedef struct RequestNode {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    u32 first;
    u32 second;
    u32 control;
    u8 unknown_10[8];
    struct RequestNode *next;
} RequestNode;

void func_08000B68(RequestNode *entry, u32 first, u32 second, u16 count)
{
    RequestNode *head;

    entry->status = 0;
    entry->kind = 3;
    entry->first = first;
    entry->second = second;
    entry->control = 0x85000000 | count;
    entry->next = 0;
    head = *(RequestNode **)0x03002BCC;
    if (head == 0) {
        *(RequestNode **)0x03002BCC = entry;
    } else {
        RequestNode *tail = head;

        while (tail->next != 0) {
            tail = tail->next;
        }
        tail->next = entry;
    }
}
