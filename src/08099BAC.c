#include "ffta.h"

/* 0x08099BAC..0x08099BF4: 72 bytes. */
typedef struct {
    u32 unit;
} UnitEntry;

typedef struct {
    u32 unit;
    u8 unknown_04[0x7C];
    void *entries;
} UnitState;

void func_08097298(u32 unit);
UnitEntry *func_08099494(void *entries, UnitState *state);
UnitEntry *func_080970E8(void *entries, u32 unit);
void func_080CE1B0(u32 unit, u32 value);
void func_080CE2F0(u32 unit, u32 value);

void func_08099BAC(UnitState *state)
{
    void *entries;
    UnitEntry *entry;

    func_08097298(state->unit);

    entries = state->entries;
    while ((entry = func_08099494(entries, state)) != 0)
        func_080CE1B0(entry->unit, 0);

    entries = state->entries;
    while ((entry = func_080970E8(entries, state->unit)) != 0)
        func_080CE2F0(entry->unit, 0);
}
