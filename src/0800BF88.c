#include "ffta.h"

typedef struct Node0800BF88 {
    u8 unknown_00;
    u8 status;
    u8 unknown_02[0x22];
    struct Node0800BF88 *next;
} Node0800BF88;

typedef struct {
    Node0800BF88 *head;
    u8 unknown_04[0x24];
} List0800BF88;

extern List0800BF88 data_02009024[];

static inline Node0800BF88 *list_head(u8 index)
{
    return data_02009024[index].head;
}

void func_0800BF88(void)
{
    u16 index;

    for (index = 0; index < 2; index++) {
        Node0800BF88 *node = list_head(index);

        while (node != 0) {
            Node0800BF88 *next = node->next;

            if (node->status == 0)
                node->status = 2;
            node = next;
        }
    }
}
