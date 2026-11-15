#include "ffta.h"

/* Complete [0x080D0AB0, 0x080D0B48): 152 bytes, 67 instructions, four literal
 * words.
 * f0b5474680b4071c8c4600261e481f4940180568002d30d01d4a90462c682278607803210840
 * 030213431a4958180004000c0021162800d8012100291ad1a1781c200840002815d146205843
 * 4044011c4131097842300078000208438022d200111c0840002805d1002f00d010c70136664502
 * d0ad68002dd0d1301c08bc9846f0bc02bc0847000000000002c82800004cae5508b0feffff
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

/* One 0x46-byte row.  The halfword at 0x41 is declared as src/080D2D54.c
 * declares it; this function reads it and tests bit 10. */
typedef struct {
    u8 unknown_00[0x41];
    u16 flags;
    u8 unknown_43[3];
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

/* An inlined copy of func_080D2FB8 (src/080D2FB8.c). */
static inline u32 inlined_080D2FB8(u16 id)
{
    u16 relative = id - 0x150;

    if (relative <= 0x16) {
        return 1;
    }
    return 0;
}

u32 func_080D0AB0(Item **items, u32 limit)
{
    u32 count = 0;
    ItemNode *node;

    for (node = g_state_02000000.head; node != 0; node = node->next) {
        Item *item = node->item;

        if (inlined_080D2FB8(item->id))
            continue;
        if (item->status != 0)
            continue;
        if ((g_table_0855AE4C[item->id].flags & 0x400) != 0)
            continue;
        if (items != 0)
            *items++ = item;
        count++;
        if (count == limit)
            break;
    }
    return count;
}
