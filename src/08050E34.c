#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 flags;
} Control;

typedef struct {
    u8 unknown_00[0x68];
    Control control;
} ControlState;

extern void func_08017D18(Control *control, u8 flags);

/* 08050E34..08050E52: 30 bytes, 14 instructions. */
void func_08050E34(ControlState *state)
{
    u8 flags = state->control.flags & 4;

    func_08017D18(&state->control, flags | 3);
}
