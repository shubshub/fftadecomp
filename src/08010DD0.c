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

/* Unlinks a node from the list its `list` byte selects and clears its state.
 * The ROM has this operation out of line as func_08011428 (src/08011428.c)
 * and inlined in func_08010E64, func_08010F30 and func_08011484; here it is
 * inlined at 0x08010DE8-0x08010E42, starting from a copy of the node pointer
 * (adds r3, r4, #0 at 0x08010DE8).  It is a do { } while (0) statement macro,
 * the agbcc-era form of a multi-statement macro. */
#define REMOVE_NODE(input)                                  \
    do {                                                    \
        Node *removed = (input);                            \
        Node **head = 0;                                    \
        Node *previous;                                     \
        Node *next;                                         \
                                                            \
        switch (removed->list) {                            \
        case 0:                                             \
            head = &data_02009178;                          \
            break;                                          \
        case 1:                                             \
            head = &data_0200917C;                          \
            break;                                          \
        case 2:                                             \
            head = &data_02009174;                          \
            break;                                          \
        case 3:                                             \
            head = &data_02009180;                          \
            break;                                          \
        }                                                   \
        previous = removed->previous;                       \
        next = removed->next;                               \
        if (previous != 0)                                  \
            previous->next = next;                          \
        else                                                \
            *head = next;                                   \
        if (next != 0)                                      \
            next->previous = previous;                      \
        removed->state = 0;                                 \
    } while (0)

/* Complete [0x08010DD0, 0x08010E62): 146 bytes, 59 instructions. */
void func_08010DD0(void)
{
    Node *node = data_02009170.nodes;
    s32 remaining = data_02009170.count;

    do {
        if (node->state != 0) {
            if (func_08010AFC(node) == 0)
                REMOVE_NODE(node);
            if ((node->flags & 6) == 0)
                func_08010D2C(node);
        }
        node++;
    } while (--remaining > 0);
}
