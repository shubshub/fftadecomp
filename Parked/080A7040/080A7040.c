#include "ffta.h"

/* 080A7040 .. 080A7138: 248 bytes. */
typedef struct {
    void *data;
} Object;

typedef struct {
    Object *object;
    u8 unknown_04[5];
    u8 status;
    u16 unknown_0a;
    u16 flags;
    u16 unknown_0e;
    union {
        u32 conditions;
        struct {
            u16 type;
            u16 unknown_12;
        } fields;
    } value;
    u8 unknown_14[0x0c];
} SelectionInfo;

typedef struct {
    SelectionInfo info;
    u8 unknown_20[0x0c];
} SelectionEntry;

typedef struct {
    SelectionInfo info;
    SelectionEntry entries[15];
    u8 unknown_2b4[0x0c];
    u8 count;
} SelectionState;

typedef struct {
    SelectionState states[14];
    u8 unknown_26b8[5];
    u8 count;
} SelectionCollection;

typedef struct {
    Object *reference;
    u16 adjustment;
    u16 unknown_06;
} ValueEntry;

u8 func_080C8280(const void *object);
s16 func_0812E5B4(void *unit, void *other);

static inline void record_adjustment(ValueEntry *entries, Object *reference, u16 adjustment)
{
    s32 i;

    for (i = 0; i < 13; i++) {
        if (entries[i].reference != 0 && entries[i].reference != reference)
            continue;
        if (entries[i].adjustment >= adjustment)
            break;
        entries[i].reference = reference;
        entries[i].adjustment = adjustment;
        break;
    }
}

void func_080A7040(void *result, SelectionCollection *collection, ValueEntry *entries)
{
    s32 i, j;
    s32 state_count, entry_count;
    SelectionState *state;
    SelectionInfo *info;
    SelectionInfo *entry;
    s32 chance;

    state_count = collection->count;
    for (i = 0; i < state_count; i++) {
        state = &collection->states[i];
        info = &state->info;
        if (info->object == 0)
            continue;
        if (info->status == 11)
            continue;
        if (info->status == 12)
            continue;
        if (func_080C8280(info->object->data) == 1)
            continue;
        if (info->value.fields.type == 0x109)
            continue;

        entry_count = state->count;
        for (j = 0; j < entry_count; j++) {
            if (state->count < j)
                entry = 0;
            else
                entry = &state->entries[j].info;
            if (!(entry->flags & 0x80))
                continue;
            if (entry->flags & 0x40)
                continue;
            chance = func_0812E5B4(info->object->data, entry->object->data);
            if (chance <= 0)
                continue;
            record_adjustment(entries, info->object, chance);
        }
    }
}
