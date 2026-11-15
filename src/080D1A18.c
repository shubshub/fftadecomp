#include "ffta.h"

/* Complete [0x080D1A18, 0x080D1B80): 360 bytes, 154 instructions, ten literal
 * words in two pools.
 * f0b557464e464546e0b4071c3620f7f78bfd0006000e82460020fef74df9002038f7ccfd
 * 002800d196e0012038702949294a88180668002e00d18de0032398462648401881463468
 * 20786178424611400d0205432a1c224bd0180004000c0021162800d80121002972d1a178
 * 1c20084000286dd14620111c41431a480b1899780720084004380006000e012860d85046
 * 002801d01a2a5bd0134882423ed11348f7f742fd0006002852d000231049114a0868a042
 * 20d001330c313f2bf8dd0024616800291ad0a068886000281cd041601ae0000000000002
 * c8280000283c0000b0feffff4cae55088d0100008c040000c8250002b8d436080c1ce1e7
 * a068002800d041600449086020681268102170f091fb002020601be0c82800021a1c4532
 * 107800280bd0022038702178607843461840000208434946088010780de04a4615802178
 * 6078434618400002084304e0b668002e00d076e7002038bc9846a146aa46f0bc02bc0847
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

/* One 0x46-byte row.  Byte 2 is declared as src/080D29D4.c declares it; this
 * function tests its low three bits and reads the byte at 0x45. */
typedef struct {
    u8 unknown_00[2];
    u8 unknown_02_low : 3;
    u8 kind : 3;
    u8 unknown_02_high : 2;
    u8 unknown_03[0x42];
    u8 unknown_45;
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
    u8 unknown_28CC[0x135C];
    u16 field_3C28;
} ItemListState;

extern ItemListState g_state_02000000;
extern const ItemMetadata g_table_0855AE4C[];
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern u8 func_080C9540(u16 bitIndex);
extern void func_080CFCD0(u8 initialize);
extern u32 func_0800A5D4(u8 enabled);

/* An inlined copy of func_080D2FB8 (src/080D2FB8.c). */
static inline u32 inlined_080D2FB8(u16 id)
{
    u16 relative = id - 0x150;

    if (relative <= 0x16) {
        return 1;
    }
    return 0;
}

/* The node search of func_080D0ED4 (src/080D0ED4.c); the unlink that follows
 * the call below is that function's as well. */
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

u32 func_080D1A18(u8 *kind_out)
{
    u8 flag = func_080C9540(0x36);
    ItemNode *cursor;

    func_080CFCD0(0);
    if (func_0800A5D4(0) != 0) {
        *kind_out = 1;
        for (cursor = g_state_02000000.head; cursor != 0; cursor = cursor->next) {
            Item *item = cursor->item;
            const ItemMetadata *metadata;

            if (inlined_080D2FB8(item->id))
                continue;
            if (item->status != 0)
                continue;
            metadata = &g_table_0855AE4C[item->id];
            if (metadata->unknown_02_low != 4 && metadata->unknown_02_low != 5)
                continue;
            if (flag != 0 && item->id == 0x1A)
                continue;
            if (item->id == 0x18D) {
                if (func_080C9540(0x48C)) {
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
            } else if (metadata->unknown_45 != 0) {
                *kind_out = 2;
                g_state_02000000.field_3C28 = item->id;
                return metadata->unknown_45;
            } else {
                g_state_02000000.field_3C28 = item->id;
                return item->id;
            }
        }
    }
    return 0;
}
