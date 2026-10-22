#ifndef FFTA_080D1E70_H
#define FFTA_080D1E70_H

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

extern u8 g_state_02000000[];

static inline u16 record_identifier(const u8 *record)
{
    return record[0] | ((record[1] & 3) << 8);
}

static inline Node *find_record_node(const u8 *record)
{
    Node *nodes = (Node *)0x020025C8;
    s32 index;

    for (index = 0; index < 64; index++) {
        if (nodes[index].record == record)
            return &nodes[index];
    }
    return 0;
}

static inline void remove_record(u8 *record)
{
    Node *node = find_record_node(record);
    Node *previous = node->previous;
    Node *next = node->next;

    if (previous != 0) {
        previous->next = next;
        if (next != 0)
            next->previous = previous;
    } else {
        if (next != 0)
            next->previous = previous;
        ((RecordState *)g_state_02000000)->head = next;
    }
    (*(void (**)(void *, s32))0x0836D4B8)(node->record, 16);
    node->record = 0;
}

#endif
