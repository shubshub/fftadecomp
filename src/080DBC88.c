#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F];
    u8 value;
} ObjectState;

s8 func_080DBC88(const ObjectState *state)
{
    return state->value;
}
