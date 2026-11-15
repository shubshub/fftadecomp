#include "ffta.h"

/* Complete target: [0x080D0ED4, 0x080D0F74), 160 bytes, five literal words.
 * 10b5041c0021fef71df92278607803210840000210434621484308494018021c4032107800280dd0
 * a1781d20404208400c210843a0701078e0702ae04cae55080c1c0ae000230949094a0868a042f7d0
 * 01330c313f2bf8dd00246068002809d0a168816000290dd048600be0c8250002b8d43608a1680029
 * 00d048600648074bc018016020681268102171f075f90020206010bc01bc004700000002c8280000
 */

typedef struct {
    u16 id : 10;
    u16 unknown_0A : 6;
    u8 unknown_flags_low : 2;
    u8 status : 3;
    u8 unknown_flags_high : 3;
    u8 unknown_03;
    u8 unknown_04[12];
} __attribute__((packed)) Item;

typedef struct {
    u8 unknown_00[0x40];
    u8 unknown_40;
    u8 unknown_41[5];
} __attribute__((packed)) ItemMetadata;

typedef struct ItemNode {
    Item *item;
    struct ItemNode *previous;
    struct ItemNode *next;
} ItemNode;

typedef struct {
    u8 unknown_00[0x25C8];
    ItemNode nodes[64];
    ItemNode *head;
} ItemListState;

extern ItemListState g_state_02000000;
extern const ItemMetadata g_table_0855AE4C[];
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern void func_080CF118(Item *item, u8 enabled);

static inline ItemNode *find_node(Item *item)
{
    ItemNode *node;
    s32 i;

    for (i = 0, node = g_state_02000000.nodes; i < 64; i++, node++) {
        if (node->item == item)
            return node;
    }
    return 0;
}

void func_080D0ED4(Item *item)
{
    const ItemMetadata *metadata;

    func_080CF118(item, 0);
    metadata = &g_table_0855AE4C[item->id];
    if (metadata->unknown_40 != 0) {
        item->status = 3;
        item->unknown_03 = metadata->unknown_40;
    } else {
        ItemNode *node = find_node(item);
        ItemNode *previous = node->previous;
        ItemNode *next;

        if (previous != 0) {
            next = node->next;
            previous->next = next;
            if (next != 0)
                next->previous = previous;
        } else {
            next = node->next;
            if (next != 0)
                next->previous = previous;
            g_state_02000000.head = next;
        }
        g_callbacks_0836D4B8[0](node->item, sizeof(*node->item));
        node->item = 0;
    }
}
