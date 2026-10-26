typedef unsigned char u8;
typedef unsigned short u16;

struct ItemEntry {
    u16 id : 10;
    u16 flags : 6;
} __attribute__((packed));

struct MenuContext {
    u8 unknown_00[0x20];
    struct ItemEntry *entries[1];
};

extern struct MenuContext *data_0200F44C;
extern int func_080CE4DC(int id, int field);
extern u8 func_080CB9CC(int category);

u8 func_08060100(void *context, int index)
{
    struct ItemEntry *entry = data_0200F44C->entries[index];
    u8 category = func_080CE4DC(entry->id, 2);

    category += 15;

    if (func_080CE4DC(entry->id, 1) == 1)
        category = 6;
    return func_080CB9CC(category);
}
