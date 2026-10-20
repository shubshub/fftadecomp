#ifndef FFTA_080CE8A8_H
#define FFTA_080CE8A8_H

#include "ffta.h"

typedef struct CategoryNode {
    const u8 *data;
    u8 unknown_04[4];
    const struct CategoryNode *next;
} CategoryNode;

typedef struct {
    u8 unknown_00[0x28C8];
    const CategoryNode *head;
} CategoryState;

extern u8 g_state_02000000[];

static inline u8 contains_category(const CategoryNode *node, u16 category)
{
    while (node != 0) {
        if ((node->data[0] | ((node->data[1] & 3) << 8)) == category)
            return 1;
        node = node->next;
    }
    return 0;
}

#endif
