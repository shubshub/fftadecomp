#ifndef FFTA_080CEF78_H
#define FFTA_080CEF78_H

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

static inline u16 record_identifier(const SelectionRecord *record)
{
    return record->identifier_low | ((record->identifier_high & 3) << 8);
}

static inline u8 identifier_in_excluded_range(u16 identifier)
{
    return (u16)(identifier - 0x150) <= 0x16;
}

#endif
