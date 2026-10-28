#include "ffta.h"

/* Target: complete [0x08060DEC, 0x08060E0C), 32 bytes, 14 instructions. */
typedef struct {
    u16 current;
    u16 value;
} StateEntry;

typedef struct {
    u8 unknown_00[0x128];
    StateEntry entries[256];
} State0200F44C;

extern State0200F44C *data_0200F44C;

void func_08060DEC(u8 index, u8 value)
{
    StateEntry *entry = &data_0200F44C->entries[index];
    entry->current = 0;
    entry->value = value;
}
