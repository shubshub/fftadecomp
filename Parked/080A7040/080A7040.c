typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

struct Owner {
    void *unit;
};

struct Record {
    struct Owner *owner;
    u8 unknown_04[8];
    u16 flags;
    u8 unknown_0E[0x1E];
};

struct Entry {
    struct Owner *owner;
    u8 unknown_04[5];
    u8 state;
    u8 unknown_0A[6];
    u16 kind;
    u8 unknown_12[0x0E];
    struct Record records[15];
    u8 unknown_2B4[0x0C];
    u8 count;
    u8 unknown_2C1[3];
};

struct Registry {
    struct Entry entries[14];
    u8 unknown_26B8[5];
    u8 count;
};

struct Result {
    struct Owner *owner;
    u16 score;
    u8 unknown_06[2];
};

extern u8 func_080C8280(void *unit);
extern s16 func_0812E5B4(void *first, void *second);

static inline struct Record *record_at(struct Entry *entry, int index)
{
    if (entry->count < index)
        return 0;
    return &entry->records[index];
}

static inline int update_result(struct Result *results, struct Owner *owner, u16 score)
{
    int index = 0;

    while (index < 13) {
        struct Result *result = &results[index];

        if (result->owner == 0 || result->owner == owner) {
            if (result->score < score) {
                result->owner = owner;
                result->score = score;
                return 1;
            }
        }
        index++;
    }
    return 0;
}

void func_080A7040(void *unused, struct Registry *registry, struct Result *results)
{
    int count = registry->count;
    int index;

    for (index = 0; index < count; index++) {
        struct Entry *entry = &registry->entries[index];
        int record_count;
        int record_index;

        if (entry->owner == 0 || entry->state == 11 || entry->state == 12
            || func_080C8280(entry->owner->unit) == 1 || entry->kind == 0x109)
            continue;

        record_count = entry->count;
        for (record_index = 0; record_index < record_count; record_index++) {
            struct Record *record = record_at(&registry->entries[index], record_index);

            if (!(record->flags & 0x80))
                continue;
            if (record->flags & 0x40)
                continue;
            {
                int score = func_0812E5B4(entry->owner->unit, record->owner->unit);

                if (score > 0)
                    update_result(results, entry->owner, score);
            }
        }
    }
}
