#ifndef FFTA_080D2300_H
#define FFTA_080D2300_H

#include "ffta.h"

typedef struct {
    u8 identifier_low;
    u8 identifier_high;
    u8 unknown_02[2];
    u8 first_index;
    u8 second_index;
    u8 unknown_06[10];
} SelectionRecord;

typedef struct Node {
    const SelectionRecord *record;
    struct Node *previous;
    struct Node *next;
} Node;

typedef struct {
    u8 unknown_00[0x28C8];
    Node *head;
} State;

extern u8 g_state_02000000[];

static inline const SelectionRecord *find_record(const Node *head, u16 identifier)
{
    const Node *node;

    if (head == 0)
        return 0;
    node = head;
    do {
        const SelectionRecord *record = node->record;

        if ((record->identifier_low | ((record->identifier_high & 3) << 8)) == identifier)
            return record;
        node = node->next;
    } while (node != 0);
    return 0;
}

#endif
