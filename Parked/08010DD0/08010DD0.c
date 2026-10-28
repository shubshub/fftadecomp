#include "ffta.h"

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
extern Node *data_02009178;
extern Node *data_0200917C;
extern Node *data_02009174;
extern Node *data_02009180;
extern u32 func_08010AFC(Node *node);
extern void func_08010D2C(Node *node);

static inline Node **get_head(const Node *node)
{
    Node **head = 0;

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

static inline void remove_node(Node *node, Node **head)
{
    Node *previous = node->previous;
    Node *next = node->next;
    if (previous != 0)
        previous->next = next;
    else
        *head = next;
    if (next != 0)
        next->previous = previous;
    node->state = 0;
}

/* Complete [0x08010DD0, 0x08010E62): 146 bytes, 59 instructions. */
void func_08010DD0(void)
{
    Node *node = data_02009170.nodes;
    s32 remaining = data_02009170.count;

    do {
        if (node->state != 0) {
            if (func_08010AFC(node) == 0)
                remove_node(node, get_head(node));
            if ((node->flags & 6) == 0)
                func_08010D2C(node);
        }
        node++;
    } while (--remaining > 0);
}
