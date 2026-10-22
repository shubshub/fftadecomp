#include "ffta.h"

typedef struct ExtendedRequestNode {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    u32 first;
    u32 second;
    u32 control;
    u16 field_10;
    u16 field_12;
    u16 field_14;
    u8 unknown_16[2];
    struct ExtendedRequestNode *next;
} ExtendedRequestNode;

void func_08000BAC(ExtendedRequestNode *entry, u32 first, u32 second,
                   u16 count, u16 field_10, u16 field_12, u16 field_14)
{
    ExtendedRequestNode *head;

    entry->status = 1;
    entry->kind = 1;
    entry->first = first;
    entry->second = second;
    entry->control = 0x80000000 | count;
    entry->field_10 = field_10;
    entry->field_12 = field_12;
    entry->field_14 = field_14;
    entry->next = 0;
    head = *(ExtendedRequestNode **)0x03002BCC;
    if (head == 0) {
        *(ExtendedRequestNode **)0x03002BCC = entry;
    } else {
        ExtendedRequestNode *tail = head;

        while (tail->next != 0) {
            tail = tail->next;
        }
        tail->next = entry;
    }
}
