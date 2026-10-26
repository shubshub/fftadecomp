typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 id : 10;
    u16 flags : 6;
    u8 unknown_02[2];
    u8 first;
    u8 second;
} __attribute__((packed)) Item;

typedef struct Node {
    const Item *item;
    void *unknown_04;
    struct Node *next;
} Node;

typedef struct {
    u8 unknown_00[0x28C8];
    Node *head;
    u8 unknown_28CC[0x135C];
    u16 selected_id;
} State;

typedef struct {
    u8 unknown_00[7];
    u8 flags;
    u8 unknown_08[8];
} Entry;

extern State g_state_02000000;
extern const Entry g_table_08521214[];

static inline const Item *find_item(Node *head, u16 id)
{
    if (head) {
        Node *node = head;

        do {
            if (node->item->id == id)
                return node->item;
            node = node->next;
        } while (node);
    }
    return 0;
}

static inline u8 supports_kind(u8 index, u8 kind)
{
    const Entry *entry = &g_table_08521214[index];
    int flags = entry->flags;

    return (flags >> (kind - 1)) & 1;
}

u8 func_080D2CC4(u8 kind)
{
    u8 result = 0;
    u16 id = g_state_02000000.selected_id;

    if (id) {
        const Item *item = find_item(g_state_02000000.head, id);

        if (item->first && supports_kind(item->first, kind))
            result = 1;
        if (item->second && supports_kind(item->second, kind))
            result = 1;
    }
    return result;
}
