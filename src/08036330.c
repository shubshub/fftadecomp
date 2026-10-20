#include "ffta.h"

typedef struct {
    u8 unknown_00[3];
    u8 value;
    u8 unknown_04[8];
} StateEntry;

typedef struct {
    u8 unknown_0000[0x2CC0];
    StateEntry entries[0];
} State;

extern State g_state_02000000;

u8 func_08036330(u8 selector)
{
    return g_state_02000000.entries[selector - 1].value;
}
