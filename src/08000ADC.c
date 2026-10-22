#include "ffta.h"

typedef struct TransferRecord {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    const void *source;
    void *destination;
    u32 control;
    u8 unknown_10[8];
    struct TransferRecord *next;
} TransferRecord;

void func_08000ADC(TransferRecord *entry, const void *source, void *destination, u16 words)
{
    TransferRecord *head;

    entry->status = 0;
    entry->kind = 1;
    entry->source = source;
    entry->destination = destination;
    entry->control = 0x84000000 | words;
    entry->next = 0;

    head = *(TransferRecord **)0x03002BCC;
    if (head == 0) {
        *(TransferRecord **)0x03002BCC = entry;
    } else {
        TransferRecord *tail = head;

        while (tail->next != 0)
            tail = tail->next;
        tail->next = entry;
    }
}
