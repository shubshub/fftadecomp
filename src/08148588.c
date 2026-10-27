#include "ffta.h"

/* 0x08148588..0x081485AC: 36 bytes. */
typedef struct StateNode {
    u16 status;
    u8 unknown_02[0x26];
    struct StateNode *next;
} StateNode;

typedef struct {
    u32 unknown_00;
    StateNode *head;
} StateList;

extern StateList data_03003C60;

void func_08148588(void)
{
    StateNode *node = data_03003C60.head;

    while (node != 0) {
        if (node->status == 1)
            node->status = 2;
        node = node->next;
    }
}
