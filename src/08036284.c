#include "ffta.h"

typedef struct {
    u8 unknown_00[3];
    u8 identifier;
    u8 unknown_04[8];
} SearchEntry;

typedef struct {
    u8 unknown_00[0xB0];
    SearchEntry entries[30];
} SearchState;

/* 08036284..080362A4: 32 bytes, 16 instructions. */
SearchEntry *func_08036284(u32 identifier, SearchState *state)
{
    s32 index;

    for (index = 0; index < 30; index++) {
        SearchEntry *entry = &state->entries[index];

        if (entry->identifier == identifier)
            return entry;
    }
    return 0;
}
