#include "ffta.h"

/* 0x080A4274..0x080A433C: 200 bytes, 97 instructions. */
typedef struct {
    void *object;
    u8 unknown_04[8];
    u16 flags;
    u8 unknown_0E[0x1E];
} UpdateRecord;

typedef struct {
    u8 unknown_00[0x10];
    u16 identifier;
    u8 unknown_12[0x0E];
    UpdateRecord records[15];
    u8 unknown_2B4[0x0C];
    u8 count;
} UpdateOwner;

typedef struct {
    void *first[6];
    void *second[6];
    u16 count;
} SelectionList;

extern u32 func_080CCD50(u16 identifier, u8 selector);
extern void *func_08099494(void *context, void *object);
extern void func_080A21B4(SelectionList *selection, void *old_object,
                          void *new_object);

static inline u32 update_record(UpdateRecord *record, SelectionList *selection,
                                 void *context)
{
    void *replacement = func_08099494(context, record->object);
    s32 i;

    if (replacement == 0 || (record->flags & 0x40)) {
        return 0;
    }
    for (i = 0; i < selection->count; i++) {
        if (selection->first[i] == record->object) {
            return 0;
        }
        if (selection->second[i] == record->object) {
            return 0;
        }
    }
    func_080A21B4(selection, record->object, replacement);
    record->object = replacement;
    return 1;
}

u32 func_080A4274(UpdateOwner *owner, SelectionList *selection, void *context)
{
    u32 changed;
    s32 i;

    if (owner->identifier != 0 &&
        !func_080CCD50(owner->identifier, 0x17)) {
        return 0;
    }
    changed = 0;
    for (i = 0; i < owner->count; i++) {
        UpdateRecord *record = &owner->records[i];
        changed |= update_record(record, selection, context);
    }
    return changed;
}
