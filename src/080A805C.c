#include "ffta.h"

// 0x080A805C..0x080A80C8: 108 bytes.
// 70b5041c0e1c151c1ce02e20215e2a22a05e814207db201c1430fff7b7ff201cfff7b4ff
// 08e0201cfff7b0ff002803d0201c1430fff7aaffa08a2086e08aa08660886086201c3030
// 291c9af0d9f8002809d0216ba06b8142d7d13420215e3c22a05e8142d1d170bc01bc0047

typedef struct {
    s16 x;
    s16 y;
    u8 unknown_04[4];
    s16 error;
    s16 period;
    s16 step_x;
    s16 step_y;
    s16 distance_x;
    s16 distance_y;
} LineState;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_06[2];
} LinePoint;

typedef struct {
    LineState first;
    LineState second;
    u8 unknown_28[2];
    s16 unknown_2A;
    u8 unknown_2C[2];
    s16 unknown_2E;
    LinePoint current;
    LinePoint end;
} LineWalkState;

typedef s32 (*LineVisitor)(LinePoint *point, void *context);

s32 func_080A7FE8(LineState *state);

void func_080A805C(LineWalkState *state, LineVisitor visit, void *context)
{
    while (visit(&state->current, context)
           && (state->current.x != state->end.x
               || state->current.y != state->end.y
               || state->current.z != state->end.z)) {
        if (state->unknown_2E >= state->unknown_2A) {
            func_080A7FE8(&state->second);
            func_080A7FE8(&state->first);
        } else {
            if (func_080A7FE8(&state->first))
                func_080A7FE8(&state->second);
        }

        state->current.x = state->second.x;
        state->current.z = state->second.y;
        state->current.y = state->first.y;
    }
}
