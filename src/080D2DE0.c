#include "ffta.h"

// Complete [0x080D2DE0, 0x080D2E22): 66 bytes, 29 instructions, two-word pool.
// 30b50004040c0348034940180068002806d112e000000002c8280000181c0de0021c0325
// 136819785878284000020843a042f3d09268002af4d1002030bc02bc0847

typedef struct {
    u16 id : 10;
    u16 unknown_0A : 6;
} __attribute__((packed)) Item;

typedef struct ItemNode {
    Item *item;
    u32 unknown_04;
    struct ItemNode *next;
} ItemNode;

typedef struct {
    u8 unknown_00[0x28C8];
    ItemNode *head;
} ItemListState;

extern ItemListState g_state_02000000;

Item *func_080D2DE0(u16 id)
{
    ItemNode *head = g_state_02000000.head;
    ItemNode *node;

    if (head == 0)
        return 0;
    for (node = head; node != 0; node = node->next) {
        Item *item = node->item;

        if (item->id == id)
            return item;
    }
    return 0;
}
