#include "ffta.h"

/* 0x0804BB10..0x0804BB5A: 74 bytes, 35 instructions. */
typedef struct {
    u8 unknown_00[2];
    u8 entries[4][4];
    u8 unknown_12[2];
} LookupRow;

extern const LookupRow data_08391E40[];

u8 func_0804BB10(u8 index, u8 key)
{
    const LookupRow *rows = data_08391E40;
    const LookupRow *row = &rows[index];

    if (row->entries[0][1] == key) {
        return row->entries[0][0];
    }
    if (row->entries[1][1] == key) {
        return row->entries[1][0];
    }
    if (row->entries[2][1] == key) {
        return row->entries[2][0];
    }
    if (row->entries[3][1] == key) {
        return row->entries[3][0];
    }
    return 255;
}
