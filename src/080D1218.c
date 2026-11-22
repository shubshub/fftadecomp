#include "script_entry.h"

/* Complete [0x080D1218, 0x080D17C4): 1452 bytes, 630 instructions, forty
 * literal words in ten pools and three alignment halfwords.
 * f0b557464e464546e0b481b082460091151c0e1c00208046002e00d1bee20449044a881800688946
 * 002805d10020b5e200000002c8280000041c274b9c4623681a785878032108400002104346214143
 * 6746ca19214940180004000c0021162800d8012100292fd199781c20084000282ad1101c41300078
 * 111c42310978090201438027ff00381c014000291cd191780720084004380006000e012814d8101c
 * 453001784800401880000d4940180078a84209d1504604308246043808c080218846013e002e04d0
 * a468002cb7d1002e08d1009a901b5de24cae5508b0feffff703a56084a4848440468002c46d02368
 * 1a7858780321084000021043462141436746ca19434940180004000c0021162800d8012100292ed1
 * 99781c200840002829d1101c41300078111c42310978090201438027ff00381c014000291bd19178
 * 0720084002380006000e012813d8101c453001784800401880002f4940180078a84208d150460430
 * 8246043808c0013e002e00d10ce2a468002cb8d1002e00d106e2680040198000244a914648442621
 * 2a1c4a4322495418417808200840002800d1f5e11f4f20480268381c102170f041ff207961790902
 * 01433970090a032421407b7804225242101c1840084320407870b87802401d2040420240ba70281c
 * 14300004000cf8f7d3f8f87031f7fef9000400149b21490071f09efab871000af8710a4848440068
 * 002815d100209ae0c8280000b0feffff703a5608b42c0002f053560850280003b8d4360814fcffff
 * 101c18e00c1c24e0021c03241548031c106801784078204000020843c0180004000c0021162800d8
 * 01210029e8d19268002aedd1002000286dd0046800230a490a4a0868a042ddd001330c313f2bf8dd
 * 0024606800280fd0a1688160002913d0486011e0b0feffffc8250002b8d43608141c1fe00a1c2ee0
 * a168002900d0486019481a4bc018016020681268102170f0b9fe002020600023154a032411785078
 * 2040000208430028e2d0013310323f2bf4dd00240f480368201c391c102270f0a3fe00220c490868
 * 0028d3d001320c313f2af8dd00220448044fc0190168002900d134e10be0000000000002c8280000
 * c8210002bcd43608c8250002896888680028fbd18a6014600020906022e1141c10e00a1c21e00023
 * 144a0324117850782040000208430028f1d0013310323f2bf4dd0024002c2ed00d480368201c391c
 * 102270f061fe00220a4908680028e0d001320c313f2af8dd00220748074940180168002900d1f2e0
 * 0be00000c8210002bcd43608c825000200000002c8280000896888680028fbd18a60146000209060
 * e0e00c1c11e002200221fdf7c9fc002869d0046800230949094a0868a042f0d001330c313f2bf8dd
 * 0024606800280dd0a1688160002911d048600fe0c8250002b8d43608141c1fe00a1c2ee0a1680029
 * 00d0486019481a4bc018016020681268102170f007fe002020600023154a03241178507820400002
 * 08430028e2d0013310323f2bf4dd00240f480368201c391c102270f0f1fd00220c4908680028d3d0
 * 01320c313f2af8dd00220448044fc0190168002900d182e00be0000000000002c8280000c8210002
 * bcd43608c8250002896888680028fbd18a6014600020906070e00c1c11e000200321fdf759fc0028
 * 69d0046800230949094a0868a042f0d001330c313f2bf8dd0024606800280dd0a1688160002911d0
 * 48600fe0c8250002b8d43608141c1fe00a1c2ee0a168002900d048601848194bc018016020681268
 * 102170f097fd002020600023144a0324117850782040000208430028e2d0013310323f2bf4dd0024
 * 0e480368201c391c102270f081fd00220b4908680028d3d001320c313f2af8dd00220348034fc019
 * 0168002913d00ae000000002c8280000c8210002bcd43608c8250002896888680028fbd18a601460
 * 0020906002e00260146091605160002c02d050460460013e0099881b40440006000e804601b038bc
 * 9846a146aa46f0bc02bc0847
 * Copies up to capacity listed items into output: first the eligible items
 * of the low kinds 4 and 5 (bit 7 of the result records that one was
 * found), then those of 2 and 3.  When room is left and the category's
 * counter is running, a new item is built in the scratch record at
 * 0x03002850 and appended to the list, replacing an item of the 0x150
 * range or one that func_080CEF78 picks when no item is free.  Returns the
 * number written plus that bit.
 */

/* The 16-byte item as src/080CFCD0.c declares it. */
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

/* One 0x46-byte row: byte 2 as src/080D29D4.c declares it and the halfword
 * at 0x41 as src/080D0590.c declares it (read a byte at a time at
 * 0x080D128A-0x080D1298). */
typedef struct {
    u8 unknown_00[2];
    u8 unknown_02_low : 3;
    u8 kind : 3;
    u8 unknown_02_high : 2;
    u8 unknown_03[0x3E];
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

/* The 12-byte record as src/080D2FD8.c declares it. */
typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 value;
    u8 unknown_03[9];
} Record080D2FD8;

/* A 38-byte row as src/080CFAD4.c declares it, with the halfword at +4
 * that this function reads a byte at a time (0x080D13CA-0x080D13D0). */
typedef struct {
    u8 unknown_00;
    u8 base;
    u16 duration;
    u16 item_id;
    u8 unknown_06;
    u8 chance[31];
} __attribute__((packed)) CounterDefinition;

