typedef unsigned char u8;
typedef unsigned short u16;

struct Item {
    u16 id;
    u8 quantity;
    u8 unknown_03;
};

struct ItemInfo {
    u8 unknown_00[0xC];
    u8 flags;
    u8 unknown_0D[0x13];
};

extern const struct ItemInfo g_table_0851D180[];
extern struct Item *func_080CB210(unsigned int id, int *count);
extern u8 func_080CBD34(u16 id);
extern u16 func_080CC86C(u16 id);
extern u8 func_080CC8B4(u16 level);
extern u16 func_080CC9F0(u8 owner, u8 index);
extern u8 func_080CECF4(void);

/* Target: 080CBDC0..080CBF32, 370 bytes. */
u16 func_080CBDC0(struct Item *output, u8 category, u16 level, u8 owner)
{
    u16 first, length;
    int mask;
    u8 rank = func_080CC8B4(level);
    u16 i;
    u16 count;
    struct Item *entry, *items;
    u16 index;

    mask = 0x10;
    if (rank == 1)
        mask = 0x20;
    else if (rank > 1)
        mask = 0x40;

    if (category != 5) {
        first = 1;
        length = 361;
    } else {
        first = 362;
        length = 14;
    }

    i = first;
    count = 0;
    for (; i < length + first; i++) {
        if ((g_table_0851D180[i].flags & mask)
            && func_080CBD34(i) == category) {
            entry = output;
            entry += count;
            entry->id = i;
            index = func_080CC86C(entry->id);
            if (index != 0xFFFF) {
                items = func_080CB210(entry->id, 0);
                entry->quantity = items[index].quantity;
                entry->unknown_03 = items[index].unknown_03;
            } else {
                entry->quantity = entry->unknown_03 = 0;
            }
            count++;
        }
    }

    for (i = 0; i <= func_080CECF4(); i++) {
        u16 id = func_080CC9F0(owner, i);
        if (func_080CBD34(id) == category && id != 0) {
            entry = output;
            entry += count;
            entry->id = id;
            index = func_080CC86C(entry->id);
            if (index != 0xFFFF) {
                items = func_080CB210(id, 0);
                entry->quantity = items[index].quantity;
                entry->unknown_03 = items[index].unknown_03;
            } else {
                entry->quantity = entry->unknown_03 = 0;
            }
            count++;
        }
    }
    return count;
}
