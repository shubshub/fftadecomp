#include "ffta.h"

typedef struct DisplayEntry {
    u16 x;
    u16 y;
    const u8 *data;
} DisplayEntry;

typedef struct DisplayState {
    u16 x;
    u16 y;
    u8 unknown_04[0x478];
    DisplayEntry entries[0];
} DisplayState;

extern DisplayState *data_0200F444;
extern const u8 data_0839176A[];
extern const u8 data_08391772[];

/* 0802E08C..0802E0DC: 80 bytes, 30 instructions. */
void func_0802E08C(u32 index, u8 selected)
{
    DisplayEntry *entry = &data_0200F444->entries[index];

    entry->data = selected ? data_0839176A : data_08391772;
    entry->x = (data_0200F444->x - 1) * 8 + 2;
    entry->y = ((index + 1) * 2 + data_0200F444->y) * 8;
}
