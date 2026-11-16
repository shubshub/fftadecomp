#include "ffta.h"

/* Complete [0x080A7040, 0x080A7138): 248 bytes, 118 instructions, including
 * the two-word literal pool at 0x080A70B4.
 * f0b557464e464546e0b483b000919146184a8818007801900021814264dab12080004843
 * 009e35182f1c286801318a46002855d0697a0b2952d00c2950d0006821f0fef80006000e
 * 012849d0298a0a48814245d0b0218900681800788046002343453ddab0229200b8180078
 * 984205da002107e0bd260000090100002c205843203039188a8980201040013302930028
 * 23d04020104000281fd1286800680968096887f067fa00040014002815dd00042b68040c
 * 002203e00b608c800de001320c2a0adcd0004e4681190868002801d09842f4d18888a042
 * eed3029b4345c1db5146019881429adb03b038bc9846a146aa46f0bc01bc0047
 *
 * For each usable state of the collection and each of its flagged entries,
 * asks func_0812E5B4 for an adjustment and records a positive one for the
 * state's object in the 13-slot table of src/080A7138.c.
 */
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
s32 func_0812E5B4(void *unit, void *other);

/* Records an adjustment for one object in the 13-slot table: the first slot
 * that is empty or already holds the object takes it, unless that slot's
 * adjustment is already as large (0x080A70F4..0x080A7118).  The ROM has no
 * out-of-line copy and no second expansion of it. */
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
            /* The ROM narrows the result to s16 (lsls/asrs #16 at 0x080A70E6). */
            chance = (s16)func_0812E5B4(info->object->data, entry->object->data);
            if (chance <= 0)
                continue;
            record_adjustment(entries, info->object, chance);
        }
    }
}
