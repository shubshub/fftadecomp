#ifndef FFTA_080D0F74_H
#define FFTA_080D0F74_H

#include "ffta.h"

typedef struct Node {
    u8 *record;
    struct Node *previous;
    struct Node *next;
} Node;

typedef struct {
    u8 unknown_00[0x28C8];
    Node *head;
} RecordState;

static inline u8 *find_record(const Node *head, u16 identifier)
{
    const Node *node;

    if (head == 0)
        return 0;
    node = head;
    do {
        u8 *record = node->record;

        if ((record[0] | ((record[1] & 3) << 8)) == identifier)
            return record;
        node = node->next;
    } while (node != 0);
    return 0;
}

#endif
