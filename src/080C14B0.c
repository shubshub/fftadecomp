#include "ffta.h"

typedef struct {
    u8 unknown_00[0x54B4];
    u8 first;
    u8 second;
} Struct080C14B0;

void func_080C14B0(u8 *first, u8 *second)
{
    Struct080C14B0 *state = (Struct080C14B0 *)0x020101F8;

    *first = state->first;
    *second = state->second;
}
