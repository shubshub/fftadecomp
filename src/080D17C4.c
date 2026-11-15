#include "script_entry.h"

/* Complete [0x080D17C4, 0x080D1A18): 596 bytes, 260 instructions, sixteen
 * literal words in four pools.
 * f0b557464e464546e0b481b00090171c090600240e4e0d0e00229319197807200840002816d05978
 * 80200840002811d19878c006c00ea8420cd1032038709a78d209d8787f21084040001043fae00000
 * 342e000206320134042cdedd3620f7f78dfe0006000e8246012038f7d1fe002800d194e001203870
 * 2849294a88180668002e00d18be003239846264840188146346820786178424611400d0205432b1c
 * 214958180004000c0021162800d80121002970d1a1781c20084000286bd14620191c414319480a18
 * 91780720084004380006000e01285ed85046002801d01a2b59d0134883423dd11248f7f747fe0006
 * 002850d000231049104a0868a0421fd001330c313f2bf8dd00246168002919d0a068886000281bd0
 * 416019e000000002c8280000283c0000b0feffff4cae55088d0100008c040000c8250002b8d43608
 * 0c1ce2e7a068002800d041600449086020681268102170f097fc002020601ae0c828000245321078
 * 00280bd0022038702178607843461840000208434946088010785fe04a4615802178607843461840
 * 0002084356e0b668002e00d078e72148214940180668002e49d03468227860780321084003021343
 * 1c4a98180004000c0021162800d80121002935d1a1781c200840002830d14620191c414314480a18
 * 131c45331878002826d0011c480040188000104940180078009988421cd191780720084004380006
 * 000e012814d811785078000208431a280ed002203870187810e0000000000002c8280000b0feffff
 * 4cae5508703a5608b668002eb5d100203870002001b038bc9846a146aa46f0bc02bc0847
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

/* One 0x46-byte row.  Byte 2 is declared as src/080D29D4.c declares it.  The
 * halfword at 0 is the row's own index in all 512 rows of the ROM table; this
 * function reads it, the low three bits of byte 2 and the byte at 0x45. */
typedef struct {
    u16 id;
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

/* The 6-byte record of src/08044158.c; the state holds five of them at 0x2E34,
 * which is entries[5] at 0x224 of the block at 0x02002C10 in that file.  Bits
 * 16..31 are one 16-bit unit of bit-fields (`resource` crosses the byte
 * boundary) and are declared on u16: the comparison of `selection` with the
 * u8 parameter below is made in 16 bits, as it is in func_080364BC. */
typedef struct {
    u8 category : 3;
    u8 unknown_03 : 5;
    u8 unknown_08 : 7;
    u8 disabled : 1;
    u16 selection : 5;
    u16 primary : 1;
    u16 secondary : 1;
    u16 resource : 8;
    u16 unknown_1f : 1;
    u16 id : 9;
    u16 unknown_29 : 7;
} __attribute__((packed)) ActionEntry;

typedef struct {
    u8 unknown_00[0x25C8];
    ItemNode nodes[64];
    ItemNode *head;
    u8 unknown_28CC[0x568];
    ActionEntry records[5];
    u8 unknown_2E52[0xDD6];
    u16 field_3C28;
} ItemListState;

extern ItemListState g_state_02000000;
extern const ItemMetadata g_table_0855AE4C[];
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern u8 func_080C9540(u16 bitIndex);
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

u32 func_080D17C4(u32 filter, u8 selection, u8 *kind_out)
{
    ItemNode *cursor;
    Item *item;
    const ItemMetadata *metadata;
    const ScriptEntry *entry;
    u8 flag;
    s32 i;

    for (i = 0; i < 5; i++) {
        ActionEntry *record = &g_state_02000000.records[i];

        if (record->category != 0 && !record->disabled && record->selection == selection) {
            *kind_out = 3;
            return record->resource;
        }
    }
    flag = func_080C9540(0x36);
    if (func_0800A5D4(1) != 0) {
        *kind_out = 1;
        for (cursor = g_state_02000000.head; cursor != 0; cursor = cursor->next) {
            item = cursor->item;
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
    for (cursor = g_state_02000000.head; cursor != 0; cursor = cursor->next) {
        item = cursor->item;
        if (inlined_080D2FB8(item->id))
            continue;
        if (item->status != 0)
            continue;
        metadata = &g_table_0855AE4C[item->id];
        if (metadata->unknown_45 == 0)
            continue;
        entry = &g_table_08563A70[metadata->unknown_45];
        if (entry->unknown_00 != filter)
            continue;
        if (metadata->unknown_02_low != 4 && metadata->unknown_02_low != 5)
            continue;
        if (metadata->id == 0x1A)
            continue;
        *kind_out = 2;
        return metadata->unknown_45;
    }
    *kind_out = 0;
    return 0;
}
