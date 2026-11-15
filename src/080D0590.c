#include "script_entry.h"

/* Complete [0x080D0590, 0x080D0AB0): 1312 bytes, 592 instructions, twenty-six
 * literal words in seven pools.
 * f0b557464e464546e0b484b00090019280460f1c002002900648b9000268404671f04cfe0449054a
 * 88180068002807d100206de2b8d4360800000002c828000000230393894607241a4b4b4404221978
 * 201c0840002804d1039801300006000e03900633013a002af1da00208246124848440668002e39d0
 * 34682278607803210840000210434621021c4a430b4955180b4940180004000c0021162800d80121
 * 002920d1a1781c20084000281bd141460be00000342e0000c82800004cae5508b0feffff01c9a042
 * 0dd008680028f9d1a97838200840102801d101229246013f002f00d113e2b668002ec5d12b484844
 * 0668002e00d183e0032399463468217860784a461040000208434621414324480d18291c45310878
 * 00280bd0214a011c4800401880008018007865f739fe0006002861d0a87807220240031c032a09d0
 * 052a07d0217860784a461040000208430f2851d1a1781c20084000284cd0c806400f022848d8e978
 * c90928794a46104040000843002802d0019988423cd1281c4130017801300078000208438022d200
 * 111c084000282fd1414608e0c82800004cae5508703a560801c9a04224d008680028f9d107201840
 * 012807d1039b002b1ad0181c01380006000e0390009810c00090029901310291a1781c2008400028
 * 06d01d225242101c084004210843a070013f002f00d18ae1b668002e00d07de75346002b00d080e0
 * 2548264940180668002e7ad0032291463468217860784b461840000208434621021c4a431e495518
 * 1e4940180004000c0021162800d8012100295fd1291c4531087800280bd0184a011c480040188000
 * 8018007865f7a0fd000600284ed0a978382008400b1c102848d1a1781c200840002843d0c806400f
 * 02283fd8e978c90928794a46104040000843002802d00199884233d141460ce000000002c8280000
 * 4cae5508b0feffff703a560801c9a04224d008680028f9d107201840012807d1039a002a1ad0101c
 * 01380006000e0390009b10c30093029801300290a1781c200840002806d01d225242101c08400421
 * 0843a070013f002f03d104e1b668002e86d100239a46014881460de00000000200217f2053461840
 * 002800d1012111438a46002f00d1cbe03d4848440668002e00d1bee0032081463468217860784a46
 * 1040000208434621414336480d18291c4531087800280cd0334a011c4800401880008018007865f7
 * 17fd0006002800d196e0207861784b461940090201432b4a88180004000c0022162800d80122002a
 * 00d085e000227f2053461840002800d10122a8788006400f904279d1204881421ed1d930f8f7f8fd
 * 0006002870d11d48f8f7f2fd000600286ad11b48f8f7ecfd0006002864d11948f8f7e6fd00060028
 * 5ed197208000f8f7dffd0006002857d1a1781c200840002852d0c806400f02284ed8e978c9092879
 * 4a46104040000843002802d0019b984242d1414613e00000c82800004cae5508703a5608b0feffff
 * 7f010000590200005a0200005b02000001c9a0422cd008680028f9d1a97807200840012806d10398
 * 002821d001380006000e0390009910c10091029a01320292a1781c200840002806d01d235b42181c
 * 084004210843a070013f002f3bd000217f2052461040002800d101218a4603e0b668002e00d047e7
 * 0d4b9946002e00d037e78022802051460840002800d127e7084848440668002e1dd01d2252423468
 * a1781c200840042812d1414607e0000000000002c828000001c9a04208d008680028f9d1a078111c
 * 014008200143a170b668002ee3d1029804b038bc9846a146aa46f0bc02bc0847
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

/* One 0x46-byte row.  Byte 2 is declared as src/080D29D4.c declares it and
 * the halfword at 0x41 as src/080D2D54.c declares it.  The three-bit filter
 * straddles bytes 3 and 4; a row with a non-zero filter is only eligible for
 * a caller that passes the same value. */
typedef struct {
    u8 unknown_00[2];
    u8 unknown_02_low : 3;
    u8 kind : 3;
    u8 unknown_02_high : 2;
    u16 unknown_03_low : 7;
    u16 filter : 3;
    u16 unknown_04_high : 6;
    u8 unknown_05[0x3C];
    u16 flags;
    u8 unknown_43[2];
    u8 unknown_45;
} __attribute__((packed)) ItemMetadata;

typedef struct ItemNode {
    Item *item;
    struct ItemNode *previous;
    struct ItemNode *next;
} ItemNode;

/* The 6-byte record as src/080D0F74.c declares it; the state holds five of
 * them at 0x2E34. */
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

typedef struct {
    u8 unknown_00[0x25C8];
    ItemNode nodes[64];
    ItemNode *head;
    u8 unknown_28CC[0x568];
    ActionEntry records[5];
} ItemListState;

extern ItemListState g_state_02000000;
extern const ItemMetadata g_table_0855AE4C[];
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern u8 func_080C9540(u16 bitIndex);
extern u8 func_08036330(u8 selector);

/* An inlined copy of func_080D2FB8 (src/080D2FB8.c). */
static inline u32 inlined_080D2FB8(u16 id)
{
    u16 relative = id - 0x150;

    if (relative <= 0x16) {
        return 1;
    }
    return 0;
}

/* Whether the zero-terminated pointer list already holds the item.  The scan
 * is expanded five times below; the ROM has no out-of-line copy of it. */
