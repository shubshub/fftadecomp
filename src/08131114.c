#include "ffta.h"

/* 0x08131114..0x0813112C: 24 bytes. */
typedef struct {
    u8 unknown_00;
    u8 value;
} PairOptions;

typedef struct {
    void *source;
    void *target;
    u8 unknown_08[0x28];
    const PairOptions *options;
} UnitPairState;

extern int func_0812DAEC(void *, void *, u8);

u8 func_08131114(const UnitPairState *state)
{
    return func_0812DAEC(state->source, state->target, state->options->value);
}
