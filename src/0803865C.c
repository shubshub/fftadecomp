#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F3C];
    u16 entries[20];
} EntryState;

extern EntryState g_state_02000000;

/* 0803865C..08038678: 28 bytes, including the global and table-offset literals. */
u16 func_0803865C(u16 value, u16 index)
{
    u16 previous = g_state_02000000.entries[index];

    g_state_02000000.entries[index] = value;
    return previous;
}
