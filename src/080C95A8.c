#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x2030];
    u8 values[0];
} State;

extern State g_state_02000000;

u8 func_080C95A8(u16 index)
{
    return g_state_02000000.values[index];
}
