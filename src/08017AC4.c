#include "ffta.h"

void func_08017AC4(Struct08017AC4 *state, u32 first, u32 second) {
    state->flags |= 2;
    state->first = first;
    state->second = second;
}
