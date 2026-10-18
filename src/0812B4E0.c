#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
} Entry0812B4E0;

typedef struct {
    u8 unknown_000[0x2A0];
    Entry0812B4E0 entries[3];
    u8 next;
} State0812B4E0;

Entry0812B4E0 *func_0812B4E0(State0812B4E0 *state)
{
    Entry0812B4E0 *entry = &state->entries[state->next];

    state->next++;
    return entry;
}
