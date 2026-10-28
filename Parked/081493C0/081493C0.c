typedef unsigned char u8;

struct PoolObject {
    u8 unknown_000[0x980];
    u8 state : 7;
    u8 busy : 1;
    u8 unknown_981[9];
} __attribute__((packed));

extern u8 data_03006168;
extern struct PoolObject *data_0300616C;

static inline struct PoolObject *find_free_object(int count, struct PoolObject *entry)
{
    int index;

    for (index = 0; index < count; index++, entry++) {
        u8 busy = entry->busy;
        if (busy == 0)
            return entry;
    }
    return 0;
}

struct PoolObject *func_081493C0(void)
{
    struct PoolObject *entry = find_free_object(data_03006168, data_0300616C);

    entry->busy = 1;
    entry->state = 4;
    return entry;
}
