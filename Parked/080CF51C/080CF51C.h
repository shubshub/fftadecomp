#ifndef FFTA_080CF51C_H
#define FFTA_080CF51C_H

#include "ffta.h"

typedef struct Node {
    u8 *record;
    struct Node *previous;
    struct Node *next;
} Node;

extern u8 g_state_02000000[];

static inline void remove_record(u8 *data, Node **head)
{
    Node *found = 0;
    Node *candidate = (Node *)(g_state_02000000 + 0x25C8);
    Node *previous;
    Node *next;
    s32 index;

    for (index = 0; index < 64; index++, candidate++) {
        if (candidate->record == data) {
            found = candidate;
            break;
        }
    }
    previous = found->previous;
    next = found->next;
    if (previous != 0) {
        previous->next = next;
        if (next != 0)
            next->previous = previous;
    } else {
        if (next != 0)
            next->previous = previous;
        *head = next;
    }
    (*(void (**)(void *, u32))0x0836D4B8)(found->record, 16);
    found->record = 0;
}

#endif
