#include "script_entry.h"

/* Complete [0x080D0B48, 0x080D0ED2): 906 bytes, 418 instructions, thirteen
 * literal words in six pools.
 * f0b557464e464546e0b481460d1c1204140c1b041b0c002d0ad0027840780321084000021043e882
 * 298d04200843288548460471437180781d267642064049468e7009784a4650780327384000020843
 * 4621414349480c18e17bc908207c07229046104040010843ff21002800d0011c4846c170207c8009
 * 617c3f231940890001430a1c1a40920048464378381c184010434a46507089093940042040423040
 * 08439070a07841460140012900d001e1334a231c4533197848004018800080188179c800401a8000
 * 401a2e49451800242d4f3978404608409a462c4a00280bd007263b1c06330134042c05dc1f1c3978
 * 301c08400028f5d11268381c062171f001fb621c0720024038780821494201401143082001433970
 * 6878c007c00f0001312252420a4002433a706978c906490f0324201c084080013f231a4002433a70
 * 890821407878073c04400c437c706a785209a8781f210840c30013438021181c0840002816d00a48
 * 03401f20034099007d20404204400c437c7017e04cae5508703a560870465608342e0002b8d43608
 * 7fff0000181c65f727fb1f21014089007a787d2040421040084378706a785209a9781f200140c900
 * 114380464246114089007a789c3810400843787048460278407803210840000210433871000a0126
 * 30407979022252420a4002437a7151460b78191c3140c901bc787f25281c20400843b8705b082b40
 * f9788020404208401843f8703240f02002437a71104a504601784800401880008018007865f7dcfa
 * 414601408846b9782020404208404246104320210843b870c006c00e002165f753fb002806d07878
 * 8021084378704be0703a56080024104880461f26002541466b1819780720084000280fd0bb420dd0
 * 9878ba78311c0140301c1040814205d15978802280200840002807d006350134042ce4dd28e00000
 * 342e000278781043787021e000291fd14846291c0122fef783fa041c002c13d0a10010480d1831f7
 * f5fc00040114081c002900daff3000120002081a000400142d78a84200db00244a469471200ad071
 * 0548064a81180a689168031c00290ed00ae000004a7e520800000002c828000092689068002802d0
 * 10684845f8d102495818016803e00000c8280000896888680028fbd109481c182068904201d19142
 * 18d0914216d05368002b09d0906898609368002b0ad05068586007e0c82800009068002802d04360
 * 906820608a6051600020906038bc9846a146aa46f0bc01bc0047
 */

/* The record of src/080D29D4.c and src/080D1C94.c (the eight-bit countdown
 * straddles bytes 1 and 2), with the two bytes src/080D2300.c reads at 4
 * and 5. */
typedef struct {
    u16 id : 10;
    u16 countdown : 8;
    u8 status : 3;
    u8 unknown_15 : 3;
    u8 unknown_03;
    u8 first;
    u8 second;
    u16 field_06 : 16;
    u8 unknown_08[8];
} __attribute__((packed)) Item;

/* One 0x46-byte row.  Bytes 2 and 0xE..0x11 are laid out as src/080D29D4.c
 * lays them out; the eleven bits that file leaves unnamed between field_0E
 * and field_10 are the eight-bit field this function reads and the three
 * mode bits of src/080D1C94.c. */
typedef struct {
    u8 unknown_00[2];
    u8 unknown_02_low : 3;
    u8 kind : 3;
    u8 unknown_02_high : 2;
    u8 unknown_03[0xB];
    u16 unknown_0E_low : 3;
    u16 field_0E : 8;
    u16 field_0F : 8;
    u16 mode : 3;
    u16 field_10 : 8;
    u16 unknown_11_high : 2;
    u8 unknown_12[0x33];
    u8 unknown_45;
} __attribute__((packed)) ItemMetadata;

/* Declared as src/080CEDC8.c declares it. */
typedef struct ItemNode ItemNode;

struct ItemNode {
    Item *item;
    ItemNode *previous;
    ItemNode *next;
};

/* The 6-byte record of src/08044158.c; the state holds five of them at
 * 0x2E34.  Bits 3..9 are split as src/080445DC.c splits them.  Each sixteen
 * bits are one unit of bit-fields on u16, as src/080D17C4.c declares bits
 * 16..31: `type` crosses the byte boundary inside the first unit, and the
 * value this function writes to `unknown_0a` is narrowed to sixteen bits
 * first (the literal 0x0000FF7F at 080D0CD8 is `~0x80` as a u16). */
typedef struct {
    u16 category : 3;
    u16 unknown_03 : 1;
    u16 mode : 2;
    u16 type : 4;
    u16 unknown_0a : 5;
    u16 disabled : 1;
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
} ItemListState;

/* One 27-byte row.  Bytes 1 and 2 are one sixteen-bit unit of bit-fields on
 * u16: the eight-bit value, where src/08045424.c reads it, starts at bit 5
 * of byte 1.  The five bits below it hold the mode bit and the three type
 * bits this function copies into a record. */
