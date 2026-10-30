#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 kind;
    u8 unknown_02;
    u8 variant;
} Record0812F328;

typedef struct {
    u8 unknown_00[0x28];
    u8 cursor;
    u8 unknown_29[3];
    const u8 *entry;
    const Record0812F328 *record;
} State0812F328;

extern State0812F328 data_0200F3F0;
extern const Record0812F328 data_08553E70[];

/* 0x0812F328..0x0812F34C:
 * 06 4A 11 1C 28 31 08 70 09 78 D0 6A 40 18 00 78
 * 80 00 03 49 40 18 10 63 70 47 00 00 F0 F3 00 02
 * 70 3E 55 08. */
void func_0812F328(u8 index)
{
    State0812F328 *state = &data_0200F3F0;

    state->cursor = index;
    state->record = &data_08553E70[state->entry[state->cursor]];
}
