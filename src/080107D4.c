#include "ffta.h"

typedef struct Node080107D4 {
    u8 unknown_00[0x14];
    u16 flags;
    u8 unknown_16[6];
    u8 list;
    u8 mode;
    u16 base;
    u16 unknown_20;
    u16 offset;
    u8 unknown_24[10];
    s16 sort_key;
    s8 priority;
    u8 unknown_31[7];
    struct Node080107D4 *previous;
    struct Node080107D4 *next;
} Node080107D4;

extern Node080107D4 *data_02009178;
extern Node080107D4 *data_0200917C;
extern Node080107D4 *data_02009174;
extern Node080107D4 *data_02009180;

static inline u8 uses_priority_only(Node080107D4 *node)
{
    if (node->mode == 0)
        return 1;
    if (node->mode == 1)
        return 1;
    if (node->flags & 0x80)
        return 1;
    return 0;
}

static inline Node080107D4 **get_head(Node080107D4 *node)
{
    Node080107D4 **head = 0;

    switch (node->list) {
    case 0:
        head = &data_02009178;
        break;
    case 1:
        head = &data_0200917C;
        break;
    case 2:
        head = &data_02009174;
        break;
    case 3:
        head = &data_02009180;
        break;
    }
    return head;
}

static inline void unlink_node(Node080107D4 *node)
{
    Node080107D4 **head = get_head(node);
    Node080107D4 *previous = node->previous;
    Node080107D4 *next = node->next;

    if (previous)
        previous->next = next;
    else
        *head = next;
    if (next)
        next->previous = previous;
}

extern void func_080105C4(Node080107D4 *node);

/* Target: complete [0x080107D4, 0x08010884), 176 bytes. */
void func_080107D4(void *object, u16 base, u16 value, u16 offset)
{
    Node080107D4 *node = object;
    u8 changed = 0;

    if ((s16)base != (s16)node->base ||
        (s16)offset != (s16)node->offset)
        changed = 1;
    node->base = base;
    node->unknown_20 = value;
    node->offset = offset;

    if (!uses_priority_only(node) && changed) {
        unlink_node(node);
        func_080105C4(node);
    }
}
