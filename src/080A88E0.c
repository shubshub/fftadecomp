#include "ffta.h"

typedef struct {
    u8 unknown_00[0x26BD];
    u8 unknown_26bd;
} ObjectState;

/* 0x080A88E0..0x080A88EC: 12 complete bytes, including the member-offset literal. */
u8 func_080A88E0(const ObjectState *state)
{
    return state->unknown_26bd;
}
