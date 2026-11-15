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

typedef struct {
    u8 unknown_00[13];
    u8 field_0D;
    u8 value;
    u8 unknown_0F;
} Entry080D2380;

extern ItemListState g_state_02000000;
extern const Entry080D2380 g_table_08521214[];
extern u32 func_08002804(void);

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

/* Complete [0x080D2380, 0x080D241A): 154 bytes. */
u32 func_080D2380(u32 id)
{
    u8 second = 0;
    u8 first = 0;
    Item *item = find_item(id);

    if (item == 0)
        return 0;
    if (item->first)
        first = g_table_08521214[item->first].value;
    if (item->second)
        second = g_table_08521214[item->second].value;
    {
        u32 result;
        if (first != 0) {
            if (second != 0) {
                if (first != 1) {
                    if (second != 1) {
                        u16 random = func_08002804();
                        result = (random & 1) ? first : second;
                    } else {
                        result = first;
                    }
                } else {
                    result = second;
                }
            } else {
                result = first;
            }
        } else {
            result = second;
        }
        return result;
    }
}
