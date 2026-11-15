#include "ffta.h"

/* Complete [0x080CF51C, 0x080CF68E): 370 bytes, 156 instructions, nine literal
 * words in three pools.
 * f0b5fff7c3f9041cfff702fc2404000484420ad1224c201cfaf704f80006002803d1201c0121
 * faf717f896208000f9f7f9ff000600280ad01a4c201cf9f7f2ff0006002803d0201c0121faf7
 * 05f81648164940180168002900d187e00e1c071c3468227860780321084000021043462141430f
 * 480d18e078011cff2903d0002904d00138e070e07800286bd1a078c006400f02280edc012818da
 * 00280dd061e0ae0500008c04000000000002c82800004cae5508032831d054e0201cfff742fd
 * 002803d1201c0021fff798fd2a1c4032107800280cd0a1781d235b42181c01400c200143a170
 * 1078e0703be00c1c0ae000230749074a0868a042f7d001330c313f2bf8dd00246168002915d1
 * 1ee00000c8250002b8d436080c1c0ae000230949094a0868a042f7d001330c313f2bf8dd0024
 * 6168002909d0a068886000280ad0416008e0c8250002b8d43608a068002800d0416038602068
 * 1268102172f0e8fd00202060b668002e00d079e7f0bc01bc0047
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
extern u16 func_080CE8A8(void);
extern u16 func_080CED2C(void);
extern u8 func_080C9540(u16 bitIndex);
extern void func_080C9574(u16 bitIndex, u16 enabled);
extern u32 func_080CF060(Item *item);
extern void func_080CF118(Item *item, u8 enabled);

/* The node search of func_080D0ED4 (src/080D0ED4.c); the unlink that follows
 * each call below is that function's as well. */
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

void func_080CF51C(void)
{
    ItemNode *head;
    ItemNode *cursor;

    if (func_080CE8A8() == func_080CED2C() && !func_080C9540(0x5AE))
        func_080C9574(0x5AE, 1);
    if (func_080C9540(0x258) && func_080C9540(0x48C))
        func_080C9574(0x48C, 1);

    head = g_state_02000000.head;
    if (head == 0)
        return;
    for (cursor = head; cursor != 0; cursor = cursor->next) {
        Item *item = cursor->item;
        const ItemMetadata *metadata = &g_table_0855AE4C[item->id];

        if (item->unknown_03 != 0xFF && item->unknown_03 != 0)
            item->unknown_03--;
        if (item->unknown_03 == 0) {
            switch (item->status) {
            case 0:
                if (func_080CF060(item) == 0)
                    func_080CF118(item, 0);
                /* fall through */
            case 1:
            case 2:
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
                break;
            case 3: {
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
                break;
            }
            }
        }
    }
}
