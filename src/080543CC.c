#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1A];
    u8 position;
} ListState;

/* Complete target: [0x080543CC, 0x080543DC), 16 bytes. */
u8 func_080543CC(ListState *state, u8 offset)
{
    return offset + state->position;
}
