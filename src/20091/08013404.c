#include "ffta.h"

typedef struct {
    u8 unknown_00[0x74C];
    u32 first;
    u32 second;
} State08013404;

void func_08013404(u32 first, u32 second)
{
    State08013404 *state = *(State08013404 **)0x0200918C;

    state->first = first;
    state->second = second;
}