static inline u32 contains(Item **items, Item *item)
{
    while (*items != 0) {
        if (*items++ == item)
            return 1;
    }
    return 0;
}

/* Fills output with up to capacity eligible items and returns how many were
 * written.  The list is cleared first and stays zero-terminated, which is
 * what contains() relies on.  Items with status 0 outside the 0x150 range
 * each take one place without being written.  Then come the rows whose low
 * field is 3 or 5 (and item 0xF), then one row of kind 2 unless a status-0
 * item of that kind was seen, then rows of kind 1 and kind 0 in turn until
 * two searches in a row find nothing.  A row whose low field is 1 also needs
 * one of the five records with category 0.  Selected items get status 1;
 * when the list did not fill up, the status-1 items left out get status 2. */
u32 func_080D0590(Item **output, u32 capacity, u32 filter)
{
    Item **start = output;
    u32 remaining = capacity;
    u32 count = 0;
    ItemNode *node;
    Item *item;
    const ItemMetadata *metadata;
    u8 unused;
    /* In the first three walks, whether a status-0 item of kind 2 was seen.
     * In the alternating search after them, its state: kind 1 is wanted
     * while the low seven bits are zero and kind 0 otherwise, and bit 7 is
     * set after a search that found nothing.  One variable, r10 throughout. */
    u8 flag;
    s32 i;

    g_callbacks_0836D4B8[0](output, capacity * sizeof(*output));
    if (g_state_02000000.head == 0)
        return 0;
    unused = 0;
    for (i = 0; i < 5; i++) {
        ActionEntry *record = &g_state_02000000.records[i];

        if (record->category == 0)
            unused++;
    }
    flag = 0;
    for (node = g_state_02000000.head; node != 0; node = node->next) {
        item = node->item;
        metadata = &g_table_0855AE4C[item->id];
        if (inlined_080D2FB8(item->id))
            continue;
        if (item->status != 0)
            continue;
        if (contains(start, item))
            continue;
        if (metadata->kind == 2)
            flag = 1;
        remaining--;
        if (remaining == 0)
            return count;
    }
    for (node = g_state_02000000.head; node != 0; node = node->next) {
        item = node->item;
        metadata = &g_table_0855AE4C[item->id];
        if (metadata->unknown_45 != 0 &&
            !func_08036330(g_table_08563A70[metadata->unknown_45].unknown_00))
            continue;
        if (metadata->unknown_02_low != 3 && metadata->unknown_02_low != 5 &&
            item->id != 0xF)
            continue;
        if (item->status == 0)
            continue;
        if (item->status > 2)
            continue;
        if (metadata->filter != 0 && metadata->filter != filter)
            continue;
        if ((metadata->flags & 0x400) != 0)
            continue;
        if (contains(start, item))
            continue;
        if (metadata->unknown_02_low == 1) {
            if (unused == 0)
                continue;
            unused--;
        }
        *output++ = item;
        count++;
        if (item->status != 0)
            item->status = 1;
        remaining--;
        if (remaining == 0)
            return count;
    }
    if (flag == 0) {
        for (node = g_state_02000000.head; node != 0; node = node->next) {
            item = node->item;
            metadata = &g_table_0855AE4C[item->id];
            if (inlined_080D2FB8(item->id))
                continue;
            if (metadata->unknown_45 != 0 &&
                !func_08036330(g_table_08563A70[metadata->unknown_45].unknown_00))
                continue;
            if (metadata->kind != 2)
                continue;
            if (item->status == 0)
                continue;
            if (item->status > 2)
                continue;
            if (metadata->filter != 0 && metadata->filter != filter)
                continue;
            if (contains(start, item))
                continue;
            if (metadata->unknown_02_low == 1) {
                if (unused == 0)
                    continue;
                unused--;
            }
            *output++ = item;
            count++;
            if (item->status != 0)
                item->status = 1;
            remaining--;
            if (remaining == 0)
                return count;
            break;
        }
    }
    flag = 0;
    do {
        for (node = g_state_02000000.head; node != 0; node = node->next) {
            u32 wanted;

            item = node->item;
            metadata = &g_table_0855AE4C[item->id];
            if (metadata->unknown_45 != 0 &&
                !func_08036330(g_table_08563A70[metadata->unknown_45].unknown_00))
                continue;
            if (inlined_080D2FB8(item->id))
                continue;
            wanted = (flag & 0x7F) == 0;
            if (metadata->kind != wanted)
                continue;
            if (item->id == 0x17F &&
                (func_080C9540(0x258) || func_080C9540(0x259) ||
                 func_080C9540(0x25A) || func_080C9540(0x25B) ||
                 func_080C9540(0x25C)))
                continue;
            if (item->status == 0)
                continue;
            if (item->status > 2)
                continue;
            if (metadata->filter != 0 && metadata->filter != filter)
                continue;
            if (contains(start, item))
                continue;
            if (metadata->unknown_02_low == 1) {
                if (unused == 0)
                    continue;
                unused--;
            }
            *output++ = item;
            count++;
            if (item->status != 0)
                item->status = 1;
            remaining--;
            if (remaining == 0)
                return count;
            flag = (flag & 0x7F) == 0;
            break;
        }
        if (node == 0) {
            if ((flag & 0x80) != 0)
                break;
            flag = (flag & 0x7F) == 0;
            flag |= 0x80;
        }
    } while (remaining != 0);
    for (node = g_state_02000000.head; node != 0; node = node->next) {
        item = node->item;
        if (item->status == 1 && !contains(start, item))
            item->status = 2;
    }
    return count;
}
