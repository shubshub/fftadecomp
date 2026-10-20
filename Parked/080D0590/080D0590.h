#ifndef FFTA_080D0590_H
#define FFTA_080D0590_H

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
    SelectionRecord *data;
    struct Node *previous;
    struct Node *next;
} Node;

static inline u16 record_identifier(const SelectionRecord *record)
{
    return record->identifier_low | ((record->identifier_high & 3) << 8);
}

static inline u8 identifier_in_excluded_range(u16 identifier)
{
    return (u16)(identifier - 0x150) <= 0x16;
}

static inline u8 output_contains(SelectionRecord **output, SelectionRecord *record)
{
    while (*output != 0) {
        if (*output++ == record)
            return 1;
    }
    return 0;
}

static inline u16 definition_flags(const u8 *definition)
{
    return definition[0x41] | (definition[0x42] << 8);
}

static inline u8 definition_filter(const u8 *definition)
{
    return (definition[3] >> 7) | ((definition[4] & 3) << 1);
}

#endif
