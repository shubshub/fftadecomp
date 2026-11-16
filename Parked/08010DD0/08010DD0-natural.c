#include "ffta.h"

// 0x08010DD0..0x08010E62: 146 bytes, 59 instructions.

typedef struct Node {
    u8 state;
    u8 unknown_01[0x13];
    u16 flags;
    u8 unknown_16[6];
    u8 list;
    u8 unknown_1D[0x1B];
    struct Node *previous;
    struct Node *next;
} Node;

typedef struct {
    u16 count;
    u8 unknown_02[0x12];
    Node *nodes;
} State;

extern State data_02009170;
extern Node *data_02009174[4];
extern u32 func_08010AFC(Node *node);
extern void func_08010D2C(Node *node);

static inline void remove_node(Node *input)
{
    Node *node = input;
    Node **head = 0;
    Node *previous;
    Node *next;

    switch (node->list) {
    case 0:
        head = &data_02009174[1];
        break;
    case 1:
        head = &data_02009174[2];
        break;
    case 2:
        head = &data_02009174[0];
        break;
    case 3:
        head = &data_02009174[3];
        break;
    }
    previous = node->previous;
    next = node->next;
    if (previous)
        previous->next = next;
    else
        *head = next;
    if (next)
        next->previous = previous;
    node->state = 0;
}

void func_08010DD0(void)
{
    Node *node = data_02009170.nodes;
    s32 remaining = data_02009170.count;

    do {
        if (node->state != 0) {
            if (func_08010AFC(node) == 0)
                remove_node(node);
            if ((node->flags & 6) == 0)
                func_08010D2C(node);
        }
        node++;
    } while (--remaining > 0);
}
