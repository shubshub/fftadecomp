#include "ffta.h"

typedef struct {
    u16 identifier : 10;
    u16 unknown_id : 6;
    u8 unknown_02[2];
    u8 first_index;
    u8 second_index;
    u8 unknown_06[10];
} __attribute__((packed)) SelectionRecord080D2380;

typedef struct Node080D2380 {
    const SelectionRecord080D2380 *record;
    struct Node080D2380 *previous;
    struct Node080D2380 *next;
} Node080D2380;

typedef struct {
    u8 unknown_00[0x28C8];
    Node080D2380 *head;
} State080D2380;

typedef struct {
    u8 unknown_00[0x0E];
    u8 value;
    u8 unknown_0F;
} TableEntry080D2380;

extern u8 g_state_02000000[];
extern const TableEntry080D2380 g_table_08521214[];
extern u32 func_08002804(void);

static inline const SelectionRecord080D2380 *find_record(
    const Node080D2380 *head, u16 identifier)
{
    const Node080D2380 *node;

    if (head == 0)
        return 0;
    node = head;
    do {
        const SelectionRecord080D2380 *record = node->record;

        if (record->identifier == identifier)
            return record;
        node = node->next;
    } while (node != 0);
    return 0;
}

/* Complete target: [0x080D2380, 0x080D241A), 154 bytes. */
u32 func_080D2380(u32 identifier)
{
    u8 first = 0;
    u8 second = 0;
    u32 selected;
    const SelectionRecord080D2380 *record =
        find_record(((const State080D2380 *)g_state_02000000)->head,
                    identifier);

    if (record == 0)
        return 0;
    if (record->first_index != 0)
        first = g_table_08521214[record->first_index].value;
    if (record->second_index != 0)
        second = g_table_08521214[record->second_index].value;
    if (first == 0)
        selected = second;
    else if (second == 0)
        selected = first;
    else if (first == 1)
        selected = second;
    else if (second == 1)
        selected = first;
    else
        selected = (u16)func_08002804() % 2 ? first : second;
    return selected;
}
