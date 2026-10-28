#include "ffta.h"

/* 0x080A6F20: 286 bytes. */
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
    Object *object;
    u8 unknown_04[0x1c];
    SelectionEntry entries[15];
    u8 unknown_2b4[0x0c];
    u8 count;
} SelectionState;

typedef struct {
    SelectionState states[14];
    u8 unknown_26b8[5];
    u8 count;
} SelectionCollection;

u8 func_080C95A8(u32 id);
u8 func_080C9540(u32 id);
u8 func_080C8240(const void *object);
u8 func_0809AA10(const Object *object);
u8 func_080C8280(const void *object);
u8 func_08130834(const void *object);

u8 func_080A6F20(SelectionCollection *collection)
{
    s32 i, j;
    s32 state_count, entry_count;
    SelectionState *state;
    SelectionInfo *info;
    SelectionInfo *entry;

    if (!func_080C95A8(13) || !func_080C9540(65))
        return 0;

    state_count = collection->count;
    for (i = 0; i < state_count; i++) {
        state = &collection->states[i];
        info = (SelectionInfo *)state;
        if (state->object == 0 || func_080C8240(state->object->data))
            continue;
        if (func_0809AA10(state->object)) {
            if (func_080C9540(66) == 1)
                continue;
        } else {
            if (func_080C9540(66) == 0)
                continue;
        }
        if (info->status == 11)
            continue;
        if (info->status == 12)
            continue;
        if (info->value.fields.type == 0x109)
            continue;

        entry_count = state->count;
        for (j = 0; j < entry_count; j++) {
            if (state->count < j)
                entry = 0;
            else
                entry = &state->entries[j].info;
            if ((entry->flags & 0x80) &&
                !func_080C8280(entry->object->data) &&
                !(entry->flags & 0x40) && !(entry->value.conditions & 0x800) &&
                func_08130834(entry->object->data))
                return 1;
        }
    }
    return 0;
}
