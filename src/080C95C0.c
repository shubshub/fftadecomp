#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x2030];
    u8 values[0];
} State;

extern State g_state_02000000;

void func_080C95C0(u16 index, u32 value)
{
    g_state_02000000.values[index] = value;
}
