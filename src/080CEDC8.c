#include "ffta.h"

/* Complete target: [0x080CEDC8, 0x080CEECC), 260 bytes, 109 instructions,
 * eight literal words in two pools.
 * f0b5071c024803494018056805e0000000000002c8280000ad68a8680028fbd16b68002b14d02a68
 * 91781c200840161c00280bd11c241d1c6b68002b08d02a689178201c0840161c0028f4d0002b03d1
 * 002054e0141c20e0a8689860a968002901d0686848601d4c2268301c102173f009fa2268281c0c21
 * 73f004fa0023184a0324117850782040000208430028e1d0013310323f2bf4dd002412480368201c
 * 391c102273f0f0f900220f490868002804d001320c313f2af8dd00210b480c4bc2181068002815d0
 * 0c60002048601068886010684160116010e00000b8d43608c8210002bcd43608c825000200000002
 * c828000011600c60886048600120f0bc02bc0847
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

/* The links and the list head are one pointer type: the ROM reads the head
 * again after each link store (080CEE96, 080CEE9A). */
typedef struct ItemNode ItemNode;

struct ItemNode {
    Item *item;
    ItemNode *previous;
    ItemNode *next;
};

/* The 64 items and their 64 list nodes sit back to back in front of the head
 * word; func_080D2E24 (src/080D2E24.c) clears them as 0x400 and 0x300 bytes. */
typedef struct {
    u8 unknown_00[0x21C8];
    Item items[64];
    ItemNode nodes[64];
    ItemNode *head;
} ItemListState;

extern ItemListState g_state_02000000;
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern void (*data_0836D4BC)(void *destination, const void *source, u32 size);

/* The first item whose id is zero.  The only caller, func_080CFCD0, holds the
 * same search at 080D017E. */
static inline Item *find_free_item(void)
{
    Item *item;
    s32 i;

    for (i = 0, item = g_state_02000000.items; i < 64; i++, item++) {
        if (item->id == 0)
            return item;
    }
    return 0;
}

/* The node search of func_080D0ED4 (src/080D0ED4.c). */
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

u32 func_080CEDC8(const Item *source)
{
    ItemNode *node;
    ItemNode *previous;
    ItemNode *free_node;
    Item *free_item;

    for (node = g_state_02000000.head; node->next != 0; node = node->next)
        ;
    previous = node->previous;
    while (previous != 0) {
        if (node->item->status != 0)
            break;
        node = previous;
        previous = node->previous;
    }
    if (previous == 0)
        return 0;
    previous->next = node->next;
    if (node->next != 0)
        node->next->previous = node->previous;
    g_callbacks_0836D4B8[0](node->item, sizeof(*node->item));
    g_callbacks_0836D4B8[0](node, sizeof(*node));

    free_item = find_free_item();
    data_0836D4BC(free_item, source, sizeof(*free_item));
    free_node = find_node(0);
    if (g_state_02000000.head != 0) {
        free_node->item = free_item;
        free_node->previous = 0;
        free_node->next = g_state_02000000.head;
        g_state_02000000.head->previous = free_node;
        g_state_02000000.head = free_node;
    } else {
        g_state_02000000.head = free_node;
        free_node->item = free_item;
        free_node->next = 0;
        free_node->previous = 0;
    }
    return 1;
}