typedef struct {
    u8 unknown_00;
    u16 mode : 1;
    u16 unknown_09 : 1;
    u16 type : 3;
    u16 value : 8;
    u16 unknown_15 : 3;
    u8 unknown_03[24];
} __attribute__((packed)) SelectionRecord;

/* Declared as src/080CF118.c declares it; that function clears the two
 * halfwords this one writes. */
typedef struct {
    u8 unknown_00[0x16];
    u16 item_id;
    u8 unknown_18[0x10];
    u16 flags;
    u8 unknown_2A[0xDE];
} Unit;

extern ItemListState g_state_02000000;
extern const ItemMetadata g_table_0855AE4C[];
extern const SelectionRecord g_table_08564670[];
/* Rows of four bytes, selected by func_080CF310's result; this function
 * reads byte 0. */
extern const u8 g_table_08527E4A[][4];
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern u32 func_08002804(void);
extern u8 func_08036330(u8 selector);
extern u32 func_08036440(u8 value, u32 mode);
extern u32 func_080CF310(const void *record, const void *object, u8 enabled);

/* Gives an item to a unit.  The unit, when there is one, gets the item's id
 * and bit 2 of its flags (func_080CF118 takes both back); the item gets the
 * two bytes, status 0, and byte 3 and the countdown from its row.  A row
 * whose low field is 1 then fills in the first of the five records with
 * category 0; a row whose low field is 0 stores func_080CF310's result in
 * field_06, or zero when a random byte is not below the result's threshold.
 * Last, the item's node is moved to the tail of the list. */
void func_080D0B48(Item *item, Unit *unit, u16 first, u16 second)
{
    const ItemMetadata *metadata;
    ItemNode *node;
    ItemNode *tail;

    if (unit != 0) {
        unit->item_id = item->id;
        unit->flags |= 4;
    }
    item->first = first;
    item->second = second;
    item->status = 0;
    metadata = &g_table_0855AE4C[item->id];
    item->unknown_03 = metadata->field_0F ? metadata->field_0F : 0xFF;
    item->countdown = metadata->field_10;

    if (metadata->unknown_02_low == 1) {
        const SelectionRecord *record =
            &g_table_08564670[g_table_08563A70[metadata->unknown_45].selector];
        ActionEntry *entry;
        s32 i;

        /* When no record is free the search ends on the last record, which
         * is then used; the ROM has no not-found path. */
        for (i = 0; i < 5; i++) {
            entry = &g_state_02000000.records[i];
            if (entry->category == 0)
                break;
        }
        g_callbacks_0836D4B8[0](entry, sizeof(*entry));
        entry->category = i + 1;
        entry->unknown_03 = 1;
        entry->mode = record->mode;
        entry->type = record->type;
        if (record->value & 0x80)
            entry->unknown_0a = record->value & ~0x80;
        else
            entry->unknown_0a = func_08036330(record->value);
        /* The ROM stores the field a second time, from the value as it is
         * in the row (080D0CF4..080D0D12). */
        entry->unknown_0a = record->value;
        entry->id = item->id;
        entry->resource = metadata->unknown_45;
        entry->unknown_29 = 0x78;
        entry->selection = func_08036330(g_table_08563A70[metadata->unknown_45].unknown_00);
        entry->primary = 1;
        if (func_08036440(entry->selection, 0)) {
            entry->disabled = 1;
        } else {
            for (i = 0; i < 5; i++) {
                ActionEntry *other = &g_state_02000000.records[i];

                if (other->category != 0 && other != entry &&
                    other->selection == entry->selection && !other->disabled) {
                    entry->disabled = 1;
                    break;
                }
            }
        }
    } else if (metadata->unknown_02_low == 0) {
        u32 result = func_080CF310(item, unit, 1);

        if (result != 0) {
            const u8 *threshold = g_table_08527E4A[result];
            s16 random = (s16)func_08002804() % 256;

            if (random >= threshold[0])
                result = 0;
        }
        item->field_06 = result;
    }

    /* A search that does not find the item ends on the tail. */
    for (node = g_state_02000000.head; node->next != 0; node = node->next) {
        if (node->item == item)
            break;
    }
    for (tail = g_state_02000000.head; tail->next != 0; tail = tail->next)
        ;
    /* The ROM makes all three comparisons (080D0E8A, 080D0E8E, 080D0E92). */
    if (g_state_02000000.head == node && tail == node)
        return;
    if (tail == node)
        return;
    if (node->previous != 0) {
        node->previous->next = node->next;
        if (node->next != 0)
            node->next->previous = node->previous;
    } else if (node->next != 0) {
        node->next->previous = node->previous;
        g_state_02000000.head = node->next;
    }
    tail->next = node;
    node->previous = tail;
    node->next = 0;
}
