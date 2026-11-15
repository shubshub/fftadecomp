#include "ffta.h"

/* Complete [0x080D1E70, 0x080D2114): 676 bytes, 280 instructions, eighteen
 * literal words in ten pools.
 * f0b557464e464546e0b482b0061c0904090c8a463278707803210840030213434620191c41431648
 * 091889465046002804d0144958180121f7f764fb002398464846143000905146090601914f461537
 * 02205346002b00d000204044850049464819817cc07c04020c43009b58190078022829d0022807dc
 * 012808d075e000004cae5508ff02000003283bd06de00c4884426ad90b4960180004040c201cf7f7
 * 4bfb0006000e791909780906091640180004010cff2900d9ff210906090e2ae0ff05000000faffff
 * 0a4b9c424dd90a4960180004040c201cf7f72efb0006010e7819007800060016814207dd081a0004
 * 010c04e0ff05000000faffff00210906090e08e0064b9c420ed9064960180004040c78190178201c
 * f7f71afb25e00000ff05000000faffff7819007800060016002804d0201c0121f7f7e4fa03e0201c
 * 0021f7f7dffa164be0180004000c17280bd8201cf7f7bcfa0006002805d1201c80300006000efdf7
 * 37fd012080444146012900dc6ce73078717803221140090201436e291cd18120f7f7d6fa0006000e
 * 032809d803480121f7f7b4fa08e0000079faffff8205000004480121f7f7aafa81200021f7f7ccfa
 * 08e00000830500002e2903d108480021f7f79cfa019b190e301cfdf769f8504600281dd04a463f32
 * 1078002804d01ce06d0300000c1c0ae000230749074a0868b042f7d001330c313f2bf8dd00246068
 * 002824d12ee00000c8250002b8d436084a464032107800280bd0b1781d20404208400c210843b070
 * 1078f07029e00c1c0ae0002309490a4a0868b042f7d001330c313f2bf8dd0024606800280ad0a168
 * 816000290ed048600ce00000c8250002b8d43608a168002900d0486009480a4bc018016020681268
 * 102170f0abf80020206002b038bc9846a146aa46f0bc01bc0047000000000002c8280000
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

/* One of four 4-byte effects at 0x12 of a 0x46-byte row: a flag index below
 * 0x600 or a counter index from 0x600 up, an operation (1 add, 2 subtract,
 * 3 set) and its signed operand. */
typedef struct {
    u16 index;
    u8 operation;
    s8 operand;
} __attribute__((packed)) ItemEffect;

/* One 0x46-byte row.  The enabled path reads the byte at 0x3F and the other
 * path the byte at 0x40, which is the one func_080D0ED4 reads. */
typedef struct {
    u8 unknown_00[0x12];
    ItemEffect effects[4];
    u8 unknown_22[0x1D];
    u8 unknown_3F;
    u8 unknown_40;
    u8 unknown_41[5];
} __attribute__((packed)) ItemMetadata;

extern ItemListState g_state_02000000;
extern const ItemMetadata g_table_0855AE4C[];
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern u8 func_080C9540(u16 bitIndex);
extern void func_080C9574(u16 bitIndex, u16 enabled);
extern u8 func_080C95A8(u16 index);
extern void func_080C95C0(u16 index, u32 value);
extern void func_080CFA48(u8 index);
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

void func_080D1E70(Item *item, u16 enabled)
{
    const ItemMetadata *metadata = &g_table_0855AE4C[item->id];
    s32 i;

    if (enabled)
        func_080C9574(item->id + 0x2FF, 1);
    for (i = 0; i < 2; i++) {
        s32 offset;
        u16 index;
        u16 value;

        if (enabled != 0)
            offset = 0;
        else
            offset = 2;
        index = metadata->effects[i + offset].index;

        switch (metadata->effects[i + offset].operation) {
        case 1:
            if (index > 0x5FF) {
                index -= 0x600;
                value = func_080C95A8(index) + metadata->effects[i + offset].operand;
                if (value > 0xFF)
                    value = 0xFF;
                func_080C95C0(index, (u8)value);
            }
            break;
        case 2:
            if (index > 0x5FF) {
                index -= 0x600;
                value = func_080C95A8(index);
                if (value > metadata->effects[i + offset].operand)
                    value -= metadata->effects[i + offset].operand;
                else
                    value = 0;
                func_080C95C0(index, (u8)value);
            }
            break;
        case 3:
            if (index > 0x5FF) {
                index -= 0x600;
                func_080C95C0(index, (u8)metadata->effects[i + offset].operand);
            } else {
                if (metadata->effects[i + offset].operand != 0)
                    func_080C9574(index, 1);
                else
                    func_080C9574(index, 0);
                if (index >= 0x587 && index <= 0x59E && !func_080C9540(index))
                    func_080CFA48(index + 0x80);
            }
            break;
        }
    }
    if (item->id == 0x6E) {
        if (func_080C95A8(0x81) <= 3)
            func_080C9574(0x582, 1);
        else
            func_080C9574(0x583, 1);
        func_080C95C0(0x81, 0);
    } else if (item->id == 0x2E) {
        func_080C9574(0x36D, 0);
    }
    func_080CF118(item, enabled);
    if (enabled) {
        if (metadata->unknown_3F != 0) {
            item->status = 3;
            item->unknown_03 = metadata->unknown_3F;
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
    } else {
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
}
