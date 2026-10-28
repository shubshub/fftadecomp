#include "ffta.h"

typedef struct Node {
    u16 state;
    u8 unknown_02[0x26];
    struct Node *next;
} Node;

typedef struct {
    u32 unknown_00;
    Node *head;
} List;

extern List data_03003C60;

/* Complete [0x081485AC, 0x081485D0): 36 bytes, 15 instructions. */
void func_081485AC(void)
{
    Node *node = data_03003C60.head;
    while (node != 0) {
        if (node->state == 2)
            node->state = 1;
        node = node->next;
    }
}
