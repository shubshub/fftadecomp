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

/* One 16-byte row.  This function reads field_09 to field_0C. */
typedef struct {
    u8 unknown_00[9];
    u8 field_09;
    u8 field_0A;
    u8 field_0B;
    u8 field_0C;
    u8 unknown_0D[3];
} Entry080D2BF4;

extern ItemListState g_state_02000000;
extern const Entry080D2BF4 g_table_08521214[];

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

/* Complete [0x080D2BF4, 0x080D2CC2): 206 bytes, 92 instructions,
 * including pools:
 * f0b50006040e00250549064a88180688002e58d0044a88180068002808d114e0
 * 00000002283c0000c82800001a1c0de0021c0327136819785878384000020843
 * b042f3d09268002af4d10022117900291bd00901044809180b2c0ed00b2c05dc
 * 0a2c08d011e00000141252080c2c06d00d2c06d009e0487a04e0887a02e0c87a
 * 00e0087b28180006050e517900291ad00901044809180b2c0dd00b2c04dc0a2c
 * 07d010e0141252080c2c06d00d2c06d009e0487a04e0887a02e0c87a00e0087b
 * 28180006050e281cf0bc02bc0847
 */
u8 func_080D2BF4(u8 category)
{
    u8 total = 0;
    u16 id = g_state_02000000.field_3C28;

    if (id != 0) {
        Item *item = find_item(id);
        u8 first;
        u8 second;

        first = item->first;
        if (first) {
            const Entry080D2BF4 *entry = &g_table_08521214[first];

            switch (category) {
            case 10:
                total += entry->field_09;
                break;
            case 11:
                total += entry->field_0A;
                break;
            case 12:
                total += entry->field_0B;
                break;
            case 13:
                total += entry->field_0C;
                break;
            }
        }
        second = item->second;
        if (second) {
            const Entry080D2BF4 *entry = &g_table_08521214[second];

            switch (category) {
            case 10:
                total += entry->field_09;
                break;
            case 11:
                total += entry->field_0A;
                break;
            case 12:
                total += entry->field_0B;
                break;
            case 13:
                total += entry->field_0C;
                break;
            }
        }
    }
    return total;
}
