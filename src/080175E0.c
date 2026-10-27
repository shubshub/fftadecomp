#include "ffta.h"

/* 0x080175E0..0x08017618: 56 bytes / 28 instructions. */
typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
} FlagState;

void func_080175E0(FlagState *state, u8 mode, u16 flags)
{
    switch (mode) {
    case 0:
        state->flags = flags;
        break;
    case 1:
        state->flags |= flags;
        break;
    case 2:
        state->flags &= ~flags;
        break;
    }
}
