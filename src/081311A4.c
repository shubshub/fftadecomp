#include "ffta.h"

/* 0x081311A4..0x081311C0: 28 bytes. */
typedef struct {
    u8 unknown_00[2];
    u8 value_02;
    u8 value_03;
} PairOptions;

typedef struct {
    void *source;
    void *target;
    u8 unknown_08[0x28];
    const PairOptions *options;
} UnitPairState;

extern int func_0812D5F4(void *, void *, u8, u8);

u8 func_081311A4(const UnitPairState *state)
{
    return func_0812D5F4(state->source, state->target,
                         state->options->value_03, state->options->value_02);
}
