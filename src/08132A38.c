#include "ffta.h"

/* 0x08132A38..0x08132A96: 94 bytes. */
typedef struct {
    u8 unknown_00[0x2A];
    u16 entries[0];
} UnitEntries;

typedef struct {
    u8 unknown_00[8];
    UnitEntries *unit;
    u8 unknown_0C[0x0C];
    u16 selected_entry;
    u8 unknown_1A[0x0C];
    u16 flags;
} EntryState;

extern s8 func_081329EC(UnitEntries *);
extern void func_080CAF78(UnitEntries *, int, u8);
extern void func_080CB54C(UnitEntries *, int);
extern u8 func_08131BB8(UnitEntries *);
extern void func_080CA9E8(u16, int);
extern void func_080CA2E8(UnitEntries *);

void func_08132A38(EntryState *state)
{
    int slot;
    u16 entry;

    if (state->flags & 0x10)
        return;
    slot = func_081329EC(state->unit);
    entry = 0;
    if (slot >= 0) {
        entry = state->unit->entries[slot];
        func_080CAF78(state->unit, 0, slot);
        func_080CB54C(state->unit, 1);
        if (func_08131BB8(state->unit))
            func_080CA9E8(entry, 1);
    }
    state->selected_entry = entry;
    func_080CA2E8(state->unit);
}
