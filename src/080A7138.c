#include "ffta.h"

/* 080A7138 .. 080A7218: 224 bytes. */
typedef struct {
    u8 unknown_00[10];
    u8 value;
} ValueUnit;

typedef struct {
    ValueUnit *unit;
} UnitReference;

typedef struct {
    UnitReference *reference;
    u16 adjustment;
    u16 unknown_06;
} ValueEntry;

typedef struct {
    UnitReference *references[13];
    u16 count;
    u8 unknown_36[6];
    ValueEntry *entries;
    u8 unknown_40;
    u8 processed;
    u8 unknown_42[0x4A];
} ValueResult;

extern void *func_08022840(u32);
extern void func_08022854(void *);
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern void func_080A7040(ValueResult *, const void *, ValueEntry *);
extern s32 func_080C7EA4(ValueUnit *, s32);
extern u8 func_080C9B8C(ValueUnit *);

ValueResult *func_080A7138(const void *first, const void *second)
{
    ValueResult *result = func_08022840(sizeof(ValueResult));
    ValueEntry *entries;
    s32 index;

    g_callbacks_0836D4B8[0](result, sizeof(ValueResult));
    entries = func_08022840(sizeof(ValueEntry) * 13);
    g_callbacks_0836D4B8[0](entries, sizeof(ValueEntry) * 13);
    func_080A7040(result, first, entries);
    if (second != 0)
        func_080A7040(result, second, entries);

    for (index = 0; index < 13 && entries[index].reference != 0; index++) {
        s16 value = entries[index].adjustment +
                    func_080C7EA4(entries[index].reference->unit, 7);
        if (value <= 99) {
            entries[index].reference->unit->value = value;
        } else {
            entries[index].reference->unit->value = 0;
            if (func_080C9B8C(entries[index].reference->unit))
                result->references[result->count++] = entries[index].reference;
        }
    }
    result->processed = index;
    result->entries = entries;
    if (result->count == 0 && result->processed == 0) {
        func_08022854(entries);
        func_08022854(result);
        return 0;
    }
    return result;
}
