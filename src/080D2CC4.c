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
    u8 unknown_28CC[0x135C];
    u16 field_3C28;
} ItemListState;

/* One 16-byte row.  This function tests one bit of flags, the byte
 * src/0801984C.c declares under that name. */
typedef struct {
    u8 unknown_00[7];
    u8 flags;
    u8 unknown_08[8];
} Entry080D2CC4;

extern ItemListState g_state_02000000;
extern const Entry080D2CC4 g_table_08521214[];

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

/* Complete [0x080D2CC4, 0x080D2D54): 144 bytes, 64 instructions,
 * including pools:
 * f0b50006070e00260549064a88180488002c37d0044a88180068002808d114e0
 * 00000002283c0000c82800001a1c0de0021c0325136819785878284000020843
 * a042f3d09268002af4d10022117900290ad009010d480918c879791e08410121
 * 0840002800d00126517900290ad0090106480918c879791e0841012108400028
 * 00d00126301cf0bc02bc084714125208
 */
u8 func_080D2CC4(u8 bit)
{
    u8 result = 0;
    u16 id = g_state_02000000.field_3C28;

    if (id != 0) {
        Item *item = inlined_080D2DE0(id);
        const Entry080D2CC4 *entry;
        u8 first;
        u8 second;

        first = item->first;
        if (first) {
            entry = &g_table_08521214[first];
            if ((entry->flags >> (bit - 1)) & 1)
                result = 1;
        }
        second = item->second;
        if (second) {
            entry = &g_table_08521214[second];
            if ((entry->flags >> (bit - 1)) & 1)
                result = 1;
        }
    }
    return result;
}
