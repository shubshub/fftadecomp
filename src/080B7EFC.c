#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10B];
    u8 first;
    u8 second;
} Struct080B7EFC;

void func_080B7EFC(Struct080B7EFC *state, u8 first, u8 second)
{
    state->first = first;
    state->second = second;
}
