#include "ffta.h"

struct TableState08010D2C {
    u32 unknown_00;
    const u8 *resources;
    const u8 *entries;
    s16 row;
    s16 column;
    u16 unknown_10;
    s16 columns;
    u16 flags;
    u16 unknown_16;
    const u8 *resolved;
};

/* Complete [0x08010D2C, 0x08010DCE): 162 bytes, 81 instructions. */
void func_08010D2C(struct TableState08010D2C *state)
{
    const u8 **output = &state->resolved;
    s16 columns = state->columns;
    s16 column = state->column;
    s16 position = column;
    u16 flags = state->flags;
    s16 row;
    u16 value;
    const u8 *entry;

    if (flags & 0x40)
        position = columns - column - 1;
    row = state->row;
    if (position == -1)
        position = column;
    if (flags & 0x4000) {
        entry = state->entries + ((const u16 *)state->entries)[row];
        value = entry[2 + (s16)position * 2];
    } else {
        entry = state->entries + ((const u32 *)state->entries)[row];
        entry += (s16)position * 4;
        value = entry[2] | (entry[3] << 8);
    }
    if (state->flags & 0x2000)
        *output = state->resources + ((const u16 *)state->resources)[(s16)value];
    else
        *output = state->resources + ((const u32 *)state->resources)[(s16)value];
}
