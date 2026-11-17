#include "script_entry.h"

/* Complete [0x080CFCD0, 0x080D0590): 2240 bytes, 936 instructions, 63
 * literal words and eight padding halfwords.
 * Adds each item row 1..511 of g_table_0855AE4C whose conditions hold and
 * that is not stored yet: the item is built in the scratch record at
 * 0x03002850, then prepended (flags & 1) or appended to the list; with 64
 * items listed, the one func_080CEF78 picks is removed first. */

typedef struct {
    u16 id : 10;
    u16 countdown : 8;
    u8 status : 3;
    u8 unknown_15 : 3;
    u8 unknown_03;
    u8 unknown_04[2];
    u16 field_06;
    u16 unknown_08;
    u16 unknown_0A;
    u16 unknown_0C;
    u16 unknown_0E;
} __attribute__((packed)) Item;

typedef struct {
    u32 flag : 16;
    u32 value : 8;
} __attribute__((packed)) ItemRequirement;

typedef struct {
    u16 id;
    u8 unknown_02_low : 3;
    u8 kind : 3;
    u8 unknown_02_high : 2;
    u16 unknown_03_low : 4;
    u16 unknown_03_mid : 3;
    u16 filter : 3;
    u16 unknown_04_high : 6;
    ItemRequirement requirements[3];
    u16 unknown_0E_low : 3;
    u16 field_0E : 8;
    u16 unknown_0F_high : 5;
    u16 unknown_10_low : 6;
    u16 field_10 : 8;
    u16 unknown_11_high : 2;
    u8 effects[0x10];
    u16 unknown_22;
    u16 unknown_24;
    u16 unknown_26;
    u16 unknown_28;
    u8 unknown_2A[0x17];
    u16 flags;
    u8 unknown_43[2];
    u8 unknown_45;
} __attribute__((packed)) ItemMetadata;

typedef struct ItemNode ItemNode;

struct ItemNode {
    Item *item;
    ItemNode *previous;
    ItemNode *next;
};

typedef struct {
    u8 unknown_00[0x21C8];
    Item items[64];
    ItemNode nodes[64];
    ItemNode *head;
    u8 unknown_28CC[0x6EE];
    u8 field_2FBA;
} ItemListState;

extern ItemListState g_state_02000000;
/* A 16-byte scratch Item; func_080D1218 clears the same 16 bytes (0x080D13BC). */
extern Item data_03002850;
extern const ItemMetadata g_table_0855AE4C[];
/* Eight rows of 20 (0x08529494-0x085295D3): the metadata selects rows with
 * 0xFFF1-0xFFF7, and 0xFFFF picks row 7; data_085295D4 (src/080D2F78.c)
 * starts after it. */
extern const u16 data_08529494[][20];
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern void (*data_0836D4BC)(void *destination, const void *source, u32 size);
extern u32 func_08002804(void);
extern u8 func_08036330(u8 selector);
extern u8 func_080C9540(u16 bitIndex);
extern u8 func_080C95A8(u16 index);
extern u32 func_080CEDC8(const Item *source);
extern u32 func_080CEECC(u16 index);
extern ItemNode *func_080CEF78(u8 mode, u16 status);
extern void func_080CF51C(void);
extern void func_080CF690(void);
extern void func_080CF7F4(void);
extern u16 func_080D21A8(void);
extern s32 func_08142950(s32 first, s32 second);

/* The array search of find_free_item for one id (src/080D2DE0.c walks the
 * list instead); the ROM tests its zero result at 0x080CFD3A-0x080CFD3C. */
static inline Item *find_item(u16 id)
{
    Item *item;
    s32 i;

    for (i = 0, item = g_state_02000000.items; i < 64; i++, item++) {
        if (item->id == id)
            return item;
    }
    return 0;
}

/* find_free_item and find_node are the text of src/080CEDC8.c. */
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

static inline s32 count_nodes(void)
{
    ItemNode *head = g_state_02000000.head;
    ItemNode *node;
    s32 count;

    if (head == 0)
        return 0;
    count = 1;
    for (node = head; node->next != 0; node = node->next)
        count++;
    return count;
}

/* The node removal src/080D0ED4.c and src/080D17C4.c write out; the ROM
 * has it three times (clears at 0x080D02BA, 0x080D039E, 0x080D0486). */
