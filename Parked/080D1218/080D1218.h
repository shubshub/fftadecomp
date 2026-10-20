#ifndef FFTA_080D1218_H
#define FFTA_080D1218_H

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
} State;

extern u8 g_state_02000000[];

static inline u16 record_identifier(const SelectionRecord *record)
{
    return record->identifier_low | ((record->identifier_high & 3) << 8);
}

static inline u8 identifier_in_excluded_range(u16 identifier)
{
    return (u16)(identifier - 0x150) <= 0x16;
}

static inline Node *find_excluded_record(void)
{
    Node *node = ((State *)g_state_02000000)->head;

    while (node != 0) {
        if (identifier_in_excluded_range(record_identifier(node->data)))
            return node;
        node = node->next;
    }
    return 0;
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

static inline SelectionRecord *find_free_record(void)
{
    SelectionRecord *records = (SelectionRecord *)0x020021C8;
    s32 index;

    for (index = 0; index < 64; index++) {
        if (record_identifier(&records[index]) == 0)
            return &records[index];
    }
    return 0;
}

static inline void remove_record(const SelectionRecord *record)
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
        ((State *)g_state_02000000)->head = next;
    }
    (*(void (**)(void *, s32))0x0836D4B8)((void *)node->data, 16);
    node->data = 0;
}

static inline void append_record(SelectionRecord *record, const SelectionRecord *source)
{
    Node *node;
    Node *tail;

    (*(void (**)(void *, const void *, s32))0x0836D4BC)(record, source, 16);
    node = find_record_node(0);
    tail = ((State *)g_state_02000000)->head;
    if (tail == 0) {
        ((State *)g_state_02000000)->head = node;
        node->data = record;
        node->next = tail;
    } else {
        while (tail->next != 0)
            tail = tail->next;
        tail->next = node;
        node->data = record;
        node->next = 0;
    }
    node->previous = tail;
}

#endif
