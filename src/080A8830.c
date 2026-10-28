#include "ffta.h"

/* 0x080A8830: 10 bytes. */
typedef struct {
    u8 unknown_00[0x2c0];
    u8 count;
} SelectionState;

u8 func_080A8830(const SelectionState *state)
{
    return state->count;
}
