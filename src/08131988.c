#include "ffta.h"

/* 0x08131988..0x081319BE: 54 bytes. */
typedef struct {
    u32 first;
    u32 second;
    u8 unknown_08[4];
    u16 identifier;
    u16 value;
    u8 unknown_10[0x16];
    u16 flags;
} State;

extern u32 func_081307C8(u32, u32, u16, u16, u16, u8);

u32 func_08131988(const State *state)
{
    u32 first = state->first;
    u32 second = state->second;
    u16 identifier = state->identifier;
    u16 value = state->value;

    return func_081307C8(first, second, identifier, value, 0,
                         (u16)(state->flags & 0x10) ? 2 : 0);
}