/* The counters at 0x2CB4 are the records src/080CFA48.c reads through
 * g_state_02002CB4; 32 of them end at 0x2E34, where the records of
 * src/080D17C4.c begin.  They are a member of the same object as head
 * here: the ROM reads head as the counter base less 0x3EC (0x080D141A). */
typedef struct {
    u8 unknown_00[0x21C8];
    Item items[64];
    ItemNode nodes[64];
    ItemNode *head;
    u8 unknown_28CC[0x3E8];
    Record080D2FD8 counters[32];
} ItemListState;

extern ItemListState g_state_02000000;
extern Item data_03002850;
extern const ItemMetadata g_table_0855AE4C[];
extern const CounterDefinition g_table_085653F0[];
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern void (*data_0836D4BC)(void *destination, const void *source, u32 size);
extern u32 func_08002804(void);
extern u8 func_080C95A8(u16 index);
extern ItemNode *func_080CEF78(u8 mode, u16 status);

/* An inlined copy of func_080D2FB8 (src/080D2FB8.c). */
static inline u32 inlined_080D2FB8(u16 id)
{
    u16 relative = id - 0x150;

    if (relative <= 0x16) {
        return 1;
    }
    return 0;
}

/* The list walk of func_080D2DE0 (src/080D2DE0.c), returning the first node
 * whose item is in the 0x150 range; the ROM tests its zero result at
 * 0x080D147C-0x080D147E. */
static inline ItemNode *find_excluded_node(void)
{
    ItemNode *head = g_state_02000000.head;
    ItemNode *node;

    if (head == 0)
        return 0;
    for (node = head; node != 0; node = node->next) {
        if (inlined_080D2FB8(node->item->id))
            return node;
    }
    return 0;
}

/* find_free_item, find_node, remove_item and append_item are the text of
 * src/080CFCD0.c; the ROM has the removal three times (clears at
 * 0x080D14D6, 0x080D163A, 0x080D171A) and the append four times (copies at
 * 0x080D1506, 0x080D158A, 0x080D166A, 0x080D174A). */
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

u8 func_080D1218(Item **output, u32 capacity, u32 category)
{
    u32 remaining = capacity;
    u8 result = 0;
    ItemNode *cursor;
    Item *item;
    const ItemMetadata *metadata;
    const ScriptEntry *entry;
    Record080D2FD8 *counter;
    const CounterDefinition *definition;

    if (remaining == 0)
        return 0;
    if (g_state_02000000.head == 0)
        return 0;
    /* First the items of the low kinds 4 and 5; the list walk and the
     * script-entry pointer are written as src/080D17C4.c writes them. */
    for (cursor = g_state_02000000.head; cursor != 0; cursor = cursor->next) {
        item = cursor->item;
        metadata = &g_table_0855AE4C[item->id];
        if (inlined_080D2FB8(item->id))
            continue;
        if (item->status != 0)
            continue;
        if ((metadata->flags & 0x400) != 0)
            continue;
        if (metadata->unknown_02_low != 4 && metadata->unknown_02_low != 5)
            continue;
        entry = &g_table_08563A70[metadata->unknown_45];
        if (entry->unknown_00 != category)
            continue;
        *output++ = item;
        result = 0x80;
        remaining--;
        if (remaining == 0)
            break;
    }
    if (remaining == 0) {
        result += capacity - remaining;
        return result;
    }
    for (cursor = g_state_02000000.head; cursor != 0; cursor = cursor->next) {
        item = cursor->item;
        metadata = &g_table_0855AE4C[item->id];
        if (inlined_080D2FB8(item->id))
            continue;
        if (item->status != 0)
            continue;
        if ((metadata->flags & 0x400) != 0)
            continue;
        if (metadata->unknown_02_low != 2 && metadata->unknown_02_low != 3)
            continue;
        entry = &g_table_08563A70[metadata->unknown_45];
        if (entry->unknown_00 != category)
            continue;
        *output++ = item;
        remaining--;
        if (remaining == 0)
            break;
    }
    if (remaining == 0) {
        result += capacity - remaining;
        return result;
    }
    /* Room is left: if the category's counter runs (flag 8, as in
     * src/080CFAD4.c), build its item and add it to the list.  The record
     * and the row are taken in the order of src/080CFA48.c. */
    counter = &g_state_02000000.counters[category];
    definition = &g_table_085653F0[category];
    if (counter->flags & 8) {
        Item *created = &data_03002850;
        Item *free_item;
        ItemNode *node;

        g_callbacks_0836D4B8[0](created, sizeof(*created));
        created->id = definition->item_id;
        created->countdown = 0;
        created->status = 0;
        created->unknown_03 = func_080C95A8(category + 0x14);
        created->field_06 = (s16)func_08002804() % 310;
        node = find_excluded_node();
        /* No item is placed yet.  On the empty-list path the ROM still sets
         * the search result to null (movs r0, #0 at 0x080D1424) before it
         * branches to 0x080D155E. */
        free_item = 0;
        if (node != 0) {
            remove_item(node->item);
            free_item = find_free_item();
            append_item(free_item, created);
        } else {
            free_item = find_free_item();
            if (free_item != 0) {
                append_item(free_item, created);
            } else {
                node = func_080CEF78(2, 2);
                if (node != 0) {
                    remove_item(node->item);
                    free_item = find_free_item();
                    append_item(free_item, created);
                } else {
                    node = func_080CEF78(0, 3);
                    if (node != 0) {
                        remove_item(node->item);
                        free_item = find_free_item();
                        append_item(free_item, created);
                    }
                }
            }
        }
        if (free_item != 0) {
            *output = free_item;
            remaining--;
        }
    }
    result += capacity - remaining;
    return result;
}
