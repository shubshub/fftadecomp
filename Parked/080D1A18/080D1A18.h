#ifndef FFTA_080D1A18_H
#define FFTA_080D1A18_H

#include "ffta.h"

typedef struct {
    u8 identifier_low;
    u8 identifier_high;
    u8 unknown_02_0 : 2;
    u8 category : 3;
    u8 unknown_02_5 : 3;
    u8 unknown_03[13];
} SelectionRecord;

typedef struct Node {
    const SelectionRecord *data;
    struct Node *previous;
    struct Node *next;
} Node;

typedef struct {
    u8 unknown_00[0x28C8];
    Node *head;
    u8 unknown_28CC[0x135C];
    u16 selected_identifier;
} SelectionStateView;

extern u8 g_state_02000000[];

static inline u16 record_identifier(const SelectionRecord *record)
{
    return record->identifier_low | ((record->identifier_high & 3) << 8);
}

static inline u8 identifier_in_excluded_range(u16 identifier)
{
    return (u16)(identifier - 0x150) <= 0x16;
}

static inline Node *find_record_node(const SelectionRecord *record)
{
    Node *nodes = (Node *)0x020025C8;
    s32 index;

    for (index = 0; index < 64; index++) {
        if (nodes[index].data == record)
            return &nodes[index];
    }
    return 0;
}

static inline void remove_record(const SelectionRecord *record)
{
    Node *node = find_record_node(record);
    Node *previous = node->previous;
    Node *next;

    if (previous != 0) {
        next = node->next;
        previous->next = next;
        if (next != 0)
            next->previous = previous;
    } else {
        next = node->next;
        if (next != 0)
            next->previous = previous;
        ((SelectionStateView *)g_state_02000000)->head = next;
    }
    (*(void (**)(void *, s32))0x0836D4B8)((void *)node->data, 16);
    node->data = 0;
}

#endif
