#include "script_entry.h"

/* Complete [0x080D0F74, 0x080D1218): 676 bytes, 290 instructions, fourteen
 * literal words in eight pools.
 * f0b557464e464546e0b481b0061cf17880200840002800d134e17f200840f0703179727901201040
 * 03020b43191c002900d1d1e046204143174809188946fe200240c82a04d1154958180121f8f7d8fa
 * 0022904648461430009011498a464f4615377179fe2008400221002800d000214246501885004946
 * 4819817cc07c04020c43009a50190078022829d0022809dc01280ad06fe000004cae5508ff020000
 * ff050000032837d065e0544563d90b4960180004040c201cf8f7bcfa0006000e7919097809060916
 * 40180004010cff2900d9ff210906090e26e0000000faffff544548d9094aa0180004040c201cf8f7
 * a1fa0006010e7819007800060016814206dd081a0004010c03e0000000faffff00210906090e07e0
 * 54450bd9044960180004040c78190178201cf8f78ffa22e000faffff7819007800060016002804d0
 * 201c0121f8f75cfa03e0201c0021f8f757fa164aa0180004000c17280bd8201cf8f734fa00060028
 * 05d1201c80300006000efef7affc012080444146012900dc6fe73079717901221140090201436e29
 * 1cd18120f8f74efa0006000e032809d803480121f8f72cfa08e0000079faffff8205000004480121
 * f8f722fa81200021f8f744fa08e00000830500002e2903d10f480021f8f714fab178412040420840
 * 20210843b0707078802108437070327970790121084000021043064f002824d0041c0548054a8018
 * 006800280ad116e06d030000703a560800000002c82800001a1c0de0021c03251368197858782840
 * 00020843a042f3d09268002af4d1002291781d20404208409070717901200840f02108437071b278
 * d209f1787f20014049001143480040188000c019007865f7a5f81f210140b2782020404210400843
 * b07005e006480268301c062171f024f801b038bc9846a146aa46f0bc01bc0047b8d43608
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

typedef struct {
    u8 unknown_00[0x12];
    ItemEffect effects[4];
    u8 unknown_22[0x24];
} __attribute__((packed)) ItemMetadata;

/* The 6-byte entry as src/08044158.c declares it (every caller passes an
 * element of that file's entries[] at 0x224), except bits 23..31, which that
 * file leaves as `u8 unknown_17 : 1; u8 unknown_03_byte;` and which are
 * declared here as src/080445DC.c declares them. */
typedef struct {
    u8 category : 3;
    u8 unknown_03 : 5;
    u8 unknown_08 : 7;
    u8 disabled : 1;
    u8 selection : 5;
    u8 primary : 1;
    u8 secondary : 1;
    u8 resource : 8;
    u8 unknown_1f : 1;
    u16 id : 9;
    u16 unknown_29 : 7;
} __attribute__((packed)) ActionEntry;

extern ItemListState g_state_02000000;
extern const ItemMetadata g_table_0855AE4C[];
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern u8 func_080C9540(u16 bitIndex);
extern void func_080C9574(u16 bitIndex, u16 enabled);
extern u8 func_080C95A8(u16 index);
extern void func_080C95C0(u16 index, u32 value);
extern void func_080CFA48(u8 index);
extern u8 func_08036330(u8 selector);

/* An inlined copy of func_080D2DE0 (src/080D2DE0.c). */
static inline Item *inlined_080D2DE0(u16 id)
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

void func_080D0F74(ActionEntry *entry)
{
    if (entry->unknown_1f) {
        entry->unknown_1f = 0;
        if (entry->id != 0) {
            const ItemMetadata *metadata = &g_table_0855AE4C[entry->id];
            s32 i;

            if (entry->unknown_29 == 100)
                func_080C9574(entry->id + 0x2FF, 1);
            for (i = 0; i < 2; i++) {
                s32 offset;
                u16 index;
                u16 value;

                if (entry->unknown_29 != 0)
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
            if (entry->id == 0x6E) {
                if (func_080C95A8(0x81) <= 3)
                    func_080C9574(0x582, 1);
                else
                    func_080C9574(0x583, 1);
                func_080C95C0(0x81, 0);
            } else if (entry->id == 0x2E) {
                func_080C9574(0x36D, 0);
            }
        }
        entry->secondary = 0;
        entry->primary = 1;
        entry->disabled = 1;
        if (entry->id != 0)
            inlined_080D2DE0(entry->id)->status = 0;
        entry->unknown_29 = 0x78;
        entry->selection = func_08036330(g_table_08563A70[entry->resource].unknown_00);
    } else {
        g_callbacks_0836D4B8[0](entry, sizeof(*entry));
    }
}
