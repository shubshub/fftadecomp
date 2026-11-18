#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 value;
} Unit;

typedef struct {
    u8 unknown_00;
    u8 kind;
} ActionRecord;

typedef struct {
    Unit *source;
    Unit *target;
    u8 unknown_08[0x28];
    ActionRecord *record;
} ActionState;

extern u8 func_080CDA4C(const void *object);

/* Evaluator slot 25, [0x08131838, 0x08131866). */
s32 func_08131838(ActionState *state)
{
    if (func_080CDA4C(state->target)) {
        u8 kind = state->record->kind;
        if (kind == 0x15 || kind == 8 || kind == 0x0F)
            return 0;
    }
    return state->source->value;
}
