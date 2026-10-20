#ifndef FFTA_080D0ED4_H
#define FFTA_080D0ED4_H

#include "ffta.h"

typedef struct {
    u8 identifier_low;
    u8 identifier_high;
    u8 unknown_02_0 : 2;
    u8 category : 3;
    u8 unknown_02_5 : 3;
    u8 duration;
    u8 unknown_04[12];
} SelectionRecord;

typedef struct Node {
    u8 *data;
    struct Node *previous;
    struct Node *next;
} Node;

static inline Node *find_node(u8 *data)
{
    Node *node = (Node *)0x020025C8;
    s32 index;

    for (index = 0; index < 64; index++, node++) {
        if (node->data == data)
            return node;
    }
    return 0;
}

#endif
