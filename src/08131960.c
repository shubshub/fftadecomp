#include "ffta.h"

/* 0x08131960..0x08131986: 38 bytes, 18 instructions. */
typedef struct {
    u32 first;
    u32 second;
    u8 unknown_08[4];
    u16 identifier;
    u8 unknown_0E[0x18];
    u16 flags;
} State;

extern u32 func_08130150(u32 first, u32 second, u16 identifier, u32 option);

u32 func_08131960(const State *state)
{
    u32 first = state->first;
    u32 second = state->second;
    u16 identifier = state->identifier;
    u16 selected = state->flags & 0x10;

    return func_08130150(first, second, identifier, selected ? 2 : 0);
}