static inline void remove_item(Item *item)
{
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

/* The ROM has it four times (copies at 0x080D02F0, 0x080D03D4, 0x080D04BA,
 * 0x080D051C). */
static inline void append_item(Item *free_item, const Item *source)
{
    ItemNode *free_node;
    ItemNode *node;

    data_0836D4BC(free_item, source, sizeof(*free_item));
    free_node = find_node(0);
    node = g_state_02000000.head;
    if (node != 0) {
        for (; node->next != 0; node = node->next)
            ;
        node->next = free_node;
        free_node->item = free_item;
        free_node->next = 0;
        free_node->previous = node;
    } else {
        g_state_02000000.head = free_node;
        free_node->item = free_item;
        free_node->next = 0;
        free_node->previous = 0;
    }
}

void func_080CFCD0(u8 initialize)
{
    u32 filter = g_state_02000000.field_2FBA;
    const ItemMetadata *metadata;
    s32 id;

    if (initialize) {
        func_080CF690();
        func_080CF7F4();
        func_080CF51C();
    }
    metadata = &g_table_0855AE4C[1];
    for (id = 1; id <= 511; id++, metadata++) {
        Item *item;
        Item *free_item;
        ItemNode *node;
        s32 requirement;

        if (metadata->unknown_03_mid == 0)
            continue;
        if (find_item(id) != 0)
            continue;
        if (func_080C9540(id + 0x2FF) && (metadata->flags & 8) == 0)
            continue;
        if (metadata->unknown_0E_low != 0 && metadata->unknown_0E_low != filter)
            continue;
        if (metadata->unknown_45 != 0 &&
            !func_08036330(g_table_08563A70[metadata->unknown_45].unknown_00))
            continue;
        requirement = metadata->requirements[0].flag;
        if (requirement > 0x5FF) {
            requirement -= 0x600;
            if (func_080C95A8(requirement) < metadata->requirements[0].value)
                continue;
        } else {
            if (func_080C9540(requirement) == 1 &&
                metadata->requirements[0].value == 0)
                continue;
            if (func_080C9540(requirement) == 0 &&
                metadata->requirements[0].value == 1)
                continue;
        }
        requirement = metadata->requirements[1].flag;
        if (requirement > 0x5FF) {
            requirement -= 0x600;
            if (func_080C95A8(requirement) < metadata->requirements[1].value)
                continue;
        } else {
            if (func_080C9540(requirement) == 1 &&
                metadata->requirements[1].value == 0)
                continue;
            if (func_080C9540(requirement) == 0 &&
                metadata->requirements[1].value == 1)
                continue;
        }
        requirement = metadata->requirements[2].flag;
        if (requirement > 0x5FF) {
            requirement -= 0x600;
            if (func_080C95A8(requirement) < metadata->requirements[2].value)
                continue;
        } else {
            if (func_080C9540(requirement) == 1 &&
                metadata->requirements[2].value == 0)
                continue;
            if (func_080C9540(requirement) == 0 &&
                metadata->requirements[2].value == 1)
                continue;
        }
        if (metadata->id == 0x17F &&
            (func_080C9540(0x258) || func_080C9540(0x259) ||
             func_080C9540(0x25A) || func_080C9540(0x25B) ||
             func_080C9540(0x25C)))
            continue;

        item = &data_03002850;
        g_callbacks_0836D4B8[0](item, sizeof(*item));
        item->id = id;
        item->countdown = metadata->field_10;
        item->status = 2;
        item->unknown_03 = metadata->field_0E ? metadata->field_0E : 0xFF;
        item->field_06 = func_08142950((s16)func_08002804(), 310);
        if (metadata->unknown_22 == 0xFFFF)
            item->unknown_08 =
                data_08529494[7][(s16)func_08142950((s16)func_08002804(), 20)];
        else if (metadata->unknown_22 > 0xFFF0)
            item->unknown_08 =
                data_08529494[metadata->unknown_22 - 0xFFF1]
                             [(s16)func_08142950((s16)func_08002804(), 20)];
        else
            item->unknown_08 = metadata->unknown_22;
        if (metadata->unknown_24 == 0xFFFF)
            item->unknown_0A =
                data_08529494[7][(s16)func_08142950((s16)func_08002804(), 20)];
        else if (metadata->unknown_24 > 0xFFF0)
            item->unknown_0A =
                data_08529494[metadata->unknown_24 - 0xFFF1]
                             [(s16)func_08142950((s16)func_08002804(), 20)];
        else
            item->unknown_0A = metadata->unknown_24;
        if (metadata->unknown_26 == 0xFF)
            item->unknown_0C = func_080D21A8();
        else
            item->unknown_0C = metadata->unknown_26;
        if (metadata->unknown_28 == 0xFF)
            item->unknown_0E = func_080D21A8();
        else
            item->unknown_0E = metadata->unknown_28;
        if (metadata->unknown_02_low == 4 || metadata->unknown_02_low == 5)
            item->status = 0;

        free_item = find_free_item();
        if (metadata->flags & 1) {
            if (free_item != 0) {
                ItemNode *free_node;

                data_0836D4BC(free_item, item, sizeof(*free_item));
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
            } else {
                func_080CEDC8(item);
            }
        } else if (count_nodes() > 63) {
            if (func_080CEECC(item->id) == 0)
                continue;
            node = func_080CEF78(1, 2);
            if (node != 0) {
                remove_item(node->item);
                free_item = find_free_item();
                if (free_item != 0)
                    append_item(free_item, item);
            } else {
                node = func_080CEF78(1, 1);
                if (node != 0) {
                    remove_item(node->item);
                    free_item = find_free_item();
                    if (free_item != 0)
                        append_item(free_item, item);
                } else {
                    node = func_080CEF78(0, 3);
                    if (node != 0) {
                        remove_item(node->item);
                        free_item = find_free_item();
                        if (free_item != 0)
                            append_item(free_item, item);
                    }
                }
            }
        } else {
            if (free_item != 0)
                append_item(free_item, item);
        }
    }
}
