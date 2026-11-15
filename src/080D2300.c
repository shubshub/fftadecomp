#include "ffta.h"

typedef struct {
    u16 id : 10;
    u16 flags : 6;
    u8 unknown_02[2];
    u8 first;
    u8 second;
} __attribute__((packed)) Item;

typedef struct ItemNode {
    Item *item;
    u32 unknown_04;
    struct ItemNode *next;
} ItemNode;

typedef struct {
    u8 unknown_00[0x28C8];
    ItemNode *head;
} ItemListState;

/* One 16-byte row.  This function reads field_0D; func_080D2380 reads value. */
typedef struct {
    u8 unknown_00[13];
    u8 field_0D;
    u8 value;
    u8 unknown_0F;
} Entry080D2380;

extern ItemListState g_state_02000000;
extern const Entry080D2380 g_table_08521214[];

/* An inlined copy of func_080D2DE0 (src/080D2DE0.c). */
static inline Item *find_item(u16 id)
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

/* Complete [0x080D2300, 0x080D2380): 128 bytes, 56 instructions,
 * three-word pool:
 * 70b500240004050c0348044940180068002807d116e0000000000002c8280000
 * 1a1c0de0021c0326136819785878304000020843a842f3d09268002af4d10022
 * 002a01d1002015e01079002805d00b48117909010918487b24185079002805d0
 * 0648517909010918487b2418002c00da0024201c70bc02bc0847000014125208
 */
s32 func_080D2300(u32 id)
{
    s32 total = 0;
    Item *item = find_item(id);

    if (item == 0)
        return 0;
    if (item->first)
        total += g_table_08521214[item->first].field_0D;
    if (item->second)
        total += g_table_08521214[item->second].field_0D;
    if (total < 0)
        total = 0;
    return total;
}
