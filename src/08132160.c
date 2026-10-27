#include "ffta.h"

/* 0x08132160..0x081321AE: 78 bytes, 34 instructions. */
typedef struct Unit Unit;

typedef struct {
    u8 unknown_00[8];
    Unit *unit;
    u8 unknown_0C[0x1A];
    u16 flags;
} State;

extern u8 func_080CD8FC(const Unit *unit);
extern void func_080CDD88(Unit *unit, u32 value);
extern void func_08131DD4(State *state, u32 value);
extern void func_080CE16C(Unit *unit, u32 value);
extern void func_080CE478(Unit *unit, u32 value);

void func_08132160(State *state)
{
    if (func_080CD8FC(state->unit)) {
        func_080CDD88(state->unit, 0);
        state->flags |= 0x100;
    } else {
        func_08131DD4(state, 31);
        if (!(state->flags & 0x10)) {
            func_080CE16C(state->unit, 1);
            func_080CE478(state->unit, 3);
        }
    }
}
