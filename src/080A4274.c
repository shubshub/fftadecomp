#include "ffta.h"

/* 0x080A4274..0x080A433C: 200 bytes, 97 instructions. */
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
    u8 unknown_04[0x0c];
    u16 type;
    u8 unknown_12[0x0e];
    SelectionEntry entries[15];
    u8 unknown_2b4[0x0c];
    u8 count;
} SelectionState;

typedef struct {
    Object *first[6];
    Object *second[6];
    u16 count;
} SelectionList;

extern u32 func_080CCD50(u16 index, u8 selector);
extern Object *func_08099494(void *owner, Object *state);
extern void func_080A21B4(SelectionList *state, Object *first, Object *second);

/* Not an out-of-line function in the ROM.  The same body is expanded a second
 * time in func_080A433C (0x080A4744..0x080A47A2), where the result is unused. */
static inline u8 update_entry(SelectionInfo *entry, SelectionList *selection,
                              void *context)
{
    Object *replacement = func_08099494(context, entry->object);
    s32 i;

    if (replacement == 0 || (entry->flags & 0x40)) {
        return 0;
    }
    for (i = 0; i < selection->count; i++) {
        if (selection->first[i] == entry->object) {
            return 0;
        }
        if (selection->second[i] == entry->object) {
            return 0;
        }
    }
    func_080A21B4(selection, entry->object, replacement);
    entry->object = replacement;
    return 1;
}

u8 func_080A4274(SelectionState *state, SelectionList *selection, void *context)
{
    u8 changed;
    s32 i;

    if (state->type != 0 && !func_080CCD50(state->type, 0x17)) {
        return 0;
    }
    changed = 0;
    for (i = 0; i < state->count; i++) {
        changed |= update_entry(&state->entries[i].info, selection, context);
    }
    return changed;
}
